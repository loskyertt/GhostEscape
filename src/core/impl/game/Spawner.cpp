/*
 * @File    :   lib\Spawner.cpp
 * @Time    :   2026/03/29 20:03:48
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/game/Spawner.h"
#include "core/game/Enemy.h"
#include "core/game/SceneMain.h"
#include "world/Effect.h"
#include "core/game/Player.h"

void Spawner::update(const float &delta_time) {
  if (!m_target_player || !m_target_player->getActiveState()) {
    return;
  }

  m_timer += delta_time;
  if (m_timer >= m_interval) {
    m_timer = 0.0f;
    // TODO: spawn objects
    for (int i = 0; i < m_num; i++) {
      auto position = m_game.randomVec2(
          m_game.getCurrentScene()->getCameraPosition(),
          m_game.getCurrentScene()->getCameraPosition() + m_game.getScreenSize());
      Enemy *enemy = Enemy::addEnemy(nullptr, position, m_target_player);
      Effect::addEffect(m_game.getCurrentScene(), "assets/effect/184_3.png", position, 1.0f, enemy);
    }
  }
}
