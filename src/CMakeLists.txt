# src/CMakeLists.txt —— 游戏本体（GhostEscape）
#
# 模块划分与依赖层次（自底向上，单向依赖，禁止反向引用）：
#
#   utility     通用工具：日志（logger）、单例（singleton）
#      ↑
#   engine      引擎核心：对象体系（Object/ObjectScreen/ObjectWorld/ObjectAffiliate）、
#               场景（Scene/Entity）、主循环（Game）、资源管理（AssetStore）
#      ↑
#   components  挂件组件：精灵（Sprite/SpriteAnim）、碰撞体（Collider）、
#               血量条（AffiliateBar）、文本标签（TextLable）
#      ↑
#   world       世界空间对象：法术（Spell）、特效（Effect）
#      ↑
#   mechanics   游戏机制：状态（States）、武器（Weapon）、计时器（Timer）、背景星空（BackgroundStar）
#      ↑
#   hud         屏幕空间 UI：HUD 面板（HUDStates/HUDSkill/HUDText/HUDButton）、鼠标指针（UIMouse）
#      ↑
#   game        游戏玩法逻辑：玩家（Player）、敌人（Enemy）、刷怪器（Spawner）、
#               雷击武器（WeaponThunder）、游戏场景（SceneMain/SceneTitle）
#
# 头文件引用统一使用 "#include "<module>/<File>.h"" 形式（include 根目录为 src/）。

set(TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

# ==========================================
# utility 模块：通用工具（日志/单例），不依赖任何游戏模块
# ==========================================
add_subdirectory(utility)

# ==========================================
# engine 模块：引擎核心
# ==========================================
add_library(engine STATIC
        engine/AssetStore.cpp
        engine/Entity.cpp
        engine/Game.cpp
        engine/Object.cpp
        engine/ObjectAffiliate.cpp
        engine/ObjectScreen.cpp
        engine/ObjectWorld.cpp
        engine/Scene.cpp
)
target_include_directories(engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(engine
        PUBLIC    # SDL、GLM 为引擎的公共依赖
        ${SDL3_LIBRARIES}
        SDL3_image::SDL3_image
        SDL3_mixer::SDL3_mixer
        SDL3_ttf::SDL3_ttf
        glm::glm
        PRIVATE   # 仅 Game.cpp 内部使用日志工具
        utility
)

# ==========================================
# components 模块：挂件组件
# ==========================================
add_library(components STATIC
        components/AffiliateBar.cpp
        components/Collider.cpp
        components/Sprite.cpp
        components/SpriteAnim.cpp
        components/TextLable.cpp
)
target_include_directories(components PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(components
        PUBLIC engine
)

# ==========================================
# world 模块：世界空间对象（法术/特效）
# ==========================================
add_library(world STATIC
        world/Effect.cpp
        world/Spell.cpp
)
target_include_directories(world PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(world
        PUBLIC
        engine
        components
)

# ==========================================
# mechanics 模块：游戏机制（状态/武器/计时器/背景星空）
# ==========================================
add_library(mechanics STATIC
        mechanics/BackGroundStar.cpp
        mechanics/States.cpp
        mechanics/Timer.cpp
        mechanics/Weapon.cpp
)
target_include_directories(mechanics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(mechanics
        PUBLIC
        engine
        components
        world
)

# ==========================================
# hud 模块：屏幕空间 UI
# ==========================================
add_library(hud STATIC
        hud/HUDButton.cpp
        hud/HUDSkill.cpp
        hud/HUDStates.cpp
        hud/HUDText.cpp
        hud/UIMouse.cpp
)
target_include_directories(hud PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(hud
        PUBLIC
        engine
        components
        mechanics
)

# ==========================================
# game 模块：游戏玩法逻辑（依赖以上全部模块）
# ==========================================
add_library(game STATIC
        game/Enemy.cpp
        game/Player.cpp
        game/SceneMain.cpp
        game/SceneTitle.cpp
        game/Spawner.cpp
        game/WeaponThunder.cpp
)
target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(game
        PUBLIC
        engine
        components
        world
        mechanics
        hud
)

# ==========================================
# 主可执行文件
# ==========================================
add_executable(${TARGET} main.cpp)
target_link_libraries(${TARGET} PRIVATE game)

# Debug 配置下启用调试宏
target_compile_definitions(${TARGET} PRIVATE
        $<$<CONFIG:Debug>:_DEBUG>
)
