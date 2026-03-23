# GhostEscape - UML Class Diagram

```mermaid
classDiagram
    direction TB

    namespace core {
        class Object {
            #Game& m_game
            #vector~unique_ptr~Object~ m_children
            #bool m_is_activive
            #bool m_need_remove
            +init()
            +handleEvents(SDL_Event&)
            +update(float)
            +render()
            +clean()
            +addObject(unique_ptr~Object~)
            +removeObject(Object*)
        }

        class ObjectAffiliate {
            #ObjectScreen* m_parent
            #vec2 m_offset
            #vec2 m_size
            #Anchor m_anchor
            +getParent() ObjectScreen*
            +getOffset() vec2
            +getSize() vec2
            +setSize(vec2)
            +setAnchor(Anchor)
            +setScale(float)
        }

        class ObjectScreen {
            #vec2 m_render_postion
            +getRenderPosition() vec2
            +getPosition() vec2 <<virtual>>
            +setRenderPosition(vec2)
        }

        class ObjectWorld {
            #vec2 m_position
            #Collider* m_collider
            +update(float) <<override>>
            +getPosition() vec2 <<override>>
            +getCollider() Collider*
            +setPosition(vec2)
            +setCollider(Collider*)
        }

        class Scene {
            #vec2 m_world_size
            #vec2 m_camera_position
            #vector~unique_ptr~ObjectScreen~ m_children_screen
            #vector~unique_ptr~ObjectWorld~ m_children_world
            +init()
            +handleEvents(SDL_Event&)
            +update(float)
            +render()
            +clean()
            +worldToScreen(vec2) vec2
            +screenToWorld(vec2) vec2
            +addObjectScreen(unique_ptr~ObjectScreen~)
            +addObjectWorld(unique_ptr~ObjectWorld~)
        }

        class Anchor {
            <<enumeration>>
            NONE
            TOP_LEFT
            TOP_CENTER
            TOP_RIGHT
            MIDDLE_LEFT
            MIDDLE_CENTER
            MIDDLE_RIGHT
            BOTTOM_LEFT
            BOTTOM_CENTER
            BOTTOM_RIGHT
        }

        class Actor {
            #States* m_states
            #vec2 m_velocity
            #float m_max_speed
            +move(float)
            +takeDamage(float)
            +isAlive() bool
            +getStates() States*
            +setVelocity(vec2)
        }

        class AssetStore {
            -SDL_Renderer* m_renderer
            -MIX_Mixer* m_mixer
            -unordered_map~string, SDL_Texture*~ m_textures
            -unordered_map~string, MIX_Audio*~ m_sounds
            -unordered_map~string, TTF_Font*~ m_fonts
            +clean()
            +loadImage(string)
            +loadSound(string, bool)
            +loadFont(string, float)
            +getImage(string) SDL_Texture*
            +getSound(string) MIX_Audio*
            +getFont(string, float) TTF_Font*
        }

        class Game {
            <<singleton>>
            -Game()
            -bool m_is_running
            -vec2 m_screen_size
            -SDL_Window* m_window
            -SDL_Renderer* m_renderer
            -MIX_Mixer* m_mixer
            -Scene* m_current_scene
            -AssetStore* m_asset_store
            -Uint64 m_FPS
            -float m_delta_time
            +getInstance() Game& <<static>>
            +init(string, int, int)
            +run()
            +getCurrentScene() Scene*
            +getAssetStore() AssetStore*
        }
    }

    namespace affiliate {
        class Sprite {
            -Texture m_texture
            -bool m_is_finished
            +render()
            +addSpriteToObjects() Sprite* <<static>>
            +getTexture() Texture
            +setTexture(Texture)
            +setFlip(bool)
            +setAngle(float)
        }

        class Texture {
            +SDL_Texture* texture
            +SDL_FRect src_rect
            +float angle
            +bool is_flip
        }

        class SpriteAnim {
            -int m_current_frame
            -int m_total_frames
            -int m_fps
            -float m_frame_interval
            -float m_frame_timer
            -bool m_is_loop
            +update(float) <<override>>
            +setTexture(Texture) <<override>>
            +addSpriteAnimToObjects() SpriteAnim* <<static>>
            +getCurrentFrame() int
            +setFPS(int)
            +setIsLoop(bool)
        }

        class Collider {
            -Type m_type
            +render()
            +addCollider() Collider* <<static>>
            +isColliding(Collider*) bool
            +getType() Type
            +setType(Type)

            class Type {
                <<enumeration>>
                CIRCLE
                RECTANGLE
            }
        }
    }

    namespace raw {
        class States {
            -Actor* m_parent
            -float m_health
            -float m_max_health
            -float m_mana
            -float m_max_mana
            -float m_mana_regen
            -float m_damage
            -bool m_is_alive
            -float m_invincibility_duration
            -float m_invincibility_timer
            -bool m_is_invincible
            +update(float)
            +canUseMana(float) bool
            +useMana(float)
            +regenMana(float)
            +takeDamage(float)
            +addStates() States* <<static>>
            +getHealth() float
            +getIsAlive() bool
        }
    }

    namespace world {
        class Effect {
            -SpriteAnim* m_sprite_anim
            -unique_ptr~ObjectWorld~ m_next_object
            +update(float)
            +checkFinish()
            +addEffectToObjects() Effect* <<static>>
            +getSpriteAnim() SpriteAnim*
            +setNextObject(unique_ptr~ObjectWorld~)
        }
    }

    class Player {
        -SpriteAnim* sprite_idle
        -SpriteAnim* sprite_move
        -bool m_is_moving
        +init()
        +handleEvents(SDL_Event&)
        +update(float)
        +render()
        +clean()
        +keyboardControl()
        +syncCamera()
        +checkState()
        +changeState(bool)
    }

    class Enemy {
        -Player* m_target_player
        -SpriteAnim* m_current_anim
        -SpriteAnim* m_anim_normal
        -SpriteAnim* m_anim_hurt
        -SpriteAnim* m_anim_die
        -State m_current_state
        +init()
        +update(float)
        +aimTargetPlayer(Player*)
        +checkState()
        +changeState(State)
        +remove()
        +attack()

        class State {
            <<enumeration>>
            NORMAL
            HURT
            DEAD
        }
    }

    class SceneMain {
        -Player* m_player
        +init()
        +handleEvents(SDL_Event&)
        +update(float)
        +render()
        +clean()
        -renderBackground()
    }

    ' ============================================================================
    ' Inheritance Relationships
    ' ============================================================================

    Object <|-- ObjectAffiliate : inherits
    Object <|-- Scene : inherits
    ObjectAffiliate <|-- ObjectScreen : inherits
    ObjectAffiliate <|-- Sprite : inherits
    ObjectAffiliate <|-- Collider : inherits
    Sprite <|-- SpriteAnim : inherits
    ObjectScreen <|-- ObjectWorld : inherits
    ObjectWorld <|-- Actor : inherits
    Actor <|-- Player : inherits
    Actor <|-- Enemy : inherits
    ObjectWorld <|-- Effect : inherits
    Scene <|-- SceneMain : inherits

    ' ============================================================================
    ' Composition Relationships
    ' ============================================================================

    Game *-- Scene : m_current_scene
    Game *-- AssetStore : m_asset_store
    Scene o-- ObjectScreen : m_children_screen
    Scene o-- ObjectWorld : m_children_world
    Object *-- Object : m_children
    ObjectAffiliate o-- ObjectScreen : m_parent
    ObjectWorld *-- Collider : m_collider
    Actor o-- States : m_states
    Player o-- SpriteAnim : sprites
    Enemy o-- Player : m_target_player
    Enemy o-- SpriteAnim : animations
    Effect o-- SpriteAnim : m_sprite_anim
    Effect o-- ObjectWorld : m_next_object
    SceneMain o-- Player : m_player
    Sprite o-- Texture : m_texture
```

