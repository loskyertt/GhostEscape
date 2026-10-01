cmake_minimum_required(VERSION 3.20.0)

project(GhostEscape VERSION 0.0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# MSVC 中文路径兼容；/Zc:preprocessor 支持日志宏的可变参数逗号省略（##__VA_ARGS__）
if (MSVC)
    add_compile_options(/utf-8 /Zc:preprocessor)
endif ()

if (MSVC)
    list(APPEND CMAKE_PREFIX_PATH
            "${CMAKE_SOURCE_DIR}/3rdparty/glm-1.0.3/share"
            "${CMAKE_SOURCE_DIR}/3rdparty/SDL3-3.4.2/cmake"
            "${CMAKE_SOURCE_DIR}/3rdparty/SDL3_image-3.4.0/cmake"
            "${CMAKE_SOURCE_DIR}/3rdparty/SDL3_mixer-3.2.0/cmake"
            "${CMAKE_SOURCE_DIR}/3rdparty/SDL3_ttf-3.2.2/cmake"
    )
endif ()

find_package(glm REQUIRED)
find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(SDL3_mixer REQUIRED)
find_package(SDL3_ttf REQUIRED)

# CMake Script
 include(cmake/find_target.cmake)

add_subdirectory(src)
add_subdirectory(examples)
