# Marlin 1.1.x (MiniTree T3) customization analysis

## Upstream reference
- Upstream base tag: `Marlin 1.1.9.2` (commit `dd00f8b`).
- Local customization commits: `ba54e2d` (main firmware changes) and `c2181f1` (README update).
- Upstream project URL: https://github.com/MarlinFirmware/Marlin

## Major customization areas

### 1) Branding & versioning
- Custom author/splash branding, MiniTree URL, and bootscreen behavior changes in `Configuration.h`.
- Firmware version string, distribution date, and machine name rebranded in `Version.h`.
- README updated to describe MiniTree T3 firmware.

### 2) Hardware configuration (`Configuration.h`)
- Filament diameter set to 1.75mm and bed thermistor enabled.
- PID tuned for MiniTree hotend and bed; bed PID enabled.
- Thermal limits adjusted, including minimum/maximum temperatures and tighter residency windows.
- Endstops enabled with pullups and inverted logic; probe set as fixed-mounted with custom offsets/speeds.
- Motion limits customized (steps, acceleration, jerk); bed size reduced to 125×125×160.
- Auto bed leveling set to linear, filament runout enabled, EEPROM enabled, SD support and LCD controller enabled.
- Nozzle park enabled; soft endstops menu item enabled; encoder direction reversed.

### 3) Advanced configuration (`Configuration_adv.h`)
- Thermal protection timers/hysteresis adjusted for hotend/bed.
- Power-loss recovery enabled.
- Advanced pause / filament change parameters tuned for MiniTree (feedrates, lengths, timeouts) with continuous purge enabled.

### 4) EEPROM layout & persistent settings
- EEPROM version format customized (`M01`) with dynamic length.
- Added new persistent settings in `configuration_store.cpp` for:
  - Per-axis motor direction overrides.
  - Encoder direction setting.
  - Homing XY destination coordinates.
- Defaults added in `MarlinSettings::reset()` for new settings.

### 5) Motion / stepper behavior
- Planner adds new runtime fields for motor inversion, encoder direction, homing destination, and cold-extrusion flag.
- Stepper direction handling now uses planner inversion values, with a single-extruder override.
- Added helper methods to reset directions.

### 6) G-code & homing behavior
- Homing (G28) now re-enables bed leveling automatically.
- Z-safe homing moves to a custom planner-controlled XY destination instead of probe offsets.
- Added custom `X1` G-code for status reporting (JSON placeholder).
- M109/M190 LCD status shows filename while heating.

### 7) Temperature handling
- Cold extrusion allowed by default.
- Bed temperature reading clamps negative values to zero in the ADC path.
- Bed set-temperature clamps negative targets to zero.

### 8) LCD UI & language
- New settings menu added to LCD with items for motor direction, encoder direction, homing XY, cold-extrusion toggle, and EEPROM actions.
- Removed/altered preheat menu options (e.g., ABS removal).
- Encoder rotation direction tied to the planner setting rather than compile-time macros.
- Chinese LCD charset and UTF-8 mapping added (`MAPPER_HASHCN`) with extended glyph mapping.
- Chinese language strings heavily customized and new strings added for the new settings menu.

### 9) Display timing & fonts
- ST7920 delays adjusted for 16MHz.
- DOGM LCD print handling tweaked for UTF-8/Chinese font mapping.
- Custom bootscreen bitmap added (`_Bootscreen.h`).

### 10) Pins & IO
- RAMPS pin definitions adjusted (Y/Z max removed, filament runout pin set to 19).

### 11) Example configurations
- Large number of upstream `example_configurations` removed to reduce repository size.

## Files touched (non-exhaustive)
- `Marlin/Configuration.h`
- `Marlin/Configuration_adv.h`
- `Marlin/configuration_store.cpp`
- `Marlin/Marlin_main.cpp`
- `Marlin/planner.*`
- `Marlin/stepper.*`
- `Marlin/temperature.*`
- `Marlin/ultralcd.*`
- `Marlin/utf_mapper.h`
- `Marlin/language_zh_CN.h`
- `Marlin/_Bootscreen.h`
- `Marlin/pins_RAMPS.h`

