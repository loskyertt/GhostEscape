/*
 * @File    :   src\core\include\core\Entity.h
 * @Time    :   2026/03/15 23:30:19
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "ObjectWorld.h"

#include <glm/fwd.hpp>

class States;
class AffiliateBar;

class Entity : public ObjectWorld {
 protected:
  States *m_states = nullptr;            // 状态
  AffiliateBar *m_health_bar = nullptr;  // 血量条

  glm::vec2 m_velocity = glm::vec2(0);  // 速度
  float m_max_speed = 100.0f;           // 默认最大速度

 public:
  void update(const float &delta_time) override;

  /* 玩家位置移动 */
  void move(const float &delta_time);

  /* 受到伤害 */
  void takeDamage(float damage) override;

  /* 物体是否存活 */
  bool isAlive() const;

  /* 更新血量条 */
  void updateHealthBar();

  // getters
 public:
  /* 获取状态 */
  States *getStates() const { return m_states; }

  /* 获取速度 */
  glm::vec2 getVelocity() const { return m_velocity; }

  /* 获取最大速度 */
  float getMaxSpeed() const { return m_max_speed; }

  /* 获取血量条 */
  AffiliateBar *getHealthBar() const { return m_health_bar; }

  // setters
 public:
  /* 设置状态 */
  void setStates(States *states) { m_states = states; }

  /* 设置速度 */
  void setVelocity(const glm::vec2 &velocity) { m_velocity = velocity; }

  /* 设置最大速度 */
  void setMaxSpeed(float max_speed) { m_max_speed = max_speed; }

  /* 设置血量条 */
  void setHealthBar(AffiliateBar *health_bar) { m_health_bar = health_bar; }
};
