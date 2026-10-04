# MiniTree T3 迁移到 Marlin lts-2.1.2 的逐项审计

## 1. 审计结论

当前分支已经完成 MiniTree T3 核心打印功能向 Marlin `lts-2.1.2` 的配置迁移，
但不能表述为“旧版所有源码修改都已原样移植”。

核对结果分为五类：

- **已移植**：旧功能在新版中保留，并使用对应配置或代码实现。
- **原生替代**：不复制旧模块，改用 Marlin 2.1.2 的标准实现。
- **安全修正**：旧行为存在安全问题或配置错误，新版有意采用不同实现。
- **无需移植**：旧改动不产生运行行为，或旧配置中实际未启用。
- **未移植**：协议不明、风险过高或仍需确认是否真的需要。

因此，核心运动、温控、调平、断料、M600、SD、掉电恢复、中文屏和 EEPROM
能力已经进入新分支；历史 `X1`、运行时电机方向、私有 EEPROM、加热时附加
文件名等源码扩展没有全部复制。所有差异都在本文中明确登记。

## 2. 当前基线与验证

- 迁移分支：`codex/minitree-t3-lts-2.1.2-migration`
- 上游目标提交：`78d76552e5de49cbb4a9364d05f14e5f693e9000`
- 旧版对照提交：`c2181f137147d1974596647e161a3d4b6395bbe2`
- 固件标识：`2.1.2.8-MiniTree-T3`
- 构建环境：PlatformIO `mega2560`

最近一次完整构建结果：

```text
python -m platformio run -e mega2560
RAM:   65.6% (5374 / 8192 bytes)
Flash: 67.8% (172064 / 253952 bytes)
```

环境安装、配置入口、构建命令、二进制包、源码包和 SHA-256 的完整流程见
[`MiniTree_T3_构建与发布打包指南.md`](MiniTree_T3_构建与发布打包指南.md)。

## 2.1 已读取的旧固件现场参数

已通过真机 `COM6`、`250000` 波特率、`8N1`、无流控读取旧固件参数。当前设备运行的不是迁移版，而是旧版：

```text
FIRMWARE_NAME: Marlin MiniTreeFirmware v0.96 beta
based on Marlin 1.0.9
MACHINE_TYPE: MiniTree2
Last Updated: 2021-03-05
Compiled: May 4 2021
M01 stored settings retrieved (669 bytes; crc 39504)
```

读取命令为 `M115`、`M501`、`M503 S0` 和 `M851`。其中 `M501` 只读取旧版 EEPROM 到内存，未发送 `M502` 或 `M500`，没有覆盖旧参数。

现场 EEPROM 返回的关键参数如下：

```gcode
M92 X80.66 Y80.58 Z400.00 E90.00
M203 X300.00 Y300.00 Z5.00 E25.00
M201 X1000 Y1000 Z50 E1000
M204 P2000.00 R2000.00 T2000.00
M205 Q20000 S0.00 T0.00 X30.00 Y30.00 Z0.30 E5.00
M206 X0.00 Y0.00 Z0.00
M301 P24.71 I1.61 D94.64
M304 P380.34 I66.65 D429.85
M851 Z0.00
M420 S0
M603 L0.00 U50.00
```

旧 EEPROM 当前报告 `M851 Z0.00`，但这只能说明保存值为 0，不能证明探针实际已经完成标定。`M420 S0` 表示读取时调平处于关闭状态，不代表新版配置不能启用调平。

与配置文档中的旧版编译默认值相比，现场值存在差异：X/Y 步数为 `80.66/80.58`，打印加速度为 `2000`，经典 Jerk X/Y 为 `30`。这些值应作为刷机后的核对参考，不能未经确认直接覆盖新版配置或 EEPROM。旧版正在使用私有 `M01` EEPROM，不能将其二进制内容直接迁移到 Marlin 2.1.2。

当前已完成旧参数读取；仍需通过 LCD 记录旧版私有菜单中的电机方向、旋钮方向和 Z 归零坐标。

已继续通过同一串口读取只读状态：

```text
Reporting endstop status
x_min: open
y_min: TRIGGERED
z_min: open
filament: TRIGGERED

ok T:23.12 /0.00 B:22.50 /0.00 @:0 B@:0
```

读取时未手动操作限位或断料开关，因此 `y_min: TRIGGERED` 和
`filament: TRIGGERED` 记录的是当前静态电平，不能单凭这一次输出判断接线极性是否正确。
刷入新版前后应在明确按压/释放开关的条件下重复 `M119` 对照验证。`M105` 显示当时热端
`23.12°C`、热床 `22.50°C`，目标温度均为 `0.00°C`，加热输出为 0；这只作为室温和传感器
接线基线，不替代新版的加热、PID 和热失控测试。

已使用 `D:\\Program Files (x86)\\AVRDUDESS\\avrdude.exe`，通过 `COM6`、ATmega2560、
`wiring` 协议和引导程序 `115200` 波特率完成刷新前只读备份。备份过程中未写入闪存或 EEPROM：

```text
backup/minitree-v0.96-beta-old-com6.hex
SHA-256: 65E8292A07297A85ADBB0627C018B1E79FB87EABD0C842D549B041AF781512E6

backup/minitree-v0.96-beta-old-com6-eeprom.hex
SHA-256: 41ECC4566B5943CDD169149F8604A7E45849DFF8B804EC9017A043E63197870D
```

闪存备份大小为 261426 字节，EEPROM 备份大小为 4096 字节。两个备份文件都被 `.gitignore`
中的 `*.hex` 规则忽略，不会进入 Git，需要另行归档保存。

EEPROM 备份的用途是回滚和归档，不是迁移手段：

- 旧版 `M01` 与新版设置结构不兼容，其二进制不能写入 Marlin 2.1.2；新版仍须执行
  `M502`、`M500` 初始化，并通过新版 G-code 恢复已经确认的参数。
- 需要完整回滚到旧固件时，闪存备份和 EEPROM 备份必须成对使用；只恢复闪存会把现场
  校准参数丢掉。
- 旧版 `1.1.x` 源码的 `SettingsDataStruct` 还保存 `planner_invert_dir`（运行时电机方向）
  和 `planner_encoder_dir`（旋钮方向）等私有字段，这些字段不会出现在 `M503` 输出中，
  是 EEPROM 备份相对串口文本的独有内容。
