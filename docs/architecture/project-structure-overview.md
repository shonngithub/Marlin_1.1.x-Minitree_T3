# 项目结构总览（MiniTree T3 / Marlin 1.1.x）

## 1. 根目录功能划分

- `Marlin/`
  - 核心固件源码目录（配置、运动控制、温控、LCD、G-code、引脚定义等）。
- `buildroot/`
  - 构建与脚本工具目录（打包、脚本、资源、构建辅助）。
- `platformio.ini`
  - PlatformIO 构建入口与环境配置。
- `process-palette.json`
  - 项目流程/调色板配置文件（与构建流程相关）。
- `docs/`
  - 项目分析与迁移文档（本次已按模块分类）。

## 2. `Marlin/` 关键模块（按功能）

- 配置层
  - `Configuration.h`
  - `Configuration_adv.h`
  - `Version.h`
- 运动与步进
  - `planner.cpp/.h`
  - `stepper.cpp/.h`
  - `Marlin_main.cpp`（部分 G-code/流程逻辑）
- 温控
  - `temperature.cpp/.h`
- LCD 与语言
  - `ultralcd*.h/.cpp`
  - `language_*.h`
  - `utf_mapper.h`
- 持久化与参数存储
  - `configuration_store.cpp`
- 硬件引脚
  - `pins_*.h`

## 3. 当前文档目录分类（优化后）

- `docs/architecture/`
  - 项目结构与模块说明。
- `docs/customizations/`
  - 1.1.x 定制点记录。
- `docs/migration/`
  - 2.x 迁移计划与步骤。
- `docs/status/`
  - 本地环境状态、命令与验证日志。

## 4. 打包兼容性说明

本次“结构优化”仅对 `docs/` 目录做分类整理，不修改 `Marlin/`、`buildroot/`、`platformio.ini` 等构建关键路径，
因此不会影响固件打包与编译流程。
