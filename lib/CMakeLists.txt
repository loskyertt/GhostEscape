# for each "lib/x.cpp", generate shared library or static library
message("CMakeLists.txt for lib directory")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 动态库：gamedll
add_library(gamedll SHARED
  core/AssetStore.cpp
  core/Game.cpp
  core/Object.cpp
  core/ObjectWorld.cpp
  core/Scene.cpp
  SceneMain.cpp
  Player.cpp
)

target_include_directories(gamedll PUBLIC ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(gamedll
  PUBLIC
    ${SDL3_LIBRARIES}
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
    SDL3_ttf::SDL3_ttf
    glm::glm
)

if(MSVC)
  set_target_properties(gamedll PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON) # 单独为 gamedll 启用 Windows 下的符号自动导出功能
  target_compile_options(gamedll PRIVATE /utf-8)  # UTF-8 支持
endif()

message(STATUS "--------------------------------------------\n")