- 实测备份中 `M01` 出现在 EEPROM 偏移 `52` 和 `2100`，是两份完全相同的 333 字节副本；
  而库内 `1.1.x` 源码中 `EEPROM_OFFSET` 为 `100`，两者不一致。因此不能假定可以直接
  按库内源码解析该备份，私有字段仍应优先从旧版 LCD 菜单读取并记录。

编译通过只证明宏组合、源码和 ATmega2560 容量检查通过，不代表限位、方向、
探针、热敏电阻、加热器、断料开关和掉电恢复已经通过实机验收。

构建后的 `firmware.elf` 已确认包含以下 `M115` 关键信息：

```text
FIRMWARE_NAME:Marlin 2.1.2.8-MiniTree-T3
SOURCE_CODE_URL:github.com/shonngithub/Marlin_1.1.x-Minitree_T3
MACHINE_TYPE:MiniTree T3
```

## 2.2 旧版 LCD 私有设置记录

以下数值由现场在旧版固件的私有设置菜单中逐项读出。这些字段不会出现在 `M503` 输出中，
只能从 LCD 读取。旧版 `1.1.x` 源码 `Marlin/ultralcd.cpp` 的 `MENU_ITEM_EDIT*` 绑定确认了
菜单的“开/关”直接对应该布尔变量本身，不存在反相显示。

| LCD 菜单项 | 现场读数 | 旧版源码对应变量 |
| --- | --- | --- |
| 电机方向 X | 关 | `planner.invert_dir[X_AXIS]` = `false` |
| 电机方向 Y | 开 | `planner.invert_dir[Y_AXIS]` = `true` |
| 电机方向 Z | 开 | `planner.invert_dir[Z_AXIS]` = `true` |
| 电机方向 E | 开 | `planner.invert_dir[E_AXIS]` = `true` |
| 旋钮方向 | 关 | `planner.encoder_dir` = `false` |
| 归原点 XY 坐标 | X0 / Y0 | `planner.homing_des[X_AXIS]` = 0、`homing_des[Y_AXIS]` = 0 |
| 冷挤出 | 关 | `thermalManager.allow_cold_extrude` = `false` |
| 软限位 | 开 | `soft_endstops_enabled` = `true` |

与新版配置的对照：

- **电机方向一致。** 新版 `Marlin/Configuration.h` 为 `INVERT_X_DIR false`、`INVERT_Y_DIR true`、
  `INVERT_Z_DIR true`、`INVERT_E0_DIR true`，与现场读数逐项相同。MOT-03 由“待实机确认”
  变为“已按旧版现场值确认”，首次点动仍须低速复验。
- **旋钮方向一致。** 旧版宏为
  `ENCODER_DIFF_CW if(planner.encoder_dir){(encoderDiff++);}else{(encoderDiff--);}`，而源码中
  注释保留的原版宏在未定义 `REVERSE_ENCODER_DIRECTION` 时是 `ENCODER_DIFF_CW (encoderDiff++)`。
  因此 `encoder_dir = false` 等价于“反转”，与新版已启用的 `REVERSE_ENCODER_DIRECTION` 相同。
  注意旧版变量名的字面含义与“开=反转”相反，不能按字面理解。
- **归原点 XY 坐标不迁移。** 现场值为 `0,0`，且旧版发布配置中 `Z_SAFE_HOMING` 是注释掉的，
  这两个坐标在旧版实际不参与回零。新版使用床中心 `Z_SAFE_HOMING_X/Y_POINT`，属于已登记的
  行为变化（HOME-02）。
- **冷挤出一致，但证据偏弱。** 现场为“关”，即禁止冷挤出，与新版 `PREVENT_COLD_EXTRUSION`
  一致。但旧版该项标注“不保存”，且库内源码编译默认值是 `allow_cold_extrude = true`，
  该读数更可能反映运行时状态而非持久设置，不能当作强证据。
- **软限位一致，但只说明总开关。** 现场为“开”。该菜单项是 `soft_endstops_enabled` 全局开关，
  不能证明旧版各轴 MIN/MAX 编译开关的状态，END-02 的差异结论不变。

## 2.3 刷机后的实机记录

### 2.3.1 刷写与启动

GitHub Actions 构建产物 `download/marlin-mega2560/firmware.hex`（172072 字节数据，
地址 `0x0–0x2A028`，未越过 `0x3E000` 应用区上限）已通过引导程序刷入，校验通过：

```text
Reading 172072 bytes for flash from input file firmware.hex
Writing | ################################################## | 100% 25.92s
Reading | ################################################## | 100% 19.70s
172072 bytes of flash verified
```

刷写使用 avrdude `-D`（不做整片擦除），EEPROM 没有被擦除，由新版固件自动重建：

```text
Marlin 2.1.2.8-MiniTree-T3
echo: Compiled: Oct  3 2026
echo:V88 stored settings retrieved (607 bytes; crc 15538)
```

刷写前读取的 EEPROM 里只有旧版 `M01` 记录（偏移 `0x34` 与 `0x834`），没有 `V88`，
因此这条 `V88` 记录是新版首次启动检测到旧结构不兼容后自动初始化写入的。`M502`、
`M500` 的等效效果已经发生，无需再单独执行。

### 2.3.2 刷后参数与旧现场值对照

刷后 `M503` 全部为编译期默认值，旧机现场 EEPROM 值没有保留：

| 项目 | 旧固件现场值 | 刷后新值 |
| --- | --- | --- |
| `M92` X/Y | 80.66 / 80.58 | 80.00 / 80.00 |
| `M204` P | 2000 | 1000 |
| `M205` X/Y | 30 / 30 | 5 / 5 |
| `M145 S0` | H190 B70 | H200 B65 |
| `M301` / `M304` | 24.71/1.61/94.64、380.34/66.65/429.85 | 相同 |
| `M851` | Z0 | X26 Y20 Z0 |
| `M412` | — | S0（现场用 LCD 关闭，已写入 EEPROM） |
| `M413` | — | S1 |

