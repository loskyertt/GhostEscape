/*
 * @File    :   lib\WeaponThunder.cpp
 * @Time    :   2026/04/06 12:48:44
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/game/WeaponThunder.h"
#include "core/Defs.h"
#include "world/Spell.h"
#include "core/Scene.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>

void WeaponThunder::handleEvents(SDL_Event &event) {
  if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
    if (event.button.button == SDL_BUTTON_LEFT) {
      if (canAttack()) {
        auto pos = m_game.getMousePosition() + m_game.getCurrentScene()->getCameraPosition();
        auto spell =
            Spell::addSpell(nullptr, "assets/effect/Thunderstrike w blur.png", pos, 40.0f, 3.0f, Anchor::MIDDLE_CENTER);
        attack(pos, spell);
      }
    }
  }
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
