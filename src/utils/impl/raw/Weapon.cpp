/*
 * @File    :   lib\raw\Weapon.cpp
 * @Time    :   2026/04/06 12:15:51
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "raw/Weapon.h"
#include "affiliate/Collider.h"
#include "core/Object.h"
#include "core/Entity.h"
#include "raw/States.h"
#include "world/Spell.h"
#include "core/Scene.h"

void Weapon::update(const float &delta_time) {
  Object::update(delta_time);
  m_cool_down_timer += delta_time;
}

void Weapon::attack(const glm::vec2 &position, Spell *spell) {
  if (!spell) {
    return;
  }

  m_parent->getStates()->useMana(m_mana_cost);
  m_cool_down_timer = 0.0f;
  spell->setPosition(position);
  m_game.getCurrentScene()->safeAddChild(spell);
}

bool Weapon::canAttack() {
  if (m_cool_down_timer < m_cool_down || !m_parent->getStates()->canUseMana(m_mana_cost)) {
    return false;
  }

  return true;
}
