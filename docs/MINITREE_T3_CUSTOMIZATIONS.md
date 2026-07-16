# MiniTree T3 Customization Inventory

This document records the intentional behavior in the legacy `1.1.x` fork so
future Marlin upgrades can be checked against a stable list.

## Source Baselines

- Fork branch: `shonngithub/Marlin_1.1.x-Minitree_T3` `1.1.x`
- Fork tip: `c2181f137147d1974596647e161a3d4b6395bbe2`
- Main customization commit: `ba54e2d` (`minitree-T3`)
- Shared upstream base: `dd00f8b1a8448ff66ffe16d5ee04e5205c734145`
  (Marlin 1.1.9.2)
- Migration target: `MarlinFirmware/Marlin` `lts-2.1.2`
- Target tip used for this migration:
  `78d76552e5de49cbb4a9364d05f14e5f693e9000`

The fork also deletes most `Marlin/example_configurations` files. Those
deletions are repository-size cleanup, not printer behavior, and must not be
ported.

## Hardware Profile

| Area | Legacy value / behavior | Migration requirement |
| --- | --- | --- |
| MCU / board | ATmega2560, `BOARD_RAMPS_14_EFB` | Build with PlatformIO `mega2560` |
| Serial | Port 0, 250000 baud | Preserve |
| Extruder | One E0 extruder, 1.75 mm filament | Preserve |
| Drivers | Legacy defaults imply A4988-compatible step/dir drivers | Confirm actual installed drivers before changing driver type |
| Build volume | 125 x 125 x 160 mm | Preserve |
| Endstops | X/Y/Z home to MIN; active/inverting state is `true` | Preserve and bench-test before motion |
| Probe | Fixed probe on Z-MIN, offset X+26 Y+20 Z0 | Preserve X/Y; obtain actual Z offset from printer EEPROM or calibration |
| Runout | One sensor on RAMPS D19 (repurposed Z-MAX) | Preserve with an explicit pin override |
| Display | RepRapDiscount Full Graphic 12864 / ST7920 | Preserve |
| Storage | LCD SD card enabled | Preserve |

## Motion Settings

- Steps/mm: `{ 80, 80, 400, 90 }`.
- Max feedrate: `{ 300, 300, 5, 25 }` mm/s.
- Max acceleration: `{ 1000, 1000, 50, 1000 }`.
- Print acceleration: `1000`; retract and travel acceleration: `2000`.
- Legacy classic jerk: X/Y `5`, Z `0.3`, E `5`.
- Motor direction: X false, Y true, Z true, E0 true.
- Minimum software endstops enabled for X/Y only.
- Z minimum software endstop disabled.
- All maximum software endstops disabled.

The legacy firmware adds an LCD menu that changes X/Y/Z/E motor direction at
runtime and stores it in EEPROM. This bypasses Marlin's compile-time direction
configuration and rewrites E0 handling for a single-extruder-only machine.
This is high risk and is not a normal Marlin feature.

## Temperature Control

- Hotend and bed sensor type: `1`.
- Hotend min/max: `-20` / `265` C.
- Bed min/max: `-20` / `120` C.
- Hotend PID: Kp `24.71`, Ki `1.61`, Kd `94.64`.
- Bed PID: Kp `380.34`, Ki `66.65`, Kd `429.85`.
- Hotend output limit (`BANG_MAX` / PID max): `200`.
- Cold extrusion threshold: `185` C.
- Maximum single extrusion: `500` mm.
- Thermal runaway period/hysteresis: hotend `60 s / 5 C`, bed `90 s / 5 C`.
- Temperature wait windows are intentionally short and broad.

The legacy source initializes `allow_cold_extrude` to true and clamps negative
bed readings to zero. Both changes weaken safety behavior and must not be
ported automatically. Use standard Marlin protection unless hardware testing
proves a documented need.

## Bed Leveling And Homing

