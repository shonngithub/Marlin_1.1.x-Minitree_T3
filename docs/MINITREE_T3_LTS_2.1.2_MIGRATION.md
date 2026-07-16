# MiniTree T3 Migration To Marlin lts-2.1.2

Status values:

- `DONE`: implemented and statically verified.
- `BUILD`: implemented but requires a successful firmware build.
- `HARDWARE`: requires testing on the physical printer.
- `HOLD`: intentionally not ported pending evidence.

## Current Verification

The migrated configuration compiled successfully on July 16, 2026:

```text
python -m platformio run -e mega2560
RAM:   65.6% (5374 / 8192 bytes)
Flash: 67.8% (172194 / 253952 bytes)
```

This is a compile and static-configuration result, not a claim that the
printer is safe to operate without the hardware checks below.

## Migration Matrix

| ID | Customization | Marlin 2.1.2 approach | Status |
| --- | --- | --- | --- |
| CFG-01 | RAMPS 1.4 EFB / Mega2560 | `BOARD_RAMPS_14_EFB`, PlatformIO `mega2560` | BUILD |
| CFG-02 | 125 x 125 x 160 volume | Set bed and Z limits | BUILD |
| CFG-03 | Steps, rates, acceleration, direction | Port configuration values; enable classic jerk | BUILD |
| CFG-04 | X/Y/Z MIN endstop polarity | Port and verify with `M119` before homing | HARDWARE |
| CFG-05 | Fixed Z probe, X+26/Y+20 | `FIX_MOUNTED_PROBE`, `NOZZLE_TO_PROBE_OFFSET` | HARDWARE |
| CFG-06 | Linear auto bed leveling | `AUTO_BED_LEVELING_LINEAR`, 3 x 3 grid | HARDWARE |
| CFG-07 | Leveling enabled after G28 | Native `ENABLE_LEVELING_AFTER_G28`; no source patch | HARDWARE |
| CFG-08 | Runout sensor on D19 | Pin override plus `FILAMENT_RUNOUT_SENSOR` | HARDWARE |
| CFG-09 | M600 / advanced pause | Port current unload/load/purge values | HARDWARE |
| CFG-10 | SD and power-loss recovery | LCD SD connection, `POWER_LOSS_RECOVERY` | HARDWARE |
| CFG-11 | Full Graphic ST7920 LCD | Native controller option; preserve conservative delays | HARDWARE |
| CFG-12 | Simplified Chinese UI | Native `LCD_LANGUAGE zh_CN` and Marlin 2 font pages | BUILD |
| CFG-13 | PID and temperature limits | Port values, then retune PID on hardware | HARDWARE |
| CFG-14 | EEPROM settings | Native Marlin settings; reset old EEPROM layout | HARDWARE |
| UI-01 | Runtime motor direction menu | Do not port; use compile-time direction | HOLD |
| UI-02 | Runtime encoder direction | Use compile-time `REVERSE_ENCODER_DIRECTION` | DONE |
| UI-03 | Editable Z-home XY point | Use fixed safe-homing point initially | HOLD |
| UI-04 | Cold extrusion toggle | Keep native safety behavior and M302 support | DONE |
| UI-05 | Chinese custom menu wording | Use upstream translations first | BUILD |
| SRC-01 | X1 Wi-Fi status command | Requires Wi-Fi protocol/client capture | HOLD |
| SRC-02 | Filename during M109/M190 | Optional UI enhancement after core migration | HOLD |
| SRC-03 | Negative bed reading clamp | Do not port | DONE |
| SRC-04 | Custom EEPROM `M01` layout | Do not port; incompatible with 2.1.2 | DONE |
| BRAND-01 | MiniTree T3 identity | Consistent author/name/website strings | BUILD |

## Required Hardware Validation

Perform these checks in order. Keep heaters disconnected for the first motion
checks where practical.

1. Run `M115` and confirm the expected build identity.
2. Run `M119`; manually trigger X, Y, Z, probe, and filament switches.
3. Jog each axis 1 mm in the positive direction. Power off immediately if any
   axis moves incorrectly.
4. Home X and Y individually, then Z with the probe.
5. Confirm physical travel limits and decide whether maximum software
   endstops can be safely enabled.
6. Set and save the real probe Z offset with `M851` and `M500`.
7. Run hotend and bed PID autotune; compare results with the legacy values.
8. Test thermal runaway and sensor-disconnect behavior.
9. Test `G29`, save leveling data if applicable, and verify post-G28 leveling.
10. Test runout-triggered `M600`, park location, load/unload, timeout, and resume.
11. Test SD printing, long Chinese filenames, and LCD encoder direction.
12. Test power interruption and recovery using a disposable print.

## EEPROM Upgrade Procedure

Before flashing, record legacy values with `M503`, especially:

- Steps/mm.
- PID values.
- Probe Z offset.
- Home offsets.
- Any manually tuned acceleration or feedrate values.

After flashing Marlin 2.1.2:

```text
M502
M500
M503
```

Then restore only confirmed calibration values with current Marlin commands.
Do not attempt to reuse or decode the legacy `M01` EEPROM structure in place.

## Deferred Compatibility Questions

- What hardware or software consumes the old `X1` command?
- Is runtime motor-direction editing actually used in the field?
- What is the calibrated probe Z offset currently stored in the printer?
- Does the bed thermistor legitimately report below 0 C, or was the old clamp
  masking a wiring fault?
- Is power-loss recovery dependable with the current SD card and power supply?
- Should maximum software endstops remain disabled after travel measurement?
