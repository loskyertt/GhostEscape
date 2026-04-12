/*
 * @File    :   lib\WeaponThunder.cpp
 * @Time    :   2026/04/06 12:48:44
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/game/WeaponThunder.h"
#include "core/Defs.h"
#include "core/Scene.h"

#include "world/Spell.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>

void WeaponThunder::init() {
  Weapon::init();
  auto scene = m_game.getCurrentScene();
  auto pos = glm::vec2(m_game.getScreenSize().x - 300, 30);
  m_hud_skill = HUDSkill::addHUDSkill(scene, "assets/UI/Electric-Icon.png", pos, 0.14f, Anchor::MIDDLE_CENTER);
}

void WeaponThunder::update(const float &delta_time) {
  Weapon::update(delta_time);
  if (m_hud_skill) {
    m_hud_skill->setPercentage(m_cool_down_timer / m_cool_down);
  }
}

bool WeaponThunder::handleEvents(SDL_Event &event) {
  if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
    if (event.button.button == SDL_BUTTON_LEFT) {
      if (canAttack()) {
        m_game.playSound("assets/sound/big-thunder.mp3");
        auto pos = m_game.getMousePosition() + m_game.getCurrentScene()->getCameraPosition();
        auto spell =
            Spell::addSpell(nullptr, "assets/effect/Thunderstrike w blur.png", pos, 40.0f, 3.0f, Anchor::MIDDLE_CENTER);
        attack(pos, spell);
        return true;
      }
    }
  }
  return false;
}

WeaponThunder *WeaponThunder::addWeaponThunder(Entity *parent, float cool_down, float mana_cost) {
  auto weapon = new WeaponThunder();
  weapon->init();
  weapon->setParent(parent);
  weapon->setCoolDown(cool_down);
  weapon->setManaCost(mana_cost);
  if (parent) {
    parent->addChild(weapon);
  }
  return weapon;
}