`M92` 的 80.66/80.58、`M204 P` 2000、`M205 X/Y` 30 属于旧机现场调试值。`M92` 直接影响
尺寸精度：用 80.00 替代 80.66 会让 100 mm 的移动短约 0.8%。是否恢复由使用者决定；
若要恢复，建议只恢复 `M92`——`M204` 的 `P`/`T` 会被 `M201 X/Y = 1000` 的逐轴上限裁剪
（见 `planner.cpp` 的 `LIMIT_ACCEL_*`），实际不会生效。

### 2.3.3 已确认与待确认

已由现场确认：回原点正常、电机方向正常（与 2.2 节读出的旧 EEPROM 方向一致）、
限位正常、存储卡读写正常。

刷后只读查询：

```text
M119: x_min open / y_min open / z_min open / filament TRIGGERED
M105: ok T:22.54 /0.00 B:22.07 /0.00 @:0 B@:0
M420: echo:Bed Leveling OFF
```

其余待确认项目见 5.3 节和第 8 节。

### 2.3.4 探针与 Z-MIN 现状

本机没有安装探针，Z-MIN 引脚上接的是**机械 Z 限位开关**。当前配置是
`FIX_MOUNTED_PROBE` + `Z_MIN_PROBE_USES_Z_MIN_ENDSTOP_PIN`，即把 Z-MIN 的触发当作
探针触发。由此：

- `G28` 正常，因为 Z 归零本来就依赖 Z-MIN 触发。
- `G29` 的 9 次测量没有意义：机械限位开关的触发高度与喷嘴所在的 XY 位置无关，
  9 个点会得到相同高度，网格恒为平面。EEPROM 重置后网格本来就是全 0，且当前
  `M420 S0`（调平关闭），所以现在不会产生错误补偿，只是 `G29` 属于无效动作。
- `NOZZLE_TO_PROBE_OFFSET` 的 `X+26 / Y+20` 在 `G29` 中只会把探测点整体挪位。

不安装探针时不要使用 `G29`，改用机械方式调平（Z 限位高度或床面调平螺丝）。以后
安装探针时，必须先按第 6 节标定 `M851 Z` 再启用调平。

### 2.3.5 长文件名选项的实测开销

`LONG_FILENAME_HOST_SUPPORT`、`SCROLL_LONG_FILENAMES`、`UTF_FILENAME_SUPPORT` 逐项
启用后的实测容量（PlatformIO `mega2560`，与基线同一工具链）：

| 配置 | RAM | Flash |
| --- | --- | --- |
| 基线 | 5374 (65.6%) | 172064 (67.8%) |
| + `LONG_FILENAME_HOST_SUPPORT` | 5374 (+0) | 172658 (+594) |
| + `SCROLL_LONG_FILENAMES` | 5416 (+42) | 172852 (+194) |
| + `UTF_FILENAME_SUPPORT` | 5481 (+65) | 173018 (+166) |
| 三项全开 | **5481（+107）** | **173018（+954）** |

三项目前都保持关闭：本次只记录数据，不做配置修改。作用区分如下：

- `LONG_FILENAME_HOST_SUPPORT` 只影响串口（`M33`、`M20 L`），LCD 上仍显示 8.3 短名。
- `SCROLL_LONG_FILENAMES` 才让 LCD 菜单显示长文件名。
- `UTF_FILENAME_SUPPORT` 让长名缓冲按 2 字节/字符处理，中文名才可能正确解码，
  但仍受 `zh_CN` 字库覆盖范围限制。

开销来源可以对账：`LONG_FILENAME_LENGTH = 13 × (UTF?2:1) × VFAT_ENTRIES_LIMIT + 1`
（`SdFatConfig.h`），而 `VFAT_ENTRIES_LIMIT` 在启用 `SCROLL_LONG_FILENAMES` 时由 2 变成
5（`Conditionals_post.h`）。缓冲因此是 27 → 66 → 131 字节，与实测的 +42 / +65 相符。

### 2.3.6 SD 卡插拔后“存储卡初始化失败”不消失（已定位）

现象：插卡正常、读取正常；拔卡后 LCD 显示“存储卡初始化失败”；重新插卡后读取恢复，
但该提示一直不消失。

只读串口抓取（`logs/sd-swap-capture.txt`）复现了完整过程：

```text
[  33.58s] echo:SD card released
[  36.09s] echo:No SD card
[  36.10s] echo:SD card released
[  38.47s] echo:SD card ok
```

原因链条（每一步都有代码依据）：

1. `core/language.h` 中 `STR_SD_INIT_FAIL` 的字符串就是 `"No SD card"`，它由
   `CardReader::mount()` 在 `driver->init()` 失败时打印。
2. 拔卡时 SD 卡座的机械检测触点会抖动，`manage_media()` 轮询到一次假的“已插入”
   边沿，于是对着一张已经不在的卡调用 `mount()`，失败。
3. `mount()` 失败后执行 `LCD_ALERTMESSAGE(MSG_MEDIA_INIT_FAIL)`，这就是 LCD 上的
   “存储卡初始化失败”，也是全工程唯一使用该字符串的位置。
4. 该提示属于 alert（级别 1），`finish_status()` 对 alert 设置
   `status_message_expire_ms = 0`，即**永不超时**。
5. 更关键的是 alert 会屏蔽后续低级别消息：`set_status()` 开头是
   `if (level < alert_level) return;`。重新插卡走的是级别 0 的
   `LCD_MESSAGE(MSG_MEDIA_INSERTED)`，会被直接丢弃，所以提示不会刷新。
6. 只有 `set_status(..., -1)` 会把 `alert_level` 清零，实际能走到的路径只有重启或
   开始一次打印，因此提示会一直停留。

可选修法：

- 最小改动：把 `MarlinUI::media_changed()` 中的插卡/拔卡消息换成 `LCD_MESSAGE_MIN(...)`
  （级别 -1），这样卡事件会顺带清掉卡住的 alert。
- 更彻底：在 `manage_media()` 中对检测引脚去抖，避免对不存在的卡发起 `mount()`。

另外，媒体菜单里的“更换存储卡”发送 `M21`（即 `card.mount()`）。它的设计用途是没有卡
检测引脚的机器，而本机 `HAS_SD_DETECT` 工作正常，所以按它通常没有可见效果——`mount()`
只在串口打印 `SD card ok`，LCD 侧只调用 `ui.refresh()`，既不提示也不发生变化。

### 2.3.7 断电续打（PLR）没有丢失，只是改了文案

