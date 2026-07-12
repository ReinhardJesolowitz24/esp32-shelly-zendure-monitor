// Copy this file to "arduino_secrets.h" and fill in your own values.
// arduino_secrets.h is git-ignored, so your credentials are never committed.

#define SECRET_SSID        "DEIN_WLAN_NAME"
#define SECRET_PASS        "DEIN_WLAN_PASSWORT"

// Local IPs of your devices (give them fixed IPs via DHCP reservation).
#define SECRET_SHELLY_HOST "192.168.1.50"   // Shelly Pro 3EM
#define SECRET_ZEN_HOST    "192.168.1.51"   // Zendure SolarFlow

// Optional -- only needed if CONTROL_WATCH_ENABLE is set to 1 in the sketch.
// IPs of the local zero-feed-in controller pair (regler + MQTT broker).
#define SECRET_REGLER_HOST "192.168.1.52"   // Regler (controller)
#define SECRET_BROKER_HOST "192.168.1.53"   // MQTT broker
