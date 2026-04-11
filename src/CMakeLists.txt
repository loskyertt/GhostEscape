# src/CMakeLists.txt

set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

# ==========================================
# utils 模块：通用工具组件
# 必须先于 core 定义，因为 core 依赖 utils
# ==========================================
add_library(utils STATIC
  # affiliate（视觉/碰撞组件）
  utils/impl/affiliate/Collider.cpp
  utils/impl/affiliate/Sprite.cpp
  utils/impl/affiliate/SpriteAnim.cpp
  utils/impl/affiliate/AffiliateBar.cpp
  utils/impl/affiliate/TextLable.cpp
  # raw（游戏机制：状态/武器）
  utils/impl/raw/States.cpp
  utils/impl/raw/Weapon.cpp
  # screen（屏幕空间 UI）
  utils/impl/screen/UIMouse.cpp
  utils/impl/screen/HUDStates.cpp
  utils/impl/screen/HUDSkill.cpp
  # world（世界空间对象：法术/特效）
  utils/impl/world/Effect.cpp
  utils/impl/world/Spell.cpp
)

# utils 包含目录
target_include_directories(utils
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/utils/include
    ${CMAKE_CURRENT_SOURCE_DIR}/core/include
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
  core/impl/AssetStore.cpp
  core/impl/Entity.cpp
  core/impl/Game.cpp
  core/impl/Object.cpp
  core/impl/ObjectAffiliate.cpp
  core/impl/ObjectScreen.cpp
  core/impl/ObjectWorld.cpp
  core/impl/Scene.cpp
  # 游戏逻辑实现
  core/impl/game/Enemy.cpp
  core/impl/game/Player.cpp
  core/impl/game/SceneMain.cpp
  core/impl/game/Spawner.cpp
  core/impl/game/WeaponThunder.cpp
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