结论：`POWER_LOSS_RECOVERY` 在新固件里是启用的（`M413 S1`，且 `Configuration_adv.h` 中
`PLR_ENABLED_DEFAULT true`），触发方式与旧版一致，**差别只在菜单文案**。

旧版（`1.1.x`，`ultralcd.cpp:929`）：

```cpp
static void lcd_job_recovery_menu() {
  defer_return_to_status = true;
  START_MENU();
  STATIC_ITEM(MSG_POWER_LOSS_RECOVERY);   // 旧 zh_CN 未翻译 → 屏幕显示英文
  MENU_ITEM(function, MSG_RESUME_PRINT, lcd_power_loss_recovery_resume);
  MENU_ITEM(function, MSG_STOP_PRINT, lcd_power_loss_recovery_cancel);
  END_MENU();
}
```

新版（`src/lcd/menu/menu_job_recovery.cpp:48`）：

```cpp
void menu_job_recovery() {
  ui.defer_status_screen();
  START_MENU();
  STATIC_ITEM(MSG_OUTAGE_RECOVERY);       // zh_CN 译为“中断恢复”
  ACTION_ITEM(MSG_RESUME_PRINT, lcd_power_loss_recovery_resume);
  ACTION_ITEM(MSG_STOP_PRINT, lcd_power_loss_recovery_cancel);
  END_MENU();
}
```

两者结构完全相同（标题 + 恢复打印 + 停止打印）。旧版 `language_zh_CN.h` 里没有
`MSG_POWER_LOSS_RECOVERY` 这一条，所以旧屏幕显示的是英文 **“Power-Loss Recovery”**；
Marlin 2.x 的 `zh_CN` 把对应的 `MSG_OUTAGE_RECOVERY` 译成了 **“中断恢复”**。因此照原来的
英文名去找就找不到，看起来像功能没了。

新固件里的位置：`Configuration` 菜单 → **“中断恢复”** 开关
（`menu_configuration.cpp:570`）。

触发方式对比：

- 旧版：`lcd_update()` 里检测到 `job_recovery_commands_count` 就切到恢复菜单
  （`ultralcd.cpp:5227`）。
- 新版：SD 首次挂载时 `manage_media()` 调用 `recovery.check()`（`cardreader.cpp:530`），
  发现有效恢复文件就注入 `M1000S`（`powerloss.cpp:132`），`M1000 S` 打开
  `menu_job_recovery` 界面（`M1000.cpp:71`）。

恢复文件也不同：旧版是卡根目录下的 `bin`（`cardreader.cpp:938`），新版是 `/PLR`
（`powerloss.cpp:42`）。打印过程中查看 SD 卡内容即可判断 PLR 是否在工作。

写入时机：本机没有专用掉电检测引脚，恢复文件只在**从 SD 卡打印期间**写入，是否落盘由
`PrintJobRecovery::save()` 的判断决定（`powerloss.cpp:182`）：

```cpp
  if (force
    #if DISABLED(SAVE_EACH_CMD_MODE)
      #if SAVE_INFO_INTERVAL_MS > 0       // 本分支为注释状态，不生效
        || ELAPSED(ms, next_save_ms)
      #endif
      || current_position.z > info.current_position.z + POWER_LOSS_MIN_Z_CHANGE
    #endif
  ) {
```

`SAVE_INFO_INTERVAL_MS` 在本分支是注释掉的（`powerloss.h:51`），所以非强制保存只由最后
一条触发；而 `info.current_position` 由步进中断持续写成“正在执行的运动块的起始位置”
（`stepper.cpp:2386`）。也就是说：**只有规划器目标 Z 比正在执行的 Z 高出
`POWER_LOSS_MIN_Z_CHANGE`（0.05 mm）时才落盘，实际效果是每换一层保存一次。**
另外 `M24` 会强制保存一次，但从 LCD 菜单启动打印走的是 `openAndPrintFile()`
（`menu_media.cpp:57`），不经过 `M24`。

推论：如果断电发生在**第一次换层之前**，卡上根本还没有 `PLR` 文件，开机自然不会有恢复
提示，这属于正常行为。因此复现时应当打印到第 2~3 层之后再断电，并在断电后先把卡拿到
电脑上确认根目录有没有 `PLR` 文件，再装回开机看提示。

## 3. 核心功能逐项核对

