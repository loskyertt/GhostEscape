/*
 * @File    :   include\raw\States.h
 * @Time    :   2026/03/20 19:04:59
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "core/Object.h"

class Entity;

class States : public Object {
 protected:
  Entity *m_parent = nullptr;  // 父节点

  float m_health = 100.0f;      // 当前生命值
  float m_max_health = 100.0f;  // 最大生命值
  float m_mana = 100.0f;        // 当前法力值
  float m_max_mana = 100.0f;    // 最大法力值
  float m_mana_regen = 10.0f;   // 法力回复速度
  float m_damage = 40.0f;       // 攻击伤害

  bool m_is_alive = true;  // 是否存活

  float m_invincibility_duration = 1.5f;  // 受伤后的无敌持续时间，单位：秒
  float m_invincibility_timer = 0.0f;     // 无敌计时器
  bool m_is_invincible = false;           // 是否无敌

 public:
  void update(const float &delta_time) override;

  /* 判断是否能用法力 */
  bool canUseMana(float mana_cost);

  /* 使用法力 */
  void useMana(float mana_cost);

  /* 法力自动回复 */
  void regenMana(const float &delta_time);

  /* 受伤 */
  void takeDamage(float damage);

 public:
  static States *addStates(
      Entity *parent,
      float max_health = 100.0f,
      float max_mana = 100.0f,
      float mana_regen = 10.0f,
      float damage = 40.0f);

  // getters
 public:
  Entity *getParent() const { return m_parent; }

  float getHealth() const { return m_health; }

  float getMaxHealth() const { return m_max_health; }

  float getMana() const { return m_mana; }

  float getMaxMana() const { return m_max_mana; }

  float getManaRegen() const { return m_mana_regen; }

  float getDamage() const { return m_damage; }

  bool getIsAlive() const { return m_is_alive; }

  float getInvincibilityDuration() const { return m_invincibility_duration; }

  bool getIsInvincible() const { return m_is_invincible; }

  // setters
 public:
  void setParent(Entity *parent) { m_parent = parent; }

  void setHealth(float health) { m_health = health; }

  void setMaxHealth(float max_health) { m_max_health = max_health; }

  void setMana(float mana) { m_mana = mana; }

  void setMaxMana(float max_mana) { m_max_mana = max_mana; }

  void setManaRegen(float mana_regen) { m_mana_regen = mana_regen; }

  void setDamage(float damage) { m_damage = damage; }

  void setIsAlive(bool is_alive) { m_is_alive = is_alive; }

  void setInvincibilityDuration(float invincibility_duration) { m_invincibility_duration = invincibility_duration; }

  void setIsInvincible(bool is_invincible) { m_is_invincible = is_invincible; }
};
