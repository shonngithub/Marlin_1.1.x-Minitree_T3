# Analysis commands log

```
$ rg -n "MACHINE_NAME|CUSTOM_MACHINE_NAME|MiniTree|T3" Marlin/Configuration.h Marlin/Version.h README.md
README.md:1:# 小树T3 3D打印机的定制固件
Marlin/Configuration.h:1:/** 小树T3
Marlin/Configuration.h:84:#define STRING_CONFIG_H_AUTHOR "(xenoxue, MiniTree V2.22)" // Who made the changes.
Marlin/Configuration.h:138://#define CUSTOM_MACHINE_NAME "3D Printer"
Marlin/Configuration.h:1290: *       For example, "G12 P1 S1 T3" will execute:
Marlin/Configuration.h:1300: *                           T1        T2        T3
Marlin/Configuration.h:1529:// PanelOne from T3P3 (via RAMPS 1.4 AUX2/AUX3)
Marlin/Version.h:38:  #define SHORT_BUILD_VERSION "MiniTreeFirmware v0.96 beta"
Marlin/Version.h:73:  #define MACHINE_NAME "MiniTree2"
```