| ID | 旧版功能 | Marlin 2.1.2 处理 | 状态 |
| --- | --- | --- | --- |
| HW-01 | RAMPS 1.4 EFB / Mega2560 | `BOARD_RAMPS_14_EFB`、`mega2560` | 已移植，编译通过 |
| HW-02 | 串口 0、250000 | 保留原值 | 已移植 |
| HW-03 | 单 E0、1.75 mm | 保留并显式使用 A4988 类驱动配置 | 已移植，驱动型号待实机确认 |
| HW-04 | 125 × 125 × 160 mm | 设置床尺寸和 Z 行程 | 已移植 |
| MOT-01 | 步数、速度、加速度 | 按旧配置迁移 | 已移植，待低速点动 |
| MOT-02 | 经典 Jerk | 启用 `CLASSIC_JERK` 并迁移数值 | 已移植 |
| MOT-03 | XYZ/E0 编译期方向 | 使用新版 `INVERT_*_DIR` | 已移植；与旧版 LCD 读数逐项一致，待首次低速点动 |
| MOT-04 | LCD 运行时修改电机方向 | 不保留危险的即时反转和私有 EEPROM | 已确认不移植 |
| END-01 | X/Y/Z MIN 限位极性 | 迁移为反相 `true` | 已移植，必须先执行 `M119` |
| END-02 | 关闭 Z 最小和全部最大软件限位 | 启用 XYZ 最小/最大软件限位：X/Y 0–125，Z 0–160 mm | 已确认采用新版限制 |
| PRB-01 | 固定探针，共用 Z-MIN | 原生固定探针配置 | 已移植，待 `M119` |
| PRB-02 | 探针 X+26/Y+20、配置默认 Z0 | 使用 `NOZZLE_TO_PROBE_OFFSET` | X/Y 已移植；旧版 `M851` 读出 Z0.00（疑似未标定），须重新标定 |
| ABL-01 | 线性 3 × 3 调平 | `AUTO_BED_LEVELING_LINEAR` | 已移植，待 G29 |
| ABL-02 | G28 后强制启用调平 | 原生 `ENABLE_LEVELING_AFTER_G28` | 原生替代，待实机确认 |
| HOME-01 | EEPROM 可编辑 Z 归零 XY | 旧配置实际未启用 `Z_SAFE_HOMING` | 无需复制；现场读数为 0,0，旧版未启用 |
| HOME-02 | 安全 Z 归零 | 使用标准床中心 `Z_SAFE_HOMING` | 安全增强，存在行为差异 |
| TMP-01 | 热端/热床传感器类型 1 | 保留 | 已移植 |
| TMP-02 | 热端/热床 PID | 保留旧值 | 已移植，建议重新整定 |
| TMP-03 | 热端输出上限 200 | `PID_MAX 200` | 已移植 |
| TMP-04 | MAXTEMP 265/120°C | 保留 | 已移植 |
| TMP-05 | MINTEMP -20°C | 使用新版安全默认 5°C | 安全修正，不等价 |
| TMP-06 | 开机默认允许冷挤出 | 恢复 `PREVENT_COLD_EXTRUSION` | 安全修正；旧版 LCD 现场读数已为“关” |
| TMP-07 | 负热床温度显示为 0 | 保留真实读数和故障 | 安全修正，不移植 |
| TMP-08 | M109/M190 等待窗口 | 保留旧值 | 已移植 |
| TMP-09 | 热失控周期和迟滞 | 保留旧值 | 已移植，需拔插与失温测试 |
| RUN-01 | D19 单路断料传感器 | D19、内部上拉、LOW 触发、默认启用 | 已移植；现场已用 `M412 S0` 关闭并写入 EEPROM；空接时实测为 TRIGGERED，见 5.3 |
| RUN-02 | 断料执行 M600 | 原生 `FILAMENT_RUNOUT_SCRIPT` | 已移植 |
| M600-01 | 装料、卸料、清料、停靠参数 | 映射到新版 Advanced Pause 参数 | 已移植，待完整流程测试 |
| M600-02 | `PAUSE_PARK_NO_STEPPER_TIMEOUT 500` | 按布尔开关正确启用 | 已确认暂停期间 XYZ 持续上电 |
| SD-01 | LCD SD | `SDSUPPORT`、LCD 连接 | 已移植 |
| SD-02 | 打印结束释放电机 | 新版 `"M84"` | 原生等价替代 |
| PLR-01 | 掉电恢复默认开启 | `POWER_LOSS_RECOVERY`、默认 `true` | 已移植；菜单文案由英文改为中文“中断恢复”，见 2.3.7；待真实断电测试 |
| LCD-01 | 12864 ST7920 | 原生 Full Graphic Controller | 已移植 |
| LCD-02 | ST7920 125/125/125 ns | 配置层 `BOARD_ST7920_DELAY_*` | 已移植，待屏幕稳定性测试 |
| LCD-03 | 旋钮方向反转 | `REVERSE_ENCODER_DIRECTION` | 原生替代；与旧版 LCD 读数一致 |
| LCD-04 | 自定义启动位图 | 旧配置从未启用；新版关闭启动画面 | 无需移植 |
| LANG-01 | 简体中文菜单 | 原生 `LCD_LANGUAGE zh_CN`，补齐本机实际编入的回退消息 | 已补齐当前构建；其他消息可回退英文 |
| LANG-02 | 自制中文字体和 UTF mapper | 使用新版原生字库和 UTF-8 框架 | 原生替代；任意汉字不保证全覆盖 |
| EEPROM-01 | M500/M501/M503 | 新版原生 EEPROM 设置 | 已移植 |
| EEPROM-02 | 私有 `M01` 布局 | 不读取旧二进制，启用自动初始化 | 不兼容，按升级流程处理 |
| BRAND-01 | MiniTree T3 身份 | `_Version.h` 统一 M115 和版本信息 | 已移植 |

## 4. 旧版引入模块核对

| 旧版引入或扩展模块 | 是否迁移 | 处理结论 |
| --- | --- | --- |
| 自制中文字体数据 | 否，原生替代 | 新版 `zh_CN` 字库覆盖基础中文 UI，避免旧映射缺陷 |
| 自制 UTF-8/汉字索引映射 | 否，原生替代 | 旧实现对两字节字符和部分 ASCII 处理有缺陷 |
| LCD 私有设置菜单 | 部分 | EEPROM、冷挤出命令、软限位等由原生命令/菜单承担；危险项不复制 |
| 运行时 XYZ/E 电机方向 | 否 | 打印中即时反向风险高，改用编译期配置 |
| 运行时旋钮方向 | 否，原生替代 | 由 `REVERSE_ENCODER_DIRECTION` 固定 |
| EEPROM 可编辑 Z 归零 XY | 否，原生替代 | 旧配置中实际无效，新版使用床中心安全归零 |
| 私有 EEPROM `M01` | 否 | 与 2.1.2 设置结构二进制不兼容 |
| `X1` Wi-Fi 命令 | 否，确认无需 | 当前 Mega2560 不使用 Wi-Fi，历史命令不再迁移 |
| M109/M190 显示当前 SD 文件名 | 否，确认不需要 | SD 打印也保持新版标准加热/冷却状态提示 |
| 隐藏 ABS 预热 | 不需要 | 保留新版原生 PLA/ABS 预热菜单，不再作为兼容要求 |
| 喷嘴单独预热 | 是，原生替代 | 新版温度菜单已提供按加热器操作 |
| 设置原点偏移后自动 M500/M501 | 否 | 使用标准“显式保存设置”语义，避免无提示写 EEPROM |
| G28 后恢复调平源码补丁 | 否，原生替代 | 使用 `ENABLE_LEVELING_AFTER_G28` |
| 自定义启动位图 | 否，无需 | 旧发布配置没有启用 |
| ST7920 慢时序 | 是 | 已等价设置为 125/125/125 ns |

## 5. 已知兼容问题和行为变化

### 5.1 刷机前必须处理

1. **旧 EEPROM 不兼容。** 旧 `M01` 与新版布局不同，必须先记录旧 `M503`
   数据，刷机后执行 `M502`、`M500`。
2. **配置文件中的探针 Z 偏移为 0。** 这不等于旧 EEPROM 的 `M851 Z` 校准值。
   结构未变化时可先恢复旧值并验证；旧值无法取得或验证不通过时再重新标定。
