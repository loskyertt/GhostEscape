/*
 * @File    :   lib\Player.cpp
 * @Time    :   2026/03/15 23:57:09
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/game/Player.h"
#include "core/game/SceneMain.h"
#include "core/Entity.h"

#include "world/Effect.h"
#include "affiliate/Collider.h"
#include "affiliate/SpriteAnim.h"
#include "raw/States.h"
#include "raw/Timer.h"

#include <glm/geometric.hpp>
#include <glm/common.hpp>
#include <glm/fwd.hpp>

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>

/* 初始化 */
void Player::init() {
  Entity::init();

  m_timer_flash = Timer::addTimer(this, 0.6f);
  m_timer_flash->start();

  m_max_speed = 500.0f;  // 设置玩家速度

  // === 测试 ===
  sprite_idle = SpriteAnim::addSpriteAnim(this, "assets/sprite/ghost-idle.png", 2.0f);
  sprite_move = SpriteAnim::addSpriteAnim(this, "assets/sprite/ghost-move.png", 2.0f);
  sprite_move->setActive(false);

  m_collider = Collider::addCollider(this, sprite_idle->getSize() / 2.0f);
  m_states = States::addStates(this);

  // 设置玩家的死亡特效
  m_effect = Effect::addEffect(Game::getInstance().getCurrentScene(), "assets/effect/1764.png", glm::vec2(0.0f), 2.0f);
  m_effect->setActive(false);

  // 创建武器
  m_weapon_thunder = WeaponThunder::addWeaponThunder(this, 2.0f, 40.0f);

  // --- 测试 ---
  // TextLable::addTextLable(this, "Player", "assets/font/VonwaonBitmap-16px.ttf", 16.0f);
}

/* 事件处理 */
bool Player::handleEvents(SDL_Event &event) {
  return Entity::handleEvents(event);
}

/* 更新 */
void Player::update(const float &delta_time) {
  Entity::update(delta_time);

  m_velocity *= 0.9f;  // 先衰减当前速度
  keyboardControl();   // 然后根据按键设置速度
  checkState();
  move(delta_time);  // 最后应用速度移动
  syncCamera();
  checkDeath();
}

/* 渲染 */
void Player::render() {
  if (m_states && m_states->getIsInvincible() && m_timer_flash->getProgress() < 0.5f) {
    return;
  }
  Entity::render();

  // Game::getInstance().drawBoundary(m_render_postion, m_render_postion + glm::vec2(20.0f), 5.0f, {1.0f, 0.0, 0.0, 1.0f});
}

/* 清理 */
void Player::clean() {
  Entity::clean();
}

/* 受到伤害 */
void Player::takeDamage(float damage) {
  // 如果玩家处于无敌状态，则不受到伤害
  if (!m_states || m_states->getIsInvincible()) {
    return;
  }
  Entity::takeDamage(damage);
  Game::getInstance().playSound("assets/sound/hit-flesh-02-266309.mp3");
}

/* 键盘控制逻辑 */
void Player::keyboardControl() {
  auto currentKeyStates = SDL_GetKeyboardState(NULL);

  // 移动控制逻辑
  if (currentKeyStates[SDL_SCANCODE_W]) {
    m_velocity.y = -m_max_speed;
  }
  if (currentKeyStates[SDL_SCANCODE_S]) {
    m_velocity.y = m_max_speed;
  }
  if (currentKeyStates[SDL_SCANCODE_A]) {
    m_velocity.x = -m_max_speed;
  }
  if (currentKeyStates[SDL_SCANCODE_D]) {
    m_velocity.x = m_max_speed;
  }
}

/* 相机跟随玩家 */
void Player::syncCamera() {
  Game::getInstance().getCurrentScene()->setCameraPosition(m_position - Game::getInstance().getScreenSize() / 2.0f);
}

/* 判断当前物体状态 */
void Player::checkState() {
  if (m_velocity.x < 0) {
    sprite_move->setFlip(true);
    sprite_idle->setFlip(true);
  } else {
    sprite_move->setFlip(false);
    sprite_idle->setFlip(false);
  }

  bool is_moving_again = glm::length(m_velocity) > 0.1f;
  if (is_moving_again != m_is_moving) {
    m_is_moving = is_moving_again;
    changeState(m_is_moving);
  }
}

/* 改变物体运动状态，让运动状态切换更丝滑 */
void Player::changeState(bool is_moving) {
  if (is_moving) {
    sprite_idle->setActive(false);
    sprite_move->setActive(true);
    sprite_move->setCurrentFrame(sprite_idle->getCurrentFrame());
    sprite_move->setFrameTimer(sprite_idle->getFrameTimer());
  } else {
    sprite_idle->setActive(true);
    sprite_move->setActive(false);
    sprite_idle->setCurrentFrame(sprite_move->getCurrentFrame());
    sprite_idle->setFrameTimer(sprite_move->getFrameTimer());
  }
}

/* 检查玩家是否死亡 */
void Player::checkDeath() {
  // TODO: 实现死亡检查逻辑
  // 例如：检查生命值、碰撞检测等
  if (!m_states->getIsAlive()) {
    // 玩家死亡，可以添加死亡动画或游戏结束逻辑
    m_effect->setActive(true);
    m_effect->setPosition(m_position);
    setActive(false);
    Game::getInstance().playSound("assets/sound/female-scream-02-89290.mp3");
  }
}
