// =====================================================================
//  Shelly Pro 3EM + Zendure SolarFlow — Monitor & Watchdog (ESP32 port)
//  Target board: ELECROW CrowPanel ESP32-S3, 7", 800x480 RGB IPS
// =====================================================================
//
//  WORK IN PROGRESS — display scaffold ready, monitor logic still to port.
//
//  Budget ESP32-S3 sibling of the Arduino GIGA R1 version:
//      https://github.com/ReinhardJesolowitz24/gigar1-shelly-zendure-monitor
//  The GIGA sketch is the reference implementation. Port plan:
//    - WiFi / HTTP client / JSON / control logic  -> ~1:1 (ESP32 WiFi.h)
//    - Display: Arduino_GFX direct (NO LVGL needed). Its Adafruit-GFX API
//      (fillScreen/setCursor/setTextSize/print/fillRect/...) matches the
//      GIGA helpers, so the drawing code ports nearly verbatim. RGB565.
//    - Layout coordinates unchanged (panel is 800x480, same as the GIGA)
//    - Hardware watchdog: esp_task_wdt instead of mbed::Watchdog
//
//  Pin map + RGB timing below are taken VERBATIM from ELECROW's official
//  7.0" factory program (LvglWidgets-LVGL-7.0), so they are known-good for
//  this exact board. Touch (GT911, I2C SCL=20/SDA=19) is unused here.
//
//  Arduino IDE board settings (ELECROW, confirmed for the 7" HMI display):
//    - esp32 core by Espressif, version 2.0.3
//    - Board: "ESP32S3 Dev Module"
//    - PSRAM: OPI PSRAM ; Flash Mode: QIO 80MHz
//    - Flash Size: depends on the WROOM-1 variant printed on the shield:
//      N16R8 -> 16MB (PDF default) ; N4R8 -> 4MB. PSRAM is 8MB either way.
//    - Partition: "Huge APP (3MB No OTA/1MB SPIFFS)"
//    - CPU: 240MHz (WiFi) ; Upload Speed: 921600
//    - Library: Arduino_GFX (from ELECROW's Arduino_Libraries.zip)
//    - Download mode if needed: hold BOOT, press RESET, then upload.
//
//  Copy arduino_secrets.example.h -> arduino_secrets.h before building.
// =====================================================================

#include "arduino_secrets.h"
#include <Arduino_GFX_Library.h>

// ---- Backlight ------------------------------------------------------
#define TFT_BL 2

// ---- RGB parallel panel: data + sync pins (from factory program) ----
Arduino_ESP32RGBPanel *rgbpanel = new Arduino_ESP32RGBPanel(
  GFX_NOT_DEFINED /* CS */, GFX_NOT_DEFINED /* SCK */, GFX_NOT_DEFINED /* SDA */,
  41 /* DE */, 40 /* VSYNC */, 39 /* HSYNC */, 0 /* PCLK */,
  14 /* R0 */, 21 /* R1 */, 47 /* R2 */, 48 /* R3 */, 45 /* R4 */,
  9  /* G0 */, 46 /* G1 */, 3  /* G2 */, 8  /* G3 */, 16 /* G4 */, 1 /* G5 */,
  15 /* B0 */, 7  /* B1 */, 6  /* B2 */, 5  /* B3 */, 4  /* B4 */
);

// ---- 7" 800x480 panel: resolution + timing (from factory program) ---
Arduino_RPi_DPI_RGBPanel *gfx = new Arduino_RPi_DPI_RGBPanel(
  rgbpanel,
  800 /* width  */, 0 /* hsync_polarity */, 210 /* hsync_front_porch */, 1 /* hsync_pulse_width */, 46 /* hsync_back_porch */,
  480 /* height */, 0 /* vsync_polarity */, 22  /* vsync_front_porch */, 1 /* vsync_pulse_width */, 23 /* vsync_back_porch */,
  0 /* pclk_active_neg */, 16000000 /* prefer_speed */, true /* auto_flush */
);

static void backlightOn() {
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, HIGH);
  ledcSetup(1, 300, 8);
  ledcAttachPin(TFT_BL, 1);
  ledcWrite(1, 255);              // brightness 0..255
}

void setup() {
  Serial.begin(115200);
  Serial.println("Shelly/Zendure monitor (ESP32-S3) booting...");

  gfx->begin();
  backlightOn();

  // --- Step 1 smoke test: confirm panel timing + PSRAM are OK ---
  gfx->fillScreen(RED);    delay(400);
  gfx->fillScreen(GREEN);  delay(400);
  gfx->fillScreen(BLUE);   delay(400);
  gfx->fillScreen(BLACK);
  gfx->setTextColor(WHITE);
  gfx->setTextSize(3);
  gfx->setCursor(20, 20);
  gfx->print("Monitor boot OK");

  // TODO: connectWiFi(), start API server, init esp_task_wdt watchdog
}

void loop() {
  // TODO: fetch Shelly + Zendure, evaluate alarms, repaint, serve JSON API
}