3. **限位和探针极性只能通过实机确认。** 首次回零前必须使用 `M119`，分别
   按下 X、Y、Z、探针和断料开关检查状态。
4. **电机方向尚未经过实机确认。** 首次只允许每轴 1 mm 低速点动，并准备
   立即断电。

### 5.2 有意保留的安全差异

| 项目 | 旧版 | 新版 | 影响 |
| --- | --- | --- | --- |
| 冷挤出 | 开机默认允许 | 默认禁止，阈值 185°C | 防止冷态强推耗材 |
| 热端/热床 MINTEMP | -20°C | 5°C | 更容易识别断线，寒冷环境需实测 |
| 负床温显示 | 强制为 0 | 显示真实值/触发故障 | 不再掩盖传感器异常 |
| XYZ 软件限位 | 旧版仅启用 X/Y 最小限位 | X/Y `0–125 mm`，Z `0–160 mm` | 已确认不需要负 Z 或越界移动 |
| Z 安全归零 | 旧配置未启用 | 启用，床中心 | 回零路径和位置发生变化 |
| M600 步进保持 | 旧宏写法实际无效 | 正确启用 | 暂停期间 XYZ 持续上电 |

以上 X/Y 范围是喷嘴的软件移动范围。探针偏移 X `+26`、Y `+20`，并保留
`15 mm` 探测边距，因此默认 G29 实际探针区域为 X `26–110 mm`、
Y `20–110 mm`；3 × 3 探测坐标为 X `{26, 68, 110}`、
Y `{20, 65, 110}`。

### 5.3 仍需实机确认

- ST7920 在 125/125/125 ns 时是否无花屏、漏字和随机复位。
- D19 断料电平与配置预期不符：`FIL_RUNOUT_PULLUP` 生效时（`runout.h` 的
  `INIT_RUNOUT_PIN` → `SET_INPUT_PULLUP`，开机时无条件执行，不受 `M412` 影响）空接插件
  本应读 HIGH，但实测 `M119` 报 `filament: TRIGGERED`，说明 D19 被外部拉低。现场已用
  `M412 S0` 关闭检测并写入 EEPROM；将来安装断料传感器时必须实测两种状态的电平，
  必要时把 `FIL_RUNOUT_STATE` 改为 `HIGH`。
- Z-MIN 由机械限位开关触发（本机未安装探针），`M119` 的 `z_min` 触发逻辑正常；但因
  探针与 Z-MIN 共用引脚，`G29` 无实际意义，见 2.3.4。
- `Z_SAFE_HOMING` 在床中心执行 Z 归零，需确认该位置机械 Z 限位能正常触发、不会撞床。
- 旧 PID 参数是否仍适合当前热端、热床、MOSFET 和电源。
- 热端 60 秒、热床 90 秒热失控周期是否过于宽松。
- 新版 `WATCH_TEMP_PERIOD 40` 与旧设备升温速度是否匹配。
- 中文菜单和特殊符号是否正常显示。长文件名三项当前全部关闭，SD 列表只显示 8.3 短名，
  中文文件名会显示为乱码；实测开销见 2.3.5。
- 已补齐当前 Mega2560 构建实际编入的缺失中文消息；未启用功能仍允许回退英文，
  实机遍历菜单后再补充发现的遗漏。
- 从 SD 打印含 `M109`、`M190` 的文件，确认状态栏分别显示喷嘴或热床的标准
  加热/冷却提示。
- 无专用掉电检测脚时，SD 写入频率、恢复文件和恢复顺序是否可靠。

## 6. 实机验收顺序

建议按以下顺序执行，不要跳过前面的低风险检查：

1. 刷机前保存旧固件的 `M503` 输出。
2. 刷入后执行 `M502`、`M500`、`M503`，确认新版默认值。
3. 执行 `M115`，确认版本为 `2.1.2.8-MiniTree-T3`。
4. 执行 `M119`，手动触发所有限位、探针和断料开关。
5. 在未回零状态下逐轴低速点动 1 mm，确认 XYZ/E 方向。
6. 分别回零 X、Y，最后在手压探针验证后回零 Z。
7. 测量真实行程，确认 X/Y `0–125 mm`、Z `0–160 mm` 软件限位与机械行程一致。
8. 使用 `M851` 标定探针 Z 偏移并 `M500` 保存。
9. 执行 G28、G29，确认 G28 后调平状态和 3 × 3 网格。
10. 对热端、热床执行 PID 自动整定，并测试传感器拔插和热失控保护。
11. 手动执行 M600，再测试断料触发、停靠、装卸料、超时和恢复。
12. 测试 SD 打印、中文菜单、文件名、旋钮方向和打印结束释放电机。
13. 最后使用可丢弃的小模型测试真实断电和恢复。

## 7. EEPROM 升级与旧参数获取流程

旧版 EEPROM 使用私有版本 `M01`，新版 Marlin 2.1.2 使用不同的设置结构。
两者不能按 EEPROM 地址或二进制镜像直接互换。正确流程是：

1. 旧固件仍在运行时，通过 USB 串口读出当前参数。
2. 另外记录旧版 LCD 私有菜单中的方向、旋钮和归零坐标。
3. 保存串口终端文本和 LCD 设置照片。
4. 刷入新版后初始化新版 EEPROM。
5. 只把已经确认的校准参数通过新版 G-code 恢复。

### 7.1 刷机前的串口连接

在旧固件仍能启动时：

1. 用 USB 线连接 Mega2560 与电脑，并给主板正常供电。
2. 打开 Pronterface、Repetier-Host、OctoPrint Terminal 或其他串口终端。
3. 选择打印机对应的 COM 口。
4. 波特率设置为 `250000`，这是旧配置中的 `BAUDRATE`。
5. 连接后先确认终端能收到旧固件的 `ok` 或启动信息。

不要在记录前发送 `M502` 或 `M500`。`M502` 会把内存参数恢复为编译期默认值，
`M500` 会把这些默认值写进旧 EEPROM。

### 7.2 读取旧版 EEPROM 参数

在串口终端依次发送：

```gcode
M115
M501
M503 S0
```

命令作用：

