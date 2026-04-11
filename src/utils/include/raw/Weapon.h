/*
 * @File    :   include\raw\Weapon.h
 * @Time    :   2026/04/06 12:15:26
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/Object.h"
#include "glm/ext/vector_float2.hpp"

class Entity;
class Spell;

class Weapon : public Object {
 protected:
  Entity *m_parent = nullptr;

  float m_cool_down = 1.0f;
  float m_mana_cost = 0.0f;
  float m_cool_down_timer = 0.0f;

 public:
  void update(const float &delta_time) override;

 public:
  void attack(const glm::vec2 &position, Spell *spell);  // 确保调用这个函数时，一定执行 attack 函数

  bool canAttack();

  // getters
 public:
  Entity *getParent() const { return m_parent; }

  float getCoolDown() const { return m_cool_down; }

  float getManaCost() const { return m_mana_cost; }

  float getCoolDownTimer() const { return m_cool_down_timer; }

  // setters
 public:
  void setParent(Entity *parent) { m_parent = parent; }

  void setCoolDown(float cool_down) { m_cool_down = cool_down; }

  void setManaCost(float mana_cost) { m_mana_cost = mana_cost; }

  void setCoolDownTimer(float cool_down_timer) { m_cool_down_timer = cool_down_timer; }
};
