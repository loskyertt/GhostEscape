/*
 * @File    :   include\WeaponThunder.h
 * @Time    :   2026/04/06 12:48:47
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/Entity.h"
#include "raw/Weapon.h"

class WeaponThunder : public Weapon {
 public:
  void handleEvents(SDL_Event &event) override;

 public:
  static WeaponThunder *addWeaponThunder(Entity *parent, float cool_down, float mana_cost);
};