- `M115`：确认当前运行的是旧 MiniTree T3 固件。
- `M501`：从旧 EEPROM 重新加载参数到当前内存。旧固件启动时通常已经加载过，
  这里再次执行是为了让读取流程明确、可重复。
- `M503 S0`：以紧凑、可重放的格式输出当前内存中的全部设置。

把终端返回的所有 `echo:` 行完整保存为文本文件。不要只截取 PID 或步数，
因为 `M503` 还可能包含现场修改过的速度、Jerk、预热温度、耗材直径、回抽等
参数。

旧版 `M503 S0` 中重点查找：

| 输出命令 | 要保存的参数 |
| --- | --- |
| `M92 X... Y... Z... E...` | XYZ/E 步数/mm |
| `M203 X... Y... Z... E...` | XYZ/E 最大速度 |
| `M201 X... Y... Z... E...` | XYZ/E 最大加速度 |
| `M204 P... R... T...` | 打印、回抽、空移加速度 |
| `M205 ...` | Jerk、最低速度等高级运动参数 |
| `M206 X... Y... Z...` | Home Offset |
| `M301 P... I... D...` | 热端 PID |
| `M304 P... I... D...` | 热床 PID |
| `M851 Z...` | 探针 Z 偏移 |

也可以在旧固件中直接查询探针 Z 偏移：

```gcode
M501
M851
```

不带参数的 `M851` 只读取并报告当前探针 Z 偏移，不会修改 EEPROM。旧固件通常
返回类似：

```text
echo:Z Offset: -2.35
```

其中 `-2.35` 只是输出格式示例。应以现场机器的实际返回值为准，并把原始行
完整保存。如果 `M851` 返回 `0.00`，仍需确认这是实机校准结果，而不是从未
校准过的配置默认值。

建议同时保留完整的原始输出，例如：

```text
旧固件 M503 S0 输出
记录时间：________________
固件版本：________________
串口：COM____ / 250000

在下面粘贴终端返回的完整内容，不要手工改写：
____________________________________________________________
____________________________________________________________
____________________________________________________________
```

### 7.3 旧版 LCD 私有设置的记录

旧版定制代码在 `M503` 中没有报告以下私有 EEPROM 字段，因此必须从 LCD 菜单
单独读取并拍照或手工记录：

- X/Y/Z/E 电机方向。
- LCD 旋钮方向。
- Z 归零 X/Y 坐标。
- 其他 MiniTree 私有设置菜单中的现场值。

这三项已在本机现场读取完成。完整读数、旧版源码绑定关系和与新版配置的对照见
本文 2.2 节，摘要如下：

```text
X 电机方向：关（false）
Y 电机方向：开（true）
Z 电机方向：开（true）
E 电机方向：开（true）
旋钮方向：关（false，等价于反转）
归原点 XY 坐标：X0 / Y0
冷挤出：关
软限位：开
```

电机方向与新版 `INVERT_*_DIR` 逐项一致，但仍必须在新固件首次点动前用低速点动复验。

旧版的 Z 归零 X/Y 菜单在发布配置中没有启用 `Z_SAFE_HOMING`，现场读数为 `0,0`，因此即使
EEPROM 中保存了坐标，实际回零也没有使用它。新版使用床中心的标准安全归零，不应把
这两个私有坐标直接写入新版 EEPROM。

### 7.4 推荐的现场资料包

刷机前建议建立一个目录，至少保存：

```text
MiniTree_T3_旧固件参数\
  M503_S0_完整输出.txt
  LCD_电机方向.jpg
  LCD_旋钮方向.jpg
  LCD_归零坐标.jpg
  LCD_其他设置.jpg
  旧固件版本.txt
  备注.txt
```

`备注.txt` 中记录喷嘴、探针、热床、挤出机和步进驱动是否拆装过。只要机械
结构发生变化，原来的探针 Z 偏移和 PID 就只能作为参考，不能直接视为有效值。

### 7.5 刷入新版后的 EEPROM 初始化

确认旧参数已经保存后，再刷入新版固件。新版首次启动可能因为 EEPROM 版本
不同而自动初始化；仍建议明确执行：

```gcode
M502
M500
M503
```

命令作用：

- `M502`：加载新版编译期默认值到内存。
- `M500`：把新版默认值写入新版 EEPROM。
- `M503`：检查新版当前设置，确认 EEPROM 初始化成功。

之后只恢复已经核对过的参数。例如：

```gcode
M92 X80 Y80 Z400 E90
M203 X300 Y300 Z5 E25
M201 X1000 Y1000 Z50 E1000
M204 P1000 R2000 T2000
M851 Z-2.35
M500
M503
```

上面的 `M851 Z-2.35` 只是格式示例，不能直接作为 MiniTree T3 的实际值。
真实 Z 值必须来自旧 `M503` 或重新标定。PID 参数也应先确认热端、热床和电源
硬件没有变化，再使用对应的 `M301`、`M304` 命令恢复；更稳妥的做法是重新
执行 PID 自动整定。

### 7.6 不能做的操作

- 不要把旧 EEPROM 芯片镜像直接写入新版。
- 不要按旧 `M01` 结构的地址手工修改新版 EEPROM。
- 不要在未记录旧参数前执行 `M502`、`M500`。
- 不要把旧版 LCD 私有电机方向字段当作新版 `M500` 能自动恢复的参数。
- 不要在探针 Z 偏移未确认前开始正式打印。

如果新版固件已经刷入并启动，且没有提前保存 `M503`，旧 EEPROM 内容可能已经
被新版的自动初始化流程覆盖。此时优先检查是否还有旧固件的串口日志、截图、
维护记录或已拆下的旧控制器；不要继续执行会写 EEPROM 的命令。

## 8. 尚未关闭的维护项

- 私有设置记录已完成：电机方向、旋钮方向、归原点 XY 坐标、冷挤出和软限位均已现场读取，
  见本文 2.2 节。
- 新固件已刷入并运行，回零、电机方向、限位和 SD 读写已现场确认，见 2.3 节。
- 探针 Z 偏移：本机未安装探针（Z-MIN 接机械限位开关），因此暂无需要标定的 Z 偏移；
  `G29` 在装探针前不要使用，见 2.3.4。
- 决定是否恢复旧机现场值 `M92 X80.66 Y80.58`（`M204 P`/`M205 X/Y` 建议不恢复），
  对照见 2.3.2。
