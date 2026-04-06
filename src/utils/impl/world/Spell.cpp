/*
 * @File    :   lib\world\Spell.cpp
 * @Time    :   2026/04/05 00:11:47
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "world/Spell.h"
#include "affiliate/Collider.h"
#include "affiliate/SpriteAnim.h"
#include "core/Defs.h"
#include "core/ObjectWorld.h"
#include "core/Scene.h"

void Spell::update(const float &delta_time) {
  ObjectWorld::update(delta_time);
  if (m_sprite_anim->getIsFinished()) {
    m_need_remove = true;
  }
  attack();
}

void Spell::attack() {
  // TODO: implement attack logic
  auto objects = m_game.getCurrentScene()->getChildrenWorld();
  for (auto &object : objects) {
    if (object->getType() != ObjectType::ENEMY) {
      continue;
    }
    if (m_collider && object->getCollider() && m_collider->isColliding(object->getCollider())) {
      object->takeDamage(m_damage);
    }
  }
}

Spell *Spell::addSpell(
    Object *parent,
    const std::string &file_path,
    const glm::vec2 &position,
    float damage,
    float scale,
    Anchor anchor) {
  auto spell = new Spell();
  spell->init();
  spell->setDamage(damage);
  spell->m_sprite_anim = SpriteAnim::addSpriteAnim(spell, file_path, scale, anchor);
  auto size = spell->m_sprite_anim->getSize();
  spell->m_collider = Collider::addCollider(spell, size, Collider::Type::CIRCLE, anchor);
  spell->m_sprite_anim->setIsLoop(false);
  spell->setPosition(position);
  if (parent) {
    parent->addChild(spell);
  }

  return spell;
}