- `FIX_MOUNTED_PROBE`.
- `AUTO_BED_LEVELING_LINEAR`, legacy 3 x 3 grid.
- Probe margin: 15 mm.
- XY probing feedrate: 1000 mm/min.
- Probe offset: `{ 26, 20, 0 }`.
- Legacy code forces leveling on after every G28.
- Legacy code adds EEPROM-backed X/Y coordinates for Z safe homing, defaulting
  to X10/Y10, but `Z_SAFE_HOMING` is disabled in the shipped configuration.

For Marlin 2.1.2, use the native leveling options. Do not carry the old G28
source patch. The desired behavior maps to `ENABLE_LEVELING_AFTER_G28` or
`RESTORE_LEVELING_AFTER_G28`, subject to printer testing.

## Filament Change

- Filament runout invokes `M600`.
- Advanced Pause is enabled.
- Unload length: 50 mm at 10 mm/s.
- Slow load: 40 mm at 5 mm/s.
- Fast load: 0 mm at 5 mm/s, acceleration 15 mm/s2.
- Continuous purge enabled; automatic purge length 0.
- Unload purge retract/delay/purge: 3 mm / 2000 ms / 0 mm.
- Nozzle timeout: 300 seconds.
- Nozzle park point: X10, Y105, Z20.
- `PARK_HEAD_ON_PAUSE` is disabled.

The old `PAUSE_PARK_NO_STEPPER_TIMEOUT 500` is an invalid value for a boolean
option and should be migrated as a plain enable/disable decision.

## SD And Power-Loss Recovery

- SD support enabled on the LCD connection.
- Power-loss recovery enabled without a dedicated power-loss input pin.
- Legacy behavior stores recovery data on SD.

This feature must be tested for SD wear, write reliability, and successful
resume on the actual controller before being considered complete.

## LCD, Language, And Branding

- Simplified Chinese is selected.
- The old fork adds a custom UTF-8 lookup table, custom Chinese glyph data,
  menu translations, and slower ST7920 timing.
- It adds a top-level settings menu for motor direction, encoder direction,
  homing coordinates, cold extrusion, soft endstops, and EEPROM actions.
- It hides the ABS preheat entry and exposes nozzle-only preheat.
- It shows the current SD filename while waiting for hotend or bed heat.
- A custom bootscreen exists, but the shipped configuration does not enable it.
- Legacy branding is inconsistent (`T3`, `MiniTree2`, `MiniTree V2.22`,
  `v0.96 beta`). New branding should consistently use `MiniTree T3`.

Marlin 2.1.2 has a different LCD and localization architecture and already
contains native Simplified Chinese font pages. Port the required labels and
behavior to the current menu APIs; do not copy old font and UTF mapper files.

## EEPROM And Custom Source Features

The legacy EEPROM version is `M01` and stores three extra groups:

1. Runtime motor direction.
2. Runtime encoder direction.
3. X/Y homing destination.

Marlin 2.1.2 uses a different settings layout. Old EEPROM bytes are not
binary-compatible. The migration must start with factory defaults and use
`M502`, then `M500`, after recording any calibration values needed from the old
printer.

Additional old source changes:

- `X1` command: returns an M105-like heater state for a Wi-Fi module. Its
  comment claims JSON, but the implementation does not produce JSON.
- Heating status messages include the active SD filename.
- LCD "set home offsets" automatically runs `M500` and `M501`.
- Runtime encoder direction is stored in EEPROM.
- ST7920 delays are set to 125 ns for all three timing slots.

## Safety Decisions For This Migration

The following legacy changes are documented but intentionally not ported
without hardware evidence:

- Default cold extrusion allowed.
- Negative bed temperature clamped to zero.
- Runtime motor-direction editing from the LCD.
- Disabling all maximum software endstops.
- Custom EEPROM binary layout.
- The custom `X1` protocol without a captured client-side specification.

They remain open verification items in the migration checklist.
