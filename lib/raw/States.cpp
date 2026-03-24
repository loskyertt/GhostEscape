/*
 * @File    :   lib\raw\States.cpp
 * @Time    :   2026/03/20 19:05:10
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "raw/States.h"
#include "core/Entity.h"

#include <utility>

void States::update(const float &delta_time) {
  Object::update(delta_time);
  regenMana(delta_time);

  if (m_is_invincible) {
    m_invincibility_timer += delta_time;
    if (m_invincibility_timer >= m_invincibility_duration) {
      m_is_invincible = false;
      m_invincibility_timer = 0.0f;
    }
  }
}

/* 判断是否能用法力 */
bool States::canUseMana(float mana_cost) {
  return m_mana >= mana_cost;
}

/* 使用法力 */
void States::useMana(float mana_cost) {
  m_mana -= mana_cost;
  if (m_mana < 0) {
    m_mana = 0;
  }
}

/* 法力自动回复 */
void States::regenMana(const float &delta_time) {
  m_mana += m_mana_regen * delta_time;
  if (m_mana > m_max_mana) {
    m_mana = m_max_mana;
  }
}

/* 受伤 */
void States::takeDamage(float damage) {
  if (m_is_invincible) {
    return;
  }
#ifndef NDEBUG
  SDL_Log(
      "调用 Entity::takeDamage(): damage = %f, m_health = %f, isAlive = %d",
      static_cast<double>(damage),
      static_cast<double>(m_health),
      m_is_alive);
#endif

  m_health -= damage;
  if (m_health <= 0) {
    m_health = 0;
    m_is_alive = false;
  }

  m_is_invincible = true;
  m_invincibility_timer = 0.0f;
}

States *States::addStates(Entity *parent, float max_health, float max_mana, float mana_regen, float damage) {
  auto states = new States();
  states->m_parent = parent;
  states->m_health = max_health;
  states->m_max_health = max_health;
  states->m_mana = max_mana;
  states->m_max_mana = max_mana;
  states->m_mana_regen = mana_regen;
  states->m_damage = damage;

  if (parent) {
    parent->addChild(std::move(states));
  }

  return states;
}
