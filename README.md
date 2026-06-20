# ESP32 — Shelly Pro 3EM + Zendure SolarFlow Monitor & Watchdog

> ⚠️ **Work in progress** — budget ESP32-S3 port of
> [gigar1-shelly-zendure-monitor](https://github.com/ReinhardJesolowitz24/gigar1-shelly-zendure-monitor).
> Code port follows once the hardware is in hand.

An **independent**, cloud-free monitor and safety watchdog for a home battery setup,
running on an **ESP32-S3** with an 800×480 display. It reads a **Shelly Pro 3EM** (grid
meter) and a **Zendure SolarFlow** battery **read-only** over their local HTTP APIs,
shows live data and a daily energy balance, raises a visible alarm on misbehaviour, and
serves its own JSON API.

This is the cheaper sibling of the Arduino GIGA R1 version — same features, ~1/3 the cost.

## Hardware

- **ELECROW CrowPanel ESP32-S3, 7″, 800×480 IPS** (RGB parallel panel, GT911 touch, PSRAM)
  - 800×480 — **same resolution as the GIGA display**, so the layout carries over 1:1
- Shelly Pro 3EM (3-phase grid meter, on the LAN)
- Zendure SolarFlow (e.g. 2400 / 2400 Pro, on the LAN via WiFi)

## Libraries

- **WiFi** (ESP32 Arduino core) — native; `WiFiClient` / `WiFiServer`
- **ArduinoJson** (>= 7.x)
- **Arduino_GFX** (`GFX_Library_for_Arduino`) *or* LovyanGFX — for the RGB parallel panel
  (NOT TFT_eSPI; that is for SPI displays)
- `esp_task_wdt` (ESP-IDF, built in) — hardware task watchdog

> RGB panels need correct timing parameters (hsync/vsync/pclk/porches). Start from
> ELECROW's working example for this board, confirm it shows a test image, then drop in
> the monitor logic.

## Features (ported from the GIGA version)

- Live grid power: total + per phase L1/L2/L3 (W / V / A)
- Zendure status (read-only): SoC, output, acStatus — incl. "API hung / OFFLINE"
- Daily energy balance [kWh] since midnight (auto-reset)
- Watchdog/alarm: grid-dumping, deep discharge, BMS-critical (independent cell-V/temp
  check), debounced against device-reboot transients
- Device health (Shelly/Zendure: ok / hung / offline)
- Heartbeat + hardware watchdog (self-supervision), robust WiFi reconnect
- JSON API: `/status`, `/balance` (cell-balancing history), `/daily` (30-day diary)
- Own IP shown on the display

## Setup

1. Copy `shelly_monitor_esp32/arduino_secrets.example.h` →
   `shelly_monitor_esp32/arduino_secrets.h`
2. Fill in **all four** values: WiFi SSID/password + local IPs of the Shelly and Zendure.
   Give each device (and this board) a fixed IP (DHCP reservation) so addresses stay stable.
3. Arduino IDE: select the ESP32-S3 board, **enable PSRAM**, set the correct flash size,
   install the libraries above, upload.

`arduino_secrets.h` is git-ignored — credentials are never committed.

## ⚠️ Disclaimer

Read-only monitor for display purposes, **not** a certified safety device. The real cell
protection is the battery's own BMS. **Use at your own risk.**

## License

[MIT](LICENSE) — Copyright (c) 2026 Reinhard Jesolowitz
