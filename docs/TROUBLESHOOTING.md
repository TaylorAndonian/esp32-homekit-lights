# Troubleshooting

## Relay behavior

| Symptom | Fix |
|---------|-----|
| Light is ON when the Home app says OFF (inverted) | Your module is "low-level trigger". Set `RELAY_ACTIVE_LOW true` in `config.h` and re-upload. |
| Relay clicks on but never turns off (active-low module) | The 3.3 V HIGH from the ESP32 isn't high enough to fully shut off a 5 V opto input. Fixes: use a module with an `S/+/−` transistor input (active-high), or remove the `JD-VCC` jumper and power the opto side from 3.3 V. |
| Relay LED lights but no click | The coil isn't getting 5 V. Check that the relay `+` goes to **VCC (5 V)**, not 3V3. |
| Relays chatter when WiFi connects | The power supply is too weak. Use a 1 A+ charger and a short, good USB cable. |

## Wall switches

| Symptom | Fix |
|---------|-----|
| Flipping the switch does nothing | Check that COM goes to IO32/IO33 and one traveler goes to GND. Open the Serial Monitor; each flip should print `[Switch] ...`. |
| One flip toggles twice | Increase `DEBOUNCE_MS` in `config.h` (try 100). |
| Light toggles randomly | The switch wire run is long and picking up noise. Use twisted pair or shielded wire, or add a 0.1 µF capacitor from the input pin to GND. |

## HomeKit

| Symptom | Fix |
|---------|-----|
| iPhone can't find the accessory | The iPhone and ESP32 must be on the **same 2.4 GHz WiFi**. The ESP32 can't join 5 GHz-only networks. |
| "Accessory already added" / won't re-pair | In the Serial Monitor, type `U` (unpair) and press Enter. Then add it again in the Home app. |
| Shows "No Response" | The ESP32 is off WiFi. Check the Serial Monitor. Type `W` to re-enter WiFi credentials. |
| Want to change WiFi without re-flashing | Type `W` in the Serial Monitor, or erase all settings with `E` and use the setup hotspot. |
| Want to start completely fresh | Type `F` (factory reset) in the Serial Monitor. |

HomeSpan's Serial Monitor runs at **115200 baud**. Type `?` to list every command.
