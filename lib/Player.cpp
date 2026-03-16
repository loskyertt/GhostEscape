/*
 * @File    :   lib\Player.cpp
 * @Time    :   2026/03/15 23:57:09
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "Player.h"
#include "core/Actor.h"
#include "core/Scene.h"

#include "glm/common.hpp"
#include "glm/fwd.hpp"

#include <SDL3/SDL.h>
#include <SDL3/SDL_keyboard.h>

Player::Player() = default;

Player::~Player() = default;

/* 初始化 */
void Player::init() {
  Actor::init();
  m_max_speed = 1000.0f;  // 设置玩家速度
}

/* 事件处理 */
void Player::handleEvents(SDL_Event &event) {
  Actor::handleEvents(event);
}

/* 更新 */
void Player::update(const float &deltaTime) {
  Actor::update(deltaTime);

  m_velocity *= 0.9f;  // 先衰减当前速度
  keyboardControl();   // 然后根据按键设置速度
  move(deltaTime);     // 最后应用速度移动
  syncCamera();
}

/* 渲染 */
void Player::render() {
  Actor::render();

  m_game.drawBoundary(m_render_postion, m_render_postion + glm::vec2(20.0f), 5.0f, {1.0f, 0.0, 0.0, 1.0f});
}

/* 清理 */
void Player::clean() {
  Actor::clean();
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

/* 玩家位置移动 */
void Player::move(const float &deltaTime) {
  setPosition(m_position += m_velocity * deltaTime);
  // SDL_Log(
  //     "deltaTime: %f, position: (%f, %f), velocity: (%f, %f)",
  //     deltaTime,
  //     m_position.x,
  //     m_position.y,
  //     m_velocity.x,
  //     m_velocity.y);

  /*
   * 返回值：value < min -> 返回 min；value > max -> 返回 max；min ≤ value ≤ max -> 返回 value 本身
   * - m_position.x = clamp(m_position.x, 0, worldSize.x);
   * - m_position.y = clamp(m_position.y, 0, worldSize.y);
   * - => 物体的在世界中的坐标范围：x ∈ [0, worldSize.x],  y ∈ [0, worldSize.y]
   */
  // 玩家位置限制
  m_position = glm::clamp(m_position, glm::vec2(0), m_game.getCurrentScene()->getWorldSize());
}

/* 相机跟随玩家 */
void Player::syncCamera() {
  m_game.getCurrentScene()->setCameraPosition(m_position - m_game.getScreenSize() / 2.0f);
}
