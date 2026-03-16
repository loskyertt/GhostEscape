/*
 * @File    :   include\core\Actor.h
 * @Time    :   2026/03/15 23:30:19
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "ObjectWorld.h"

#include "glm/fwd.hpp"

class Actor : public ObjectWorld {
 protected:
  glm::vec2 m_velocity = glm::vec2(0);  // 速度
  float m_max_speed = 100.0f;           // 默认最大速度

  // getters
 public:
  /* 获取速度 */
  glm::vec2 getVelocity() { return m_velocity; }

  /* 获取最大速度 */
  float getMaxSpeed() { return m_max_speed; }

  // setters
 public:
  /* 设置速度 */
  void setVelocity(const glm::vec2 &velocity) { m_velocity = velocity; }

  /* 设置最大速度 */
  void setMaxSpeed(float max_speed) { m_max_speed = max_speed; }
};
