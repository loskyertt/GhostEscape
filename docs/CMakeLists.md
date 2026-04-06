# CMakeLists.txt 参考文档

本文档提供基于新项目结构的完整 CMake 构建配置参考。

---

## 1. 根目录 CMakeLists.txt

```cmake
# ==========================================
# 顶层 CMakeLists.txt
# GhostEscape 游戏项目
# ==========================================

cmake_minimum_required(VERSION 3.20.0)

# 项目配置
project(geometry_app VERSION 0.0.1 LANGUAGES C CXX)

# ==========================================
# 语言标准配置
# ==========================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

# 导出编译命令（用于 clangd、IDE 支持）
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# MSVC 中文路径兼容
if(MSVC)
  add_compile_options(/utf-8)
endif()

# ==========================================
# 第三方库查找配置
# ==========================================
if(MSVC)
  list(APPEND
    CMAKE_PREFIX_PATH
      "${CMAKE_SOURCE_DIR}/3rdparty/SDL3-3.4.2/cmake"
      "${CMAKE_SOURCE_DIR}/3rdparty/SDL3_image-3.4.0/cmake"
      "${CMAKE_SOURCE_DIR}/3rdparty/SDL3_mixer-3.2.0/cmake"
      "${CMAKE_SOURCE_DIR}/3rdparty/SDL3_ttf-3.2.2/cmake"
  )
endif()

# SDL 库（主库）
find_package(SDL3 REQUIRED)

# SDL 扩展库
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)

# GLM 数学库（头文件库，直接添加子目录）
add_subdirectory(${CMAKE_SOURCE_DIR}/3rdparty/glm-1.0.3)

# ==========================================
# 自定义 CMake 模块（可选）
# ==========================================
# include(cmake/checkArch.cmake)

# ==========================================
# 子模块
# ==========================================
add_subdirectory(src)

# 测试模块（可选）
# add_subdirectory(tests)

# 示例程序模块（可选）
# add_subdirectory(examples)
```

---

## 2. src/CMakeLists.txt

```cmake
# ==========================================
# src/CMakeLists.txt
# 源码构建配置
# ==========================================

# 可执行文件名（平台适配）
set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

# ==========================================
# utils 模块：通用工具组件
# 必须先于 core 定义，因为 core 依赖 utils
# ==========================================
add_library(utils STATIC
  # affiliate（视觉/碰撞组件）
  src/utils/impl/affiliate/Collider.cpp
  src/utils/impl/affiliate/Sprite.cpp
  src/utils/impl/affiliate/SpriteAnim.cpp
  # raw（游戏机制：状态/武器）
  src/utils/impl/raw/States.cpp
  src/utils/impl/raw/Weapon.cpp
  # screen（屏幕空间 UI）
  src/utils/impl/screen/UIMouse.cpp
  # world（世界空间对象：法术/特效）
  src/utils/impl/world/Effect.cpp
  src/utils/impl/world/Spell.cpp
)

# utils 包含目录
target_include_directories(utils
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/include
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/impl
)

# utils 链接库（SDL、GLM 作为 utils 的公共依赖）
target_link_libraries(utils
  PUBLIC
    ${SDL3_LIBRARIES}
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
    SDL3_ttf::SDL3_ttf
    glm::glm
)

# ==========================================
# core 模块：引擎核心 + 游戏逻辑
# ==========================================
add_library(core STATIC
  # 引擎核心实现
  src/core/impl/AssetStore.cpp
  src/core/impl/Entity.cpp
  src/core/impl/Game.cpp
  src/core/impl/Object.cpp
  src/core/impl/ObjectAffiliate.cpp
  src/core/impl/ObjectScreen.cpp
  src/core/impl/ObjectWorld.cpp
  src/core/impl/Scene.cpp
  # 游戏逻辑实现
  src/core/impl/game/Enemy.cpp
  src/core/impl/game/Player.cpp
  src/core/impl/game/SceneMain.cpp
  src/core/impl/game/Spawner.cpp
  src/core/impl/game/WeaponThunder.cpp
)

# core 包含目录
target_include_directories(core
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/core/include
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/core/impl
    # utils 的公开头文件对 core 的游戏逻辑可见
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/include
)

# core 链接库
target_link_libraries(core
  PUBLIC
    # 引擎核心依赖 SDL、GLM
    ${SDL3_LIBRARIES}
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
    SDL3_ttf::SDL3_ttf
    glm::glm
  PRIVATE
    # core 的游戏逻辑依赖 utils
    utils
)

# ==========================================
# 主可执行文件
# ==========================================
add_executable(${TARGET} main.cpp)

# 主程序链接 core 和 utils
target_link_libraries(${TARGET} PRIVATE core utils)

# 运行时工作目录（可选：便于调试）
target_compile_definitions(${TARGET} PRIVATE
  $<$<CONFIG:Debug>:_DEBUG>
)
```

---

## 3. 关键设计说明

### 3.1 模块顺序

```
utils 必须在 core 之前定义
  ├── utils: 通用组件（不依赖 core 中的具体类）
  └── core:  引擎核心 + 游戏逻辑（依赖 utils）
```

### 3.2 包含目录策略

| 模块 | PUBLIC 目录 | PRIVATE 目录 |
|------|-------------|--------------|
| `utils` | `utils/include/` | `utils/impl/` |
| `core` | `core/include/` | `core/impl/` + `utils/include/` |

### 3.3 链接属性

- **utils**: SDL、GLM 等库使用 `PUBLIC`，因为 utils 的头文件会被 core 使用
- **core**: 对外暴露引擎接口使用 `PUBLIC`，内部游戏逻辑使用 `PRIVATE` 依赖 utils

---

## 4. 编译验证命令

```bash
# 使用 CMake 配置（Debug 模式）
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug

# 编译
cmake --build build

# 使用 MSVC
cmake -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Debug
```

---

## 5. 常见问题

### Q: LSP 提示头文件找不到？

- 确保 `.clangd` 或 IDE 配置了正确的 include 路径
- CMake 会自动生成 `compile_commands.json`，大部分现代 IDE 可自动识别

### Q: 如何添加新的源文件？

1. 在对应模块的 `impl/` 目录添加 `.cpp` 文件
2. 将文件路径添加到对应 `add_library()` 的文件列表中
3. 如果需要公开头文件，在 `include/` 目录添加 `.h` 文件
