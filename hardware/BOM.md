# Bill of Materials

A spreadsheet version is in [`BOM.csv`](BOM.csv).

## Core parts

| Ref | Qty | Part | Spec | Connects to |
|-----|-----|------|------|-------------|
| U1 | 1 | **MH-ET LIVE ESP32 MiniKit** | ESP32-WROOM-32, WiFi | Controller |
| K1 | 1 | **Single relay module** | Songle SRD-05VDC-SL-C, 5 V coil, 10 A / 250 VAC contacts | GPIO 18 → Light 1 |
| K2 | 1 | **Single relay module** | Songle SRD-05VDC-SL-C, 5 V coil, 10 A / 250 VAC contacts | GPIO 19 → Light 2 |
| SW1 | 1 | **Single-pole 2-way switch** | SPDT light switch | GPIO 32 (low voltage) |
| SW2 | 1 | **Single-pole 2-way switch** | SPDT light switch | GPIO 33 (low voltage) |

## Wiring and power

| Ref | Qty | Part | Notes |
|-----|-----|------|-------|
| PS1 | 1 | 5 V USB supply, ≥ 1 A, plus micro-USB cable | Powers the ESP32 and both relay coils |
| W1 | 1 set | Dupont female–female jumpers | ESP32 ↔ relay modules |
| W2 | as needed | 22 AWG stranded hook-up wire | Switch runs (3.3 V signal only) |
| W3 | as needed | Lamp cord (SPT-2) or 14 AWG THHN | Mains side of the relays |
| J1 | 4 | Lever nuts (e.g. WAGO 221-412) | Mains splices |
| E1 | 1 | 3D-printed main box, 90 × 132 × 38 mm ([STEP](enclosure/main_switch_box.step)) | PETG or ASA |
| E2 | 1 | 3D-printed back plate, 109 × 151 × 13 mm ([STEP](enclosure/switch_box_back.step)) | PETG or ASA, 4 mounting ears |

## Optional (permanent install)

| Ref | Qty | Part | Notes |
|-----|-----|------|-------|
| PS2 | 1 | Hi-Link HLK-PM01 AC-DC module (5 V / 0.6 A) | Replaces the USB charger |
| F1 | 1 | Inline fuse holder + 5 A slow-blow fuse | On the hot wire feeding the relays |

## Power budget

| Load | Current @ 5 V |
|------|---------------|
| ESP32 (WiFi active, peaks) | ~250 mA |
| Relay coil × 2 (~72 mA each) | ~145 mA |
| Module LEDs | ~10 mA |
| **Total** | **~400 mA** → a 1 A supply has plenty of headroom |
