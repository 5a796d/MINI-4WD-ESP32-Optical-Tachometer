#include <Arduino.h>
#include "driver/pcnt.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/* ================= CONFIG ================= */

#define PCNT_INPUT_PIN       18
#define PCNT_UNIT_USED       PCNT_UNIT_0

#define SAMPLE_TIME_MS       200
#define IMPULSI_PER_GIRO     64      // 32 finestre × 2 fronti / set the number of holes in your disc x2

#define RPM_MIN_STABLE       8000
#define STABLE_DELTA_RPM     100
#define STABLE_TIME_MS       500

#define EMA_ALPHA            0.2f

#define PCNT_FILTER_TICKS    800     // ~10 µs @ 80 MHz APB

/* ===== DISPLAY / I2C ===== */

#define SCREEN_WIDTH         128
#define SCREEN_HEIGHT        64
#define DISPLAY_UPDATE_MS    300

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

/* ============== VARIABILI ================= */

unsigned long lastSample = 0;
unsigned long stableTimer = 0;
unsigned long lastDisplayUpdate = 0;

float rpmEMA = 0.0f;
float lastRpmEMA = 0.0f;

int   rpmLocked = 0;
bool  stable = false;

/* ========================================== */

void setupPCNT() {
    pcnt_config_t pcntConfig = {};
    pcntConfig.pulse_gpio_num = PCNT_INPUT_PIN;
    pcntConfig.ctrl_gpio_num  = PCNT_PIN_NOT_USED;
    pcntConfig.unit           = PCNT_UNIT_USED;
    pcntConfig.channel        = PCNT_CHANNEL_0;

    pcntConfig.pos_mode = PCNT_COUNT_INC;
    pcntConfig.neg_mode = PCNT_COUNT_INC;
    pcntConfig.lctrl_mode = PCNT_MODE_KEEP;
    pcntConfig.hctrl_mode = PCNT_MODE_KEEP;

    pcntConfig.counter_h_lim = 32767;
    pcntConfig.counter_l_lim = 0;

    pcnt_unit_config(&pcntConfig);

    pcnt_set_filter_value(PCNT_UNIT_USED, PCNT_FILTER_TICKS);
    pcnt_filter_enable(PCNT_UNIT_USED);

    pcnt_counter_clear(PCNT_UNIT_USED);
    pcnt_counter_resume(PCNT_UNIT_USED);
}

/* ========================================== */

void setup() {
    Serial.begin(115200);

    Wire.begin();
    Wire.setTimeOut(50);   //  FIX CRITICO

    setupPCNT();

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        for (;;);
    }

    display.clearDisplay();
    display.setTextColor(SSD1306_WHITE);
    display.setTextSize(2);

    lastSample = millis();
    pcnt_counter_clear(PCNT_UNIT_USED);
}

/* ========================================== */

void loop() {
    unsigned long now = millis();
    unsigned long elapsed = now - lastSample;

    if (elapsed >= SAMPLE_TIME_MS) {

        int16_t pcntValue = 0;
        pcnt_get_counter_value(PCNT_UNIT_USED, &pcntValue);
        pcnt_counter_clear(PCNT_UNIT_USED);
        lastSample = now;

        float rpmRaw = (pcntValue * 60000.0f) /
                       (elapsed * IMPULSI_PER_GIRO);

        rpmEMA = EMA_ALPHA * rpmRaw + (1.0f - EMA_ALPHA) * rpmEMA;

        /* ===== LOGICA STABLE ===== */

        float delta = fabs(rpmEMA - lastRpmEMA);

        if (rpmEMA >= RPM_MIN_STABLE && delta <= STABLE_DELTA_RPM) {
            if (stableTimer == 0) {
                stableTimer = now;
            } else if (now - stableTimer >= STABLE_TIME_MS) {
                stable = true;
                rpmLocked = (int)rpmEMA;
            }
        } else {
            stable = false;
            stableTimer = 0;
        }

        lastRpmEMA = rpmEMA;

        /* ===== DISPLAY (THROTTLED) ===== */

        if (now - lastDisplayUpdate >= DISPLAY_UPDATE_MS) {

            display.clearDisplay();
            display.setCursor(0, 0);

            display.print("RPM:");
            if (stable) {
                display.print(rpmLocked);
                display.setCursor(0, 32);
                display.print("STABLE");
            } else {
                display.print((int)rpmEMA);
            }

            display.display();  // chiamata semplice
            lastDisplayUpdate = now;
        }

        /* ===== DEBUG ===== */

        Serial.print("pcnt=");
        Serial.print(pcntValue);
        Serial.print(" rpmRaw=");
        Serial.print(rpmRaw);
        Serial.print(" rpmEMA=");
        Serial.print(rpmEMA);
        Serial.print(" stable=");
        Serial.println(stable);
    }
}