---

## 类图说明 / Class Diagram Explanation

### 项目概述 / Project Overview
**GhostEscape** 是一个基于 SDL3 的 2D 游戏项目，采用了面向对象的设计模式。

### 核心架构 / Core Architecture

```
Game (Singleton)
    └── Scene
        ├── ObjectScreen (屏幕空间对象)
        │   └── ObjectWorld (世界空间对象)
        │       ├── Actor
        │       │   ├── Player
        │       │   └── Enemy
        │       └── Effect
        └── ObjectAffiliate (组件)
            ├── Sprite
            ├── SpriteAnim
            └── Collider
```

### 类层次结构 / Class Hierarchy

| 层级 | 类名 | 说明 |
|------|------|------|
| **基础层** | `Object` | 所有游戏对象的基类，提供生命周期管理 |
| **空间层** | `ObjectScreen` | 屏幕空间对象（固定在屏幕） |
| | `ObjectWorld` | 世界空间对象（随世界移动） |
| **实体层** | `Actor` | 游戏角色基类（玩家、敌人） |
| **组件层** | `ObjectAffiliate` | 可附加到对象的组件 |
| | `Sprite` | 精灵图渲染组件 |
| | `SpriteAnim` | 精灵动画组件 |
| | `Collider` | 碰撞检测组件 |
| | `States` | 角色状态（生命值、法力等） |

### 设计模式 / Design Patterns

1. **单例模式 (Singleton)**: `Game` 类确保全局只有一个游戏实例
2. **组合模式 (Composite)**: `Object` 使用 `m_children` 管理子对象
3. **组件模式 (Component)**: 对象通过附加组件实现功能
4. **工厂方法**: 各组件提供 `addXxxToObjects()` 静态方法创建实例

### 渲染流程 / Render Pipeline

```
Game.run()
    └── Game.update()
        └── Scene.update()
            ├── ObjectScreen.update()
            │   └── Sprite.render() / SpriteAnim.render()
            └── ObjectWorld.update()
                ├── Actor.update()
                │   └── States.update()
                └── Collider.render() (调试)
```

### 碰撞检测 / Collision Detection

- `Collider` 支持两种类型: `CIRCLE` 和 `RECTANGLE`
- 通过 `isColliding()` 方法检测碰撞
- 调试模式下可通过 `Game.renderColliders()` 可视化碰撞体
