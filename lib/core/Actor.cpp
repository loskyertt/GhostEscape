/*
 * @File    :   lib\core\Actor.cpp
 * @Time    :   2026/03/19 21:12:08
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "SceneMain.h"
#include "core/Actor.h"

/* 玩家位置移动 */
void Actor::move(const float &delta_time) {
  setPosition(m_position += m_velocity * delta_time);
  // SDL_Log(
  //     "delta_time: %f, position: (%f, %f), velocity: (%f, %f)",
  //     delta_time,
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
