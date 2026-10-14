// =====================================================================
//  config.h  —  everything you might want to change lives here
// =====================================================================
#pragma once

// ---------- Relay outputs (to the relay modules' IN / S pin) ----------
#define RELAY1_PIN        18      // Light 1
#define RELAY2_PIN        19      // Light 2

// Most single "S / + / -" Songle modules switch ON with a HIGH signal.
// Modules marked "low level trigger" (pins IN / VCC / GND) switch ON with LOW.
// If your light is ON when HomeKit says OFF, flip this.
#define RELAY_ACTIVE_LOW  false

// ---------- Wall switch inputs (low-voltage only, switch to GND) -------
#define SWITCH1_PIN       32      // Wall switch for Light 1
#define SWITCH2_PIN       33      // Wall switch for Light 2

// Debounce time for the wall switches, in milliseconds.
#define DEBOUNCE_MS       50

// ---------- Names shown in the Apple Home app ----------
#define BRIDGE_NAME       "ESP32 Lights"
#define LIGHT1_NAME       "Light 1"
#define LIGHT2_NAME       "Light 2"

// ---------- HomeKit pairing code ----------
// 8 digits, entered in the Home app as XXX-XX-XXX.
// Apple rejects "easy" codes like 12345678 or 11111111.
#define PAIRING_CODE      "46637726"   // shows in Home as 466-37-726

// ---------- Status LED ----------
// The MH-ET LIVE MiniKit's onboard blue LED is on GPIO 2.
#define STATUS_LED_PIN    2

// ---------- WiFi (optional) ----------
// Leave these empty and set WiFi over USB serial instead (type 'W' in the
// Serial Monitor) or join the "HomeSpan-Setup" hotspot on first boot.
// Never commit real credentials to GitHub.
#define WIFI_SSID         ""
#define WIFI_PASSWORD     ""
