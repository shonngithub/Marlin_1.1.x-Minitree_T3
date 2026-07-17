# MiniTree T3 Marlin 2.1.2 构建与发布打包指南

## 1. 文档用途

本文用于从当前迁移分支构建 MiniTree T3 固件，并生成便于刷写、归档和后续维护的
发布包。当前固件基于 Marlin `lts-2.1.2`，固件标识为：

```text
2.1.2.8-MiniTree-T3
```

目标硬件为：

- MCU：ATmega2560，16 MHz
- 主板：RAMPS 1.4 EFB
- PlatformIO 环境：`mega2560`
- 显示器：RepRapDiscount 12864 Full Graphic，ST7920
- 串口：`SERIAL_PORT 0`，`250000`

不要使用 Arduino IDE 直接编译本项目。当前配置和验证流程以 PlatformIO 为准。

## 2. 已验证的构建环境

2026 年 7 月 17 日验证通过的环境如下：

| 组件 | 已验证版本 | 说明 |
| --- | --- | --- |
| Windows | Windows 10/11 64 位 | 当前维护环境 |
| Git | 2.51.1.windows.1 | 拉取源码、记录提交和制作源码包 |
| Python | 3.11.7 | PlatformIO 运行环境 |
| PlatformIO Core | 6.1.19 | 命令行构建工具 |
| PlatformIO 平台 | `atmelavr 4.0.1` | 已由 `ini/avr.ini` 固定为 `~4.0.1` |
| Arduino AVR 框架 | 5.1.0 | PlatformIO 自动安装 |
| AVR GCC 工具链 | 1.70300.191015 | GCC 7.3.0，PlatformIO 自动安装 |
| avrdude | 1.60300.200527 | PlatformIO 自动安装 |
| U8glib-HAL | 0.5.4 | 12864 图形屏依赖，首次构建自动安装 |

首次安装依赖和库需要联网。依赖下载完成后，在 PlatformIO 缓存未被清理的情况下
可以离线重复构建。

## 3. 安装构建环境

### 3.1 推荐方式：VS Code

安装以下软件：

1. Git for Windows。
2. Python 3.11，安装时勾选加入 PATH。
3. Visual Studio Code。
4. VS Code 的 PlatformIO IDE 扩展。

使用 VS Code 打开仓库根目录，而不是只打开 `Marlin` 子目录。PlatformIO 应识别
根目录下的 `platformio.ini`，默认环境为 `mega2560`。

### 3.2 命令行方式

使用固定版本安装 PlatformIO：

```powershell
py -3.11 -m pip install --user platformio==6.1.19
py -3.11 -m platformio --version
```

如果机器已经由 PlatformIO IDE 创建了标准虚拟环境，也可以直接使用：

```powershell
& "$env:USERPROFILE\.platformio\penv\Scripts\platformio.exe" --version
```

以下章节使用 `python -m platformio` 表示 PlatformIO 命令。实际执行时可以替换成
当前机器可用的 `py -3.11 -m platformio`、`pio`，或上面的完整可执行文件路径。

## 4. 获取正确源码

```powershell
git clone git@github.com:shonngithub/Marlin_1.1.x-Minitree_T3.git
Set-Location Marlin_1.1.x-Minitree_T3
git switch codex/minitree-t3-lts-2.1.2-migration
git pull --ff-only origin codex/minitree-t3-lts-2.1.2-migration
```

构建前记录分支和提交：

```powershell
git status --short --branch
git log -1 --oneline
git rev-parse HEAD
```

正式发布时工作树应保持干净。若 `git status --porcelain` 有输出，应先确认这些修改
是否就是本次准备发布的内容，不要把不明改动打入固件。

## 5. 构建入口和关键配置

### 5.1 PlatformIO 配置

- `platformio.ini`
  - 源码目录：`Marlin`
  - 默认环境：`mega2560`
- `ini/avr.ini`
  - 平台：`atmelavr@~4.0.1`
  - CPU：16 MHz
  - C++ 标准：GNU++17
- `Marlin/config.ini`
  - 当前 `ini_use_config = none`
  - 不会在构建前覆盖 `Configuration.h`

不要把 `Marlin/config.ini` 中的示例 `config:minimal` 当成本机实际配置。当前有效配置
直接来自下面两个头文件。

### 5.2 机器主配置

`Marlin/Configuration.h` 保存：

- RAMPS 1.4 EFB、串口和波特率。
- A4988 驱动、XYZ/E0 方向。
- 步数、最大速度、加速度和 Jerk。
- 热敏电阻、PID、温度限制和热保护。
- X/Y `0–125 mm`、Z `0–160 mm` 软件行程。
- 固定探针、Z-MIN 共用、X+26/Y+20 探针偏移。
- 线性 3 × 3 自动调平和安全 Z 回零。
- D19 断料传感器、内部上拉、LOW 触发。
- EEPROM、PLA/ABS 预热、中文、SD 和 12864 LCD。

`Marlin/Configuration_adv.h` 保存：

