/*
 * =====================================================================
 *  ESP32 HomeKit Lights
 *  Two relay-switched lights controlled from the Apple Home app,
 *  with a physical wall switch for each light.
 *
 *  Board:    MH-ET LIVE ESP32 MiniKit (ESP32-WROOM-32)
 *  Library:  HomeSpan (install from Arduino Library Manager)
 *
 *  Relays:   GPIO 18 (Light 1), GPIO 19 (Light 2)
 *  Switches: GPIO 32 (Light 1), GPIO 33 (Light 2)  -- see config.h
 *
 *  How the wall switches behave:
 *    Each switch is a regular two-position light switch. Flipping it in
 *    EITHER direction toggles the light, just like a 2-way (stairwell)
 *    circuit. That way the switch never "fights" the Home app: if Siri
 *    turned the light on, one flip of the wall switch turns it off.
 *
 *  Light state is saved to flash, so the lights come back the way they
 *  were after a power cut.
 * =====================================================================
 */

#include "HomeSpan.h"
#include "config.h"

// ---------------------------------------------------------------------
//  One light = one HomeKit LightBulb service + one relay + one switch
// ---------------------------------------------------------------------
struct RelayLight : Service::LightBulb {

  SpanCharacteristic *power;   // HomeKit "On" characteristic
  uint8_t relayPin;
  uint8_t switchPin;

  int      lastReading;        // last raw reading of the switch pin
  int      stableState;        // debounced switch position
  uint32_t lastChangeMs;       // when the raw reading last changed

  RelayLight(uint8_t relayPin, uint8_t switchPin)
      : Service::LightBulb(), relayPin(relayPin), switchPin(switchPin) {

    // 'true' = remember on/off state in flash across reboots
    power = new Characteristic::On(false, true);

    // Set the output level BEFORE enabling the pin, so the relay
    // doesn't click on for a moment at boot.
    writeRelay(power->getVal());
    pinMode(relayPin, OUTPUT);

    pinMode(switchPin, INPUT_PULLUP);
    lastReading  = digitalRead(switchPin);
    stableState  = lastReading;
    lastChangeMs = millis();

    Serial.printf("Light ready: relay GPIO %d, switch GPIO %d, state %s\n",
                  relayPin, switchPin, power->getVal() ? "ON" : "OFF");
  }

  // Called by HomeSpan when the Home app / Siri changes the light
  boolean update() override {
    bool on = power->getNewVal();
    writeRelay(on);
    Serial.printf("[HomeKit] GPIO %d -> %s\n", relayPin, on ? "ON" : "OFF");
    return true;
  }

  // Called by HomeSpan over and over; we use it to watch the wall switch
  void loop() override {
    int reading = digitalRead(switchPin);

    if (reading != lastReading) {          // pin moved: restart debounce timer
      lastReading  = reading;
      lastChangeMs = millis();
    }

    if (reading != stableState && millis() - lastChangeMs >= DEBOUNCE_MS) {
      stableState = reading;               // switch really changed position
      bool on = !power->getVal();          // toggle the light
      power->setVal(on);                   // tells the Home app too
      writeRelay(on);
      Serial.printf("[Switch]  GPIO %d -> %s\n", relayPin, on ? "ON" : "OFF");
    }
  }

  void writeRelay(bool on) {
    bool level = RELAY_ACTIVE_LOW ? !on : on;
    digitalWrite(relayPin, level ? HIGH : LOW);
  }
};

// ---------------------------------------------------------------------
void setup() {
  Serial.begin(115200);

  homeSpan.setStatusPin(STATUS_LED_PIN);
  homeSpan.setPairingCode(PAIRING_CODE);
  homeSpan.enableAutoStartAP();            // WiFi setup hotspot if no WiFi saved

  if (strlen(WIFI_SSID) > 0) {
    homeSpan.setWifiCredentials(WIFI_SSID, WIFI_PASSWORD);
  }

  homeSpan.begin(Category::Bridges, BRIDGE_NAME);

  // Accessory 1: the bridge itself (required first, no lights in it)
  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify();

  // Accessory 2: Light 1
  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify();
      new Characteristic::Name(LIGHT1_NAME);
    new RelayLight(RELAY1_PIN, SWITCH1_PIN);

  // Accessory 3: Light 2
  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify();
      new Characteristic::Name(LIGHT2_NAME);
    new RelayLight(RELAY2_PIN, SWITCH2_PIN);
}

void loop() {
  homeSpan.poll();
}
