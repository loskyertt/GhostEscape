# src/utility/CMakeLists.txt —— utility 模块：通用工具（日志/单例）
#
# 该模块不依赖任何游戏模块，可独立编译、独立测试。

add_library(utility STATIC
        logger/logger.cpp
)

# include 根目录为 src/，统一使用 "#include "utility/xxx.h"" 形式引用
target_include_directories(utility
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..
)

# logger.cpp 使用 localtime/rename 等 CRT 接口，屏蔽 MSVC 安全告警
if(MSVC)
    target_compile_definitions(utility PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

# 单元测试
add_subdirectory(tests)