- SD 掉电恢复及默认启用状态。
- M600 Advanced Pause 参数。
- 换料暂停期间 XYZ 电机持续上电。
- SD 连接和其他高级行为。

### 5.3 版本和中文

- `Marlin/_Version.h`
  - 固件版本、机器名、源码地址和发布日期。
- `Marlin/src/lcd/language/language_zh_CN.h`
  - 简体中文菜单和状态文本。
- `Marlin/src/lcd/dogm/fontdata/langdata_zh_CN.h`
  - 12864 中文字形数据。

修改中文文本时，如果所有汉字都已在原语言文件中使用过，现有字库通常已经包含
对应字形。如果引入了新的汉字，必须在带 Bash、`cc` 和 `make` 的 POSIX 环境中
重新生成字库：

```bash
cd Marlin
../buildroot/share/fonts/genallfont.sh zh_CN
```

生成后应检查并提交 `Marlin/src/lcd/dogm/fontdata/langdata_zh_CN.h`。仅修改语言文本
但漏掉新字形时，代码可能编译成功，LCD 却显示空白或缺字。

## 6. 构建固件

### 6.1 干净构建

在仓库根目录执行：

```powershell
python -m platformio run -e mega2560 -t clean
python -m platformio run -e mega2560
```

当前已验证构建结果为：

```text
RAM:   65.6% (5374 / 8192 bytes)
Flash: 67.8% (172064 / 253952 bytes)
```

构建成功后主要产物位于：

```text
.pio/build/mega2560/firmware.hex
.pio/build/mega2560/firmware.elf
```

- `firmware.hex`：用于刷写 ATmega2560，必须放入二进制发布包。
- `firmware.elf`：包含符号和调试信息，仅维护或排查问题时需要。

构建目录 `.pio` 是缓存目录，不应提交到 Git。

### 6.2 构建失败的常见原因

- 没有在仓库根目录执行命令。
- 使用了错误的 PlatformIO 环境，而不是 `mega2560`。
- 首次构建时无法联网下载平台、工具链或 U8glib-HAL。
- Python 或 PlatformIO 安装损坏。
- 修改配置后超过 ATmega2560 的 RAM 或 Flash 限制。
- 修改中文时破坏了 UTF-8 文件编码或字符串语法。

可以查看依赖解析结果：

```powershell
python -m platformio pkg list -e mega2560
```

## 7. 发布前检查

正式打包前至少完成以下检查：

```powershell
git status --porcelain
git diff --check
python -m platformio run -e mega2560
```

要求：

- `git status --porcelain` 没有非预期输出。
- `git diff --check` 没有空白字符错误。
- PlatformIO 输出 `SUCCESS`。
- RAM 和 Flash 未超过容量。
- `Marlin/_Version.h` 中的版本和日期符合本次发布。
- 维护文档中的配置、构建结果和实机验收状态已经更新。

如果本次发布包含配置或代码修改，应先提交，再从提交后的干净工作树重新构建：

```powershell
git add <本次文件>
git commit -m "描述本次发布内容"
python -m platformio run -e mega2560 -t clean
python -m platformio run -e mega2560
```

这样源码包中的提交与二进制固件能够一一对应。

## 8. 制作发布包

建议每次发布同时生成：

1. **二进制包**：给刷机人员使用。
2. **对应源码包**：用于 GPL 合规、复现构建和后续维护。
3. **SHA-256 校验文件**：确认下载或复制后文件没有损坏。

以下 PowerShell 命令在仓库根目录执行。`Release` 已被 `.gitignore` 忽略。

### 8.1 设置包名

```powershell
$VersionLine = Select-String -LiteralPath "Marlin/_Version.h" -Pattern '#define SHORT_BUILD_VERSION "([^"]+)"'
$Version = $VersionLine.Matches[0].Groups[1].Value
$Commit = (git rev-parse --short=8 HEAD).Trim()
$Date = Get-Date -Format "yyyyMMdd"
$PackageName = "Marlin_${Version}_${Date}_${Commit}"
$ReleaseRoot = Join-Path $PWD "Release"
$BinaryDir = Join-Path $ReleaseRoot "${PackageName}-binary"

New-Item -ItemType Directory -Force -Path $BinaryDir | Out-Null
```

### 8.2 收集二进制和配置

```powershell
Copy-Item ".pio/build/mega2560/firmware.hex" $BinaryDir
Copy-Item "Marlin/Configuration.h" $BinaryDir
Copy-Item "Marlin/Configuration_adv.h" $BinaryDir
Copy-Item "Marlin/_Version.h" $BinaryDir
Copy-Item "LICENSE" $BinaryDir
Copy-Item "docs/MiniTree_T3_Marlin_lts-2.1.2_迁移审计.md" $BinaryDir
Copy-Item "docs/MiniTree_T3_构建与发布打包指南.md" $BinaryDir
```

`firmware.elf` 默认不放入普通刷机包。如需保留调试符号，可以额外复制：

