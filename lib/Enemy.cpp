/*
 * @File    :   lib\Enemy.cpp
 * @Time    :   2026/03/19 00:08:27
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "Enemy.h"

#include "glm/geometric.hpp"

/* 向玩家移动 */
void Enemy::aimTargetPlayer(Player *target_player) {
  auto direction = target_player->getPosition() - this->getPosition();
  direction = glm::normalize(direction);
  m_velocity = direction * m_max_speed;
}
