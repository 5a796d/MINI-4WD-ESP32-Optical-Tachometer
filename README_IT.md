# MINI4WD Tachimetro ottico ESP32 – Versione 1.0

Tachimetro ottico ad alta precisione basato su ESP32, progettato per misurare gli RPM in modo affidabile anche in ambienti elettricamente rumorosi.

Il progetto utilizza il contatore hardware PCNT dell’ESP32 e un sensore ottico a disco forato per misure stabili oltre i 50.000 RPM.

---

## 🔧 Caratteristiche principali

- Conteggio impulsi hardware (PCNT)
- Sensore ottico fotointerruttore
- Disco a 32 fori
- Testato oltre 50.000 RPM
- Logica di stabilità RPM
- Display OLED SSD1306 (I²C)
- Progetto resistente ai disturbi EMI
- Calibrazione di fabbrica tramite trimmer 10k (tarato a 7.5k come base di partenza)

---

## ⚙️ Specifiche tecniche

- MCU: ESP32  
- Frequenza CPU: **160 MHz**  
- Frequenza Flash: **80 MHz**  
- PSRAM: disabilitata  
- Metodo di misura: PCNT hardware  
- Sensore: fotointerruttore ottico  
- Display: OLED SSD1306 (I²C)  
- Alimentazione: 5 V (al pin 5V - NO USB)

---

## 🔌 Note hardware

- Uscita sensore collegata a **GPIO18**
- Resistenza serie da 330 Ω sul segnale
- Cavo coassiale consigliato (calza collegata a GND solo lato ESP32) - (esempio il cavo interno dell'antenna wifi dei notebook)
- Pull-up I²C da 4.7 kΩ
- Condensatore da 100 nF sui contatti del motore


---

## 🎯 Calibrazione

La calibrazione viene effettuata **una sola volta in fase di assemblaggio** tramite trimmer.

- Punto di calibrazione: ~70–80% del range operativo
- Precisione tipica dopo calibrazione: ±1–2%
- Errore massimo ammesso: ±3%

⚠️ Il trimmer **non deve essere regolato** durante l’uso normale.

---

## 📄 Documentazione

- Documentazione tecnica completa disponibile in formato PDF (IT / EN)
- Include architettura, mitigazione EMI, calibrazione e precisione

---

## 📌 Stato del progetto

**Versione 1.0 – Rilascio stabile**

- Hardware validato
- Disturbi EMI risolti
- Calibrazione di fabbrica definita
- Progetto completo

Eventuali nuove funzioni (peak-hold, logging, ecc.) saranno introdotte in Versione 1.1+

---

## 📜 Licenza

Questo progetto è rilasciato sotto licenza GPL.
