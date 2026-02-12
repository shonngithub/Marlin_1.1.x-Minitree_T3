# Workspace Layout（分类视图）

该目录用于按功能对项目进行分类整理，提升可读性。

> 说明：本目录主要使用**符号链接**聚合原始文件，
> 不改动原有构建路径（如 `Marlin/`、`buildroot/`、`platformio.ini`），
> 因此不会影响现有打包与编译流程。

## 目录分类

- `firmware/`
  - `Marlin`：固件核心源码

- `build/`
  - `platformio.ini`：PlatformIO 构建入口
  - `buildroot`：构建脚本与资源
  - `process-palette.json`：流程配置

- `project_meta/`
  - `README.md`：项目说明
  - `LICENSE`：许可证

- `documentation/`
  - `docs`：项目分析、迁移、状态文档

- `automation/`
  - `.github`：Issue 模板与仓库自动化配置
