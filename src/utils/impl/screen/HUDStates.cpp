/*
 * @File    :   src\utils\impl\screen\HUDStates.cpp
 * @Time    :   2026/04/06 20:44:20
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "screen/HUDStates.h"
#include "core/Defs.h"
#include "core/ObjectScreen.h"
#include "core/Entity.h"
#include "affiliate/Sprite.h"
#include "glm/ext/vector_float2.hpp"
#include "raw/States.h"

void HUDStates::init() {
  ObjectScreen::init();
  // 渲染顺序与挂载到场景树的顺序一致
  // 先绘制背景图片
  m_health_bar_bg = Sprite::addSprite(this, "assets/UI/bar_bg.png", 3.0f, Anchor::MIDDLE_LEFT);
  m_health_bar_bg->setOffset(m_health_bar_bg->getOffset() + glm::vec2(30.0f, 0));

  // 再绘制前景图片
  m_health_bar = Sprite::addSprite(this, "assets/UI/bar_red.png", 3.0f, Anchor::MIDDLE_LEFT);
  m_health_bar->setOffset(m_health_bar->getOffset() + glm::vec2(30.0f, 0));

  // 再绘制图标 icon
  m_health_bar_icon = Sprite::addSprite(this, "assets/UI/Red Potion.png", 0.5f, Anchor::MIDDLE_LEFT);

  m_mana_bar_bg = Sprite::addSprite(this, "assets/UI/bar_bg.png", 3.0f, Anchor::MIDDLE_LEFT);
  m_mana_bar_bg->setOffset(m_mana_bar_bg->getOffset() + glm::vec2(300.0f, 0));

  m_mana_bar = Sprite::addSprite(this, "assets/UI/bar_blue.png", 3.0f, Anchor::MIDDLE_LEFT);
  m_mana_bar->setOffset(m_mana_bar->getOffset() + glm::vec2(300.0f, 0));

  m_mana_bar_icon = Sprite::addSprite(this, "assets/UI/Blue Potion.png", 0.5f, Anchor::MIDDLE_LEFT);
  m_mana_bar_icon->setOffset(m_mana_bar_icon->getOffset() + glm::vec2(270.0f, 0));
}

void HUDStates::update(const float &delta_time) {
  ObjectScreen::update(delta_time);
  updateHealthBar();
  updateManaBar();
}

void HUDStates::updateHealthBar() {
  if (!m_target || !m_health_bar || !m_target->getStates()) {
    return;
  }

  m_health_bar->setPercentage(
      glm::vec2(m_target->getStates()->getHealth() / m_target->getStates()->getMaxHealth(), 1.0f));
}

void HUDStates::updateManaBar() {
  if (!m_target || !m_mana_bar || !m_target->getStates()) {
    return;
  }

  m_mana_bar->setPercentage(glm::vec2(m_target->getStates()->getMana() / m_target->getStates()->getMaxMana(), 1.0f));
}

HUDStates *HUDStates::addHUDStates(Object *parent, Entity *target, glm::vec2 render_position) {
  auto hud_states = new HUDStates();
  hud_states->init();
  hud_states->setRenderPosition(render_position);
  hud_states->setTarget(target);
  if (parent) {
    parent->addChild(hud_states);
  }
  return hud_states;
}
