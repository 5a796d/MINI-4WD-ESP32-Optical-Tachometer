# MINI 4WD ESP32 Optical Tachometer – Version 1.0 

High-precision optical tachometer based on ESP32, designed for reliable RPM measurement even in electrically noisy environments.

This project uses the ESP32 hardware pulse counter (PCNT) and an optical slotted disk sensor to measure rotational speed up to and beyond 50,000 RPM.

---

## 🔧 Key Features

- Hardware pulse counting (PCNT)
- Optical photointerrupter sensor
- 32-slot disk support
- Tested beyond 50,000 RPM
- Stable RPM detection logic
- OLED display (SSD1306, I²C)
- EMI-hardened design
- Factory calibration via trimmer (calibrated at 7.5k as a starting point)

---

## ⚙️ Technical Specifications

- MCU: ESP32  
- CPU frequency: **160 MHz**  
- Flash frequency: **80 MHz**  
- PSRAM: disabled  
- Measurement method: hardware PCNT  
- Sensor: optical photointerrupter  
- Display: SSD1306 OLED (I²C)  
- Power supply: 5 V (on 5V Pin - NO USB)

---

## 🔌 Hardware Notes

- Sensor output connected to **GPIO18**
- 330 Ω series resistor on signal line
- Coaxial cable recommended (shield connected to GND on ESP32 side only) - (example the internal cable of the notebook wifi antenna)
- 4.7 kΩ pull-ups on I²C lines
- 100 nF capacitor across motor terminals


---

## 🎯 Calibration

Calibration is performed **once during factory setup** using a trimmer.

- Calibration point: ~70–80% of operating RPM range
- Typical accuracy after calibration: ±1–2%
- Maximum acceptable error: ±3%

⚠️ The trimmer must **not** be adjusted during normal operation.

---

## 📄 Documentation

- Full technical documentation is available in PDF format (IT / EN)
- Includes architecture, EMI mitigation, calibration and accuracy notes

---

## 📌 Project Status

**Version 1.0 – Stable release**

- Hardware validated
- EMI issues resolved
- Factory calibration defined
- Feature-complete

Future enhancements (logging, peak-hold, etc.) will be released as Version 1.1+

---

## 📜 License

This project is released under the GPL License.
