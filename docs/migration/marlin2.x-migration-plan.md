# Marlin 2.x 迁移计划（MiniTree T3）

## 状态说明
- 上游仓库地址：https://github.com/MarlinFirmware/Marlin
- 当前环境无法访问上游 Marlin 2.x 仓库（HTTP 403），因此不能自动创建基于上游的 `marlin2.x` 分支。
- 一旦网络可用，请按下面步骤获取 `bugfix-2.0.x` 并迁移 MiniTree T3 的定制改动。

## 建议的分支创建方式（网络可用时执行）
```sh
# 示例（需要网络访问）：
# git remote add upstream https://github.com/MarlinFirmware/Marlin.git
# git fetch upstream
# git checkout -b marlin2.x upstream/bugfix-2.0.x
```

## 定制改动迁移清单

### A) 配置文件
**文件（Marlin 2.x 路径）：**
- `Marlin/Configuration.h`
- `Marlin/Configuration_adv.h`

**迁移要点：**
- MiniTree 品牌信息（作者、开机信息、URL、机型名）、LCD 语言与字符集。
- 运动参数（步进、加速度、加加速度/抖动、平台尺寸、归零偏移）。
- 温控设置（热床传感器、热端/热床 PID、温度上下限）。
- 功能开关：EEPROM、断料检测、高级暂停/换料、断电续打、喷嘴停靠、线性调平、SD 支持、LCD 控制器、软限位菜单项。

### B) EEPROM 格式与设置
**文件（Marlin 2.x 路径）：**
- `Marlin/src/module/settings.cpp`
- `Marlin/src/module/settings.h`
- `Marlin/src/module/planner.*`

**迁移要点：**
- EEPROM 版本号格式（自定义）及动态长度。
- 设置结构体新增字段：
  - 各轴电机方向（`planner.invert_dir`）。
  - 旋钮方向（`planner.encoder_dir`）。
  - 归零 XY 目标坐标（`planner.homing_des`）。
- 在重置流程中设置读写默认值。

### C) 运动与步进
**文件（Marlin 2.x 路径）：**
- `Marlin/src/module/stepper.cpp`
- `Marlin/src/module/stepper.h`

**迁移要点：**
- 步进方向使用 `planner.invert_dir`。
- 新增方向刷新函数，便于 EEPROM 修改后实时生效。
- 保留单挤出机的方向覆盖逻辑，必要时兼顾多挤出机。

### D) LCD / 菜单
**文件（Marlin 2.x 路径）：**
- `Marlin/src/lcd/ultralcd.cpp`（或新版 `Marlin/src/lcd/menu/`）
- `Marlin/src/lcd/language/language_zh_CN.h`
- `Marlin/src/lcd/utf_mapper.h`

**迁移要点：**
- 新增 MiniTree 设置菜单：
  - 电机方向
  - 旋钮方向
  - 归零 XY
  - 冷挤出开关
  - EEPROM 操作
- 旋钮方向改为运行时可配置（使用 `planner.encoder_dir`）。
- 中文字符映射与字库映射（`MAPPER_HASHCN`）同步到 2.x。

### E) G-code 与归零
**文件（Marlin 2.x 路径）：**
- `Marlin/src/gcode/gcode.cpp`
- `Marlin/src/gcode/geometry/G28.cpp`
- `Marlin/src/gcode/temperature/M109.cpp`

**迁移要点：**
- G28 归零后自动开启调平。
- Z 安全归零使用 `planner.homing_des` 的 XY 位置。
- 若需要 WiFi 模块对接，保留 `X1` 自定义 G-code。
- M109/M190 加热时在 LCD 显示当前打印文件名。

### F) 温度相关逻辑
**文件（Marlin 2.x 路径）：**
- `Marlin/src/module/temperature.cpp`
- `Marlin/src/module/temperature.h`

**迁移要点：**
- 默认允许冷挤出（如需求一致）。
- 热床温度为负时的钳制逻辑（需确认与 2.x 热保护机制兼容）。

### G) 显示时序与开机图
**文件（Marlin 2.x 路径）：**
- `Marlin/src/lcd/dogm/`（ST7920 时序与自定义位图）

**迁移要点：**
- 如需保留，应用 ST7920 延时参数调整。
- 添加 `Marlin/_Bootscreen.h` 并启用自定义开机图。

### H) 引脚定义
**文件（Marlin 2.x 路径）：**
- `Marlin/src/pins/ramps/pins_RAMPS.h`

**迁移要点：**
- 移除 Y/Z 最大限位引脚定义，断料检测改为 19。

## 兼容性验证（建议）
- 使用 PlatformIO 编译目标板（RAMPS/ATmega2560），确认结构调整后能成功构建。
- 上电后执行 `M502` + `M500`，确保新 EEPROM 字段完成初始化。
- 验证 LCD 菜单、旋钮方向、归零目标位置等行为是否正确。