```powershell
Copy-Item ".pio/build/mega2560/firmware.elf" $BinaryDir
```

### 8.3 写入构建信息

```powershell
$Branch = (git branch --show-current).Trim()
$FullCommit = (git rev-parse HEAD).Trim()
$FirmwareHash = (Get-FileHash (Join-Path $BinaryDir "firmware.hex") -Algorithm SHA256).Hash

@(
  "Firmware: $Version"
  "Board: RAMPS 1.4 EFB / ATmega2560"
  "PlatformIO environment: mega2560"
  "Branch: $Branch"
  "Commit: $FullCommit"
  "Build date: $(Get-Date -Format 'yyyy-MM-dd HH:mm:ss zzz')"
  "firmware.hex SHA256: $FirmwareHash"
) | Set-Content -LiteralPath (Join-Path $BinaryDir "BUILD-INFO.txt") -Encoding utf8
```

### 8.4 压缩二进制包

```powershell
$BinaryZip = Join-Path $ReleaseRoot "${PackageName}-binary.zip"
Compress-Archive -Path "$BinaryDir\*" -DestinationPath $BinaryZip -Force
```

### 8.5 生成对应源码包

使用 `git archive` 从当前提交生成源码包，避免把 `.pio`、临时文件和未提交改动带入：

```powershell
$SourceZip = Join-Path $ReleaseRoot "${PackageName}-source.zip"
git archive --format=zip --output="$SourceZip" HEAD
```

源码包包含当前提交中的 Marlin 源码、机器配置、版本文件、许可证和维护文档。

### 8.6 生成发布包校验文件

```powershell
$ChecksumFile = Join-Path $ReleaseRoot "${PackageName}-SHA256SUMS.txt"
$Files = @($BinaryZip, $SourceZip)

$ChecksumLines = foreach ($File in $Files) {
  $Hash = Get-FileHash -LiteralPath $File -Algorithm SHA256
  "$($Hash.Hash)  $([IO.Path]::GetFileName($File))"
}

$ChecksumLines | Set-Content -LiteralPath $ChecksumFile -Encoding ascii
Get-Content -LiteralPath $ChecksumFile
```

最终 `Release` 目录应至少包含：

```text
Marlin_<版本>_<日期>_<提交>-binary.zip
Marlin_<版本>_<日期>_<提交>-source.zip
Marlin_<版本>_<日期>_<提交>-SHA256SUMS.txt
```

## 9. 校验发布包

在另一目录解压二进制包并重新计算哈希：

```powershell
$TestDir = Join-Path $env:TEMP "MiniTree_T3_release_test"
New-Item -ItemType Directory -Force -Path $TestDir | Out-Null
Expand-Archive -LiteralPath $BinaryZip -DestinationPath $TestDir -Force
Get-FileHash -LiteralPath (Join-Path $TestDir "firmware.hex") -Algorithm SHA256
Get-Content -LiteralPath (Join-Path $TestDir "BUILD-INFO.txt")
```

计算结果应与 `BUILD-INFO.txt` 中的 `firmware.hex SHA256` 一致。还应确认源码包能够
解压，并包含 `platformio.ini`、`Marlin/Configuration.h`、
`Marlin/Configuration_adv.h` 和 `Marlin/_Version.h`。

## 10. 上传固件

连接 Mega2560，确认串口号后可由 PlatformIO 上传：

```powershell
python -m platformio run -e mega2560 -t upload --upload-port COM3
```

将 `COM3` 替换为实际端口。上传前关闭占用串口的 Pronterface、Repetier-Host、
OctoPrint 串口连接或其他终端。

仅有发布包时，可使用支持 ATmega2560 的图形化刷写工具加载 `firmware.hex`。
目标芯片必须选择 ATmega2560，不能按 ATmega1280 或其他主板刷写。

## 11. 刷机前后操作

刷机前先从旧固件保存现场 EEPROM 参数，详细步骤见迁移审计文档。至少保存：

- `M92` 步数。
- `M203` 最大速度。
- `M201`、`M204` 加速度。
- 热端和热床 PID。
- `M851` 探针 Z 偏移。
- Home Offset 和其他现场调校值。

刷入新版后执行：

```gcode
M502
M500
M503 S0
```

然后依次完成 `M119`、低速点动、G28、G29、M851、温控、M600、断料、SD、
掉电恢复和 LCD 验收。在探针 Z 偏移、限位极性和电机方向没有确认前，不要直接
开始正式打印。

## 12. 发布记录建议

每个正式发布至少记录：

- 固件版本和发布日期。
- Git 完整提交号。
- `firmware.hex` SHA-256。
- PlatformIO 构建结果和容量占用。
- 相对上一版的配置或功能变化。
- 已完成和未完成的实机测试。
- 是否需要执行 `M502`、重新标定 M851 或重新整定 PID。

二进制包、源码包、校验文件和实机验收记录应一起归档。仅保存 `firmware.hex`
会导致后续难以确认它对应哪一版源码和机器配置。
