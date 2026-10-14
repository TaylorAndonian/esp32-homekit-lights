# Wiring Guide

![Schematic](../hardware/schematic.svg)


> **Do the low-voltage wiring and test everything first, with NO mains connected.**
> The relays click and their LEDs light up, so you can confirm the whole system works before any 120 V wire is involved.

## 1. ESP32 → relay modules

| ESP32 MiniKit pin | Relay 1 | Relay 2 |
|-------------------|---------|---------|
| VCC (5 V) | `+` / `VCC` | `+` / `VCC` |
| GND | `−` / `GND` | `−` / `GND` |
| IO18 | `S` / `IN` | — |
| IO19 | — | `S` / `IN` |

The MiniKit's **VCC** pin passes through the 5 V from USB. Don't use the 3.3 V pin for the relays, because the coils need 5 V.

## 2. Wall switches → ESP32 (low voltage)

Each switch has three screws: **COM** (usually the dark/black screw) and two **travelers**.

| Switch terminal | Goes to |
|-----------------|---------|
| SW1 COM | IO32 |
| SW1 traveler A | GND |
| SW1 traveler B | not connected |
| SW2 COM | IO33 |
| SW2 traveler A | GND |
| SW2 traveler B | not connected |

No resistors are needed because the firmware enables the ESP32's internal pull-ups.
The switch reads LOW in one position and HIGH in the other. **Every change toggles the light.**

> ⚠ These switch wires carry 3.3 V only. Never put a switch on mains and also on the ESP32.
> If you use real wall switches in a wall box, keep this low-voltage wiring in its own box,
> separate from any mains wiring.

## 3. Relay → light (mains side)

Each relay breaks the **hot (L)** wire to one light:

```
Hot (L) from breaker ──► Relay COM
Relay NO ──────────────► Light hot terminal
Light neutral ─────────► Neutral (N)
Relay NC ──────────────► (leave empty)
```

Using **NO** (normally open) means the light is OFF if the ESP32 loses power or reboots.

### Mains safety

- Switch the breaker OFF (or unplug the cord) before touching anything on the mains side.
- Put all relay modules in a **closed, non-conductive enclosure**, such as the printed one in [`hardware/enclosure/`](../hardware/enclosure/). The screw terminals and solder joints underneath are live.
- The Songle contacts are rated 10 A, but cheap module PCBs aren't. Stay **under ~5 A per channel** (a 600 W light is about 5 A at 120 V). That covers normal LED lamps easily.
- For anything wired into a building's walls, follow local electrical code. If you're unsure, have an electrician check it.

## 4. Power

Plug a 5 V, 1 A (or bigger) USB charger into the MiniKit. For a permanent build, an HLK-PM01 AC→5 V module can feed the VCC/GND pins instead. Fuse its input, and keep it in the same enclosure.
