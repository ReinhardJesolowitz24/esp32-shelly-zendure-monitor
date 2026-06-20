// =====================================================================
//  Shelly Pro 3EM + Zendure SolarFlow — Monitor & Watchdog (ESP32 port)
//  Target board: ELECROW CrowPanel ESP32-S3, 7", 800x480 RGB IPS
// =====================================================================
//
//  WORK IN PROGRESS — placeholder.
//
//  This is the budget ESP32-S3 sibling of the Arduino GIGA R1 version:
//      https://github.com/ReinhardJesolowitz24/gigar1-shelly-zendure-monitor
//
//  The GIGA sketch is the reference implementation. The port plan:
//    - WiFi / HTTP client / JSON / control logic  -> ~1:1 (ESP32 WiFi.h)
//    - Display library: LovyanGFX (or Arduino_GFX) for the RGB parallel
//      panel (NOT TFT_eSPI). Colors stay RGB565.
//    - Layout coordinates: unchanged (panel is 800x480, same as the GIGA)
//    - Hardware watchdog: esp_task_wdt instead of mbed::Watchdog
//
//  Arduino IDE board settings (ELECROW, confirmed for the 7" HMI display):
//    - esp32 core by Espressif, version 2.0.3
//    - Board: "ESP32S3 Dev Module"
//    - PSRAM: OPI PSRAM ; Flash Size: 16MB ; Flash Mode: QIO 80MHz
//    - Partition: "Huge APP (3MB No OTA/1MB SPIFFS)"
//    - CPU: 240MHz (WiFi) ; Upload Speed: 921600
//    - Libraries: elecrow.com/download/product/ESP32_Display/Arduino_Libraries.zip
//
//  Step 1 on real hardware: flash ELECROW's factory example for this board
//  to show a test image (confirms panel timing + PSRAM), then drop in the
//  logic. To enter download mode: hold BOOT, press RESET, then upload.
//
//  Copy arduino_secrets.example.h -> arduino_secrets.h before building.
// =====================================================================

#include "arduino_secrets.h"

void setup() {
  Serial.begin(115200);
  // TODO: init display (Arduino_GFX/LovyanGFX), WiFi, watchdog, API server
}

void loop() {
  // TODO: fetch Shelly + Zendure, evaluate alarms, repaint, serve JSON API
}
