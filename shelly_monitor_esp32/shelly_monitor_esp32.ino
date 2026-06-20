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
//    - Display library: Arduino_GFX or LovyanGFX for the RGB parallel
//      panel (NOT TFT_eSPI). Adafruit-GFX-compatible, so the drawing
//      helpers port with renamed calls; colors stay RGB565.
//    - Layout coordinates: unchanged (panel is 800x480, same as the GIGA)
//    - Hardware watchdog: esp_task_wdt instead of mbed::Watchdog
//    - Enable PSRAM in the board config (framebuffer ~768 KB)
//
//  Step 1 on real hardware: get ELECROW's example for this board to show
//  a test image (confirms panel timing + PSRAM), then drop in the logic.
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
