# Flash-Checkliste — ELECROW 7″ HMI ESP32-S3 Monitor

Abhaken von oben nach unten. Geschätzte Zeit: 20–30 min beim ersten Mal.

---

## 0. Modul-Etikett mit der Lupe lesen (vor allem anderen)

Auf dem silbernen Metallschild des WLAN-Moduls steht die genaue Variante:

```
ESP32-S3-WROOM-1-N16R8     <- 16 MB Flash, 8 MB PSRAM
ESP32-S3-WROOM-1-N4R8      <-  4 MB Flash, 8 MB PSRAM
```

- [ ] Variante notiert: __________________  (→ bestimmt die „Flash Size" in Schritt 3)
- Falls der Suffix (`-N16R8` / `-N4R8`) **fehlt**: kein Problem, der Sketch zeigt
  Flash + PSRAM beim ersten Boot selbst an (Schritt 6).

---

## 1. Arduino IDE vorbereiten (einmalig)

- [ ] In **File → Preferences → Additional Boards Manager URLs** eintragen:
      `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
- [ ] **Tools → Board → Boards Manager** → „esp32" suchen →
      **esp32 by Espressif, Version 2.0.3** installieren
- [ ] **LovyanGFX 1.1.12** über den Library Manager installieren
      (**1.2.x meiden** — kompiliert nicht auf Core 2.0.3; 1.1.9/1.1.12 sind die 2.0.3-Versionen)
- [ ] **ArduinoJson** (>= 7.x) über den Library Manager installieren

---

## 2. Projekt vorbereiten

- [ ] `shelly_monitor_esp32/arduino_secrets.example.h` →
      kopieren nach `shelly_monitor_esp32/arduino_secrets.h`
- [ ] In `arduino_secrets.h` eintragen:
  - [ ] `SECRET_SSID`        = WLAN-Name
  - [ ] `SECRET_PASS`        = WLAN-Passwort
  - [ ] `SECRET_SHELLY_HOST` = lokale IP des Shelly Pro 3EM
  - [ ] `SECRET_ZEN_HOST`    = lokale IP des Zendure
- [ ] `shelly_monitor_esp32/shelly_monitor_esp32.ino` in der Arduino IDE öffnen

---

## 3. Board-Einstellungen (Tools-Menü)

- [ ] Board: **ESP32S3 Dev Module**
- [ ] PSRAM: **OPI PSRAM**
- [ ] Flash Size: **16MB** (bei N16R8) — oder **4MB** (bei N4R8)
- [ ] Flash Mode: **QIO 80MHz**
- [ ] Partition Scheme: **Huge APP (3MB No OTA/1MB SPIFFS)**
- [ ] CPU Frequency: **240MHz (WiFi)**
- [ ] Upload Speed: **921600**
- [ ] USB CDC On Boot: **Disabled** (Serial läuft über den UART-Brücken-Chip)

---

## 4. Board anschließen & Port wählen

- [ ] Board per USB-C an den PC
- [ ] **Tools → Port** → den neuen COM-Port wählen
- [ ] (Optional) **Tools → Get Board Info** → bestätigt, dass das Board erkannt wird

---

## 5. Hochladen

- [ ] **Verify/Compile** (Häkchen) — muss fehlerfrei durchlaufen
- [ ] **Upload** (Pfeil)
- [ ] Falls der Upload nicht startet / „Connecting…" hängt:
      **BOOT gedrückt halten**, kurz **RESET** drücken, BOOT loslassen → erneut Upload.
      (Serial Monitor zeigt dann `waiting for download`.)
- [ ] Nach „Done uploading" einmal **RESET** drücken

---

## 6. Erster Boot prüfen

- [ ] Display zeigt kurz **„ESP32-S3 Monitor boot"** + **„Flash X MB / PSRAM Y MB"**
  - PSRAM-Zeile **grün** = PSRAM aktiv ✓   ·   **rot** = PSRAM fehlt → Schritt 3 prüfen (OPI PSRAM!)
  - Flash-Wert mit dem Etikett aus Schritt 0 vergleichen
- [ ] Danach erscheint das Dashboard + **„Verbinde mit WLAN…"**
- [ ] Bei Erfolg: **„WLAN verbunden  192.168.x.x"** (diese IP notieren — das ist die API-Adresse)
- [ ] Serial Monitor (115200 Baud) zeigt dieselben Infos + `Watchdog aktiv, Timeout 120 s`

---

## 7. Funktion prüfen

- [ ] Netz-Gesamtwert + Phasen L1/L2/L3 plausibel
- [ ] Zendure-Zeile zeigt SoC / Abgabe (oder „API haengt" / „OFFLINE")
- [ ] Grüner Heartbeat-Punkt blinkt im Sekundentakt
- [ ] JSON-API im Browser testen: `http://<board-ip>/status`
- [ ] Im `/status` die neuen Diagnose-Felder prüfen: `boots` (Boot-Zähler),
      `base_restored` (Tagessaldo aus NVS wiederhergestellt?), `min_free_heap`, `rssi`

---

> 💾 **Tagessaldo-Persistenz (ab v1.1):** Der Tagessaldo liegt im NVS und übersteht
> Reboots/Stromausfall — nach einem Neustart am selben Tag läuft er weiter
> (`base_restored:true` im `/status`) statt auf 0 zu springen. Kein extra Flash-Schritt
> nötig; die Baseline wird nur ~1×/Tag geschrieben (Flash-Verschleiß vernachlässigbar).

---

## Troubleshooting

| Symptom | Wahrscheinliche Ursache / Lösung |
|---|---|
| Display bleibt schwarz | Backlight/Init — Board-Settings prüfen; war Compile wirklich für S3? |
| Bild flackert / verschoben / Farbsäume / Streifen rechts | Panel-Timing einer anderen Charge → LovyanGFX-Porches im Sketch anpassen (hsync/vsync front/back porch, `pclk_idle_high`) |
| PSRAM-Zeile rot | „OPI PSRAM" nicht gewählt (Schritt 3) |
| Compile-Fehler `arduino_secrets.h not found` | Schritt 2 vergessen |
| Compile-Fehler bei `LovyanGFX` | zu neue Version (1.2.x) auf Core 2.0.3 → **1.1.12** nehmen |
| Compile-Fehler bei `ledcSetup`/`esp_task_wdt_init` | Core ist nicht 2.0.3 → Schritt 1 prüfen |
| Hängt in „Verbinde mit WLAN…" | SSID/Passwort in `arduino_secrets.h` falsch; 2,4-GHz-WLAN nötig (kein 5 GHz) |
| „Shelly-Fehler!" | falsche Shelly-IP, oder Shelly nicht im selben Netz |

---

*Wenn alles läuft: Foto vom Display machen → dann erst GitHub-Repo anlegen & pushen.*
