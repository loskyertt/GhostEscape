/*
 * @File    :   include\Enemy.h
 * @Time    :   2026/03/18 23:55:47
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   Enemy class declaration
 */

#pragma once

#include "Player.h"

class Enemy : public Actor {
 private:
  Player *m_target_player = nullptr;

 public:
  /* 向玩家移动 */
  void aimTargetPlayer(Player *target_player);
};