- 实机遍历新版启用功能的中文菜单，记录仍显示英文或缺字的项目并按需补充。
- 长文件名三项的实测开销已记录（2.3.5），当前决定暂不启用。
- SD 卡插拔后“存储卡初始化失败”不消失：已定位（2.3.6）并按最小改动打补丁（9.1），
  待下次构建刷入后复验。
- 断电续打功能确认存在，只是菜单文案改为“中断恢复”（2.3.7）；仍需一次真实断电测试。
- 实机运行构建与库内 `1.1.x` 源码存在不一致：EEPROM 中 `M01` 位于偏移 `52`（源码为 `100`），
  且旧版 `allow_cold_extrude` 编译默认为 `true` 而现场读数为“关”。旧版源码只能作为参考，
  不能当作实机行为的精确依据。
- 完成全部实机验收后，把本文中的“待实机”状态更新为具体结果。

在这些项目完成前，可以确认“迁移分支编译通过且核心配置已映射”，但不能确认
“所有旧定制功能均已实机无问题”。

## 9. 本分支引入的本地定制

以下改动不是旧版遗留定制，而是迁移到 Marlin 2.1.2 之后为修复实机问题新增的补丁。
升级上游源码或重新合并时，需要连同这些改动一起处理。

**当前装机状态**：9.1 与 9.2 已合入，并用本地构建（`Compiled: Oct 4 2026 18:54:43`，
RAM `5374`、Flash `172008`）通过 COM6 刷入。刷写使用 avrdude `-D`，EEPROM 未被擦除，
启动仍读到 `V88 stored settings retrieved (607 bytes; crc 15538)`，与刷写前一致；
`M412 S0`、`M413 S1` 等现场设置保留。

曾刷入过一版 9.2 守卫写错的构建（Flash `172096`），该版本媒体菜单里出现的是“释放存储卡”
而不是“更换存储卡”，已用修正版覆盖。两个补丁的 LCD 行为仍待现场确认。

### 9.1 媒体插拔消息改用 `LCD_MESSAGE_MIN`

- **文件**：`Marlin/src/lcd/marlinui.cpp`，函数 `MarlinUI::media_changed()`
- **改动**：插卡与拔卡两处消息由 `LCD_MESSAGE(...)`（级别 0）改为 `LCD_MESSAGE_MIN(...)`
  （级别 -1）。

```cpp
        #else
          LCD_MESSAGE_MIN(MSG_MEDIA_INSERTED); // MiniTree T3: level -1 clears a stuck media alert
        #endif
```

```cpp
        #elif HAS_SD_DETECT
          LCD_MESSAGE_MIN(MSG_MEDIA_REMOVED); // MiniTree T3: level -1 clears a stuck media alert
```

- **原因**：见 2.3.6。拔卡时卡座检测触点抖动会让固件对着一张不存在的卡调用 `mount()`，
  失败后弹出级别 1 的 `MSG_MEDIA_INIT_FAIL`（“存储卡初始化失败”）。该 alert 永不超时，
  并且会屏蔽级别 0 的后续消息，于是重新插卡时“存储卡已插入”无法覆盖它。级别 -1 会在
  设置消息的同时把 `alert_level` 清零。
- **影响范围**：只影响媒体插拔提示本身，不改变挂载/卸载逻辑；其他
  `LCD_ALERTMESSAGE` 调用未改动，其他 alert 的粘滞行为不受影响。
- **构建验证**：本地 `platformio run -e mega2560` 通过，RAM `5374`、Flash `172064`，
  与打补丁前完全一致（同一个调用只换了参数，无额外体积）。
- **待实机验证**：刷入后重复 2.3.6 的拔插步骤，确认提示能被“存储卡已插入”替换。

### 9.2 隐藏媒体菜单的“更换存储卡”

- **文件**：`Marlin/Configuration_adv.h`（开关）、`Marlin/src/lcd/menu/menu_main.cpp`（两处菜单项）
- **改动**：新增开关 `HIDE_MEDIA_CHANGE_ITEM`，并用它把两处菜单项包起来。

```cpp
  // Configuration_adv.h, SDSUPPORT 段
  #define HIDE_MEDIA_CHANGE_ITEM
```

```cpp
        // menu_main.cpp：守卫必须嵌在 HAS_SD_DETECT 分支内部
        #if HAS_SD_DETECT
          #if DISABLED(HIDE_MEDIA_CHANGE_ITEM)
            GCODES_ITEM(MSG_CHANGE_MEDIA, F("M21" TERN_(MULTI_VOLUME, "S"))); // M21 Change Media
          #endif
          #if ENABLED(MULTI_VOLUME)
            GCODES_ITEM(MSG_ATTACH_USB_MEDIA, F("M21U")); // M21 Attach USB Media
          #endif
        #else                                             // - or -
          ACTION_ITEM(MSG_RELEASE_MEDIA, ...);            // M22 Release Media（无卡检测的机器用）
        #endif
```

- **⚠️ 已踩过的坑**：不要写成 `#if HAS_SD_DETECT && DISABLED(HIDE_MEDIA_CHANGE_ITEM)`。
  定义开关后该条件为假，预处理器会掉进 `#else` 分支，把**给无卡检测机器用的
  “释放存储卡”（M22）编译进来**，看起来像“隐藏成功”，实际是换错了一项。
  构建体积也能暴露这个问题：正确隐藏应让 Flash **变小**（172064 → 172008），
  写错时会变成变大（172064 → 172096）。
- **原因**：见 2.3.6 末尾。本机 `HAS_SD_DETECT` 工作正常，媒体自动挂载/释放，手动
  “更换存储卡”（`M21`）没有可见效果。菜单项原本由 `#if HAS_SD_DETECT` 直接编译进来，
  上游没有提供隐藏开关。
- **注意**：不要用 `NO_SD_DETECT` 达到同样目的——那会连卡检测一起关掉。
- **影响范围**：只隐藏菜单项，`M21` 命令本身仍然可用（实测返回 `SD card ok`）；菜单里
  “从存储卡上打印”（`MSG_MEDIA_MENU`）等其他项目不受影响。

### 9.3 尚未合入源码的候选改动

- `manage_media()` 检测引脚去抖：从源头避免对不存在的卡发起 `mount()`，属于 9.1 的
  更彻底方案。当前未实施。
