cmake_minimum_required(VERSION 3.20.0)

# 项目配置
project(GhostEscape VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

# 导出编译命令（用于 clangd、IDE 支持）
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# MSVC 中文路径兼容
if(MSVC)
  add_compile_options(/utf-8)
endif()

# 第三方库查找配置
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

# 自定义 CMake 模块（可选）
# include(cmake/checkArch.cmake)

# 子模块
add_subdirectory(src)

# 测试模块（可选）
# add_subdirectory(tests)

# 示例程序模块（可选）
# add_subdirectory(examples)
