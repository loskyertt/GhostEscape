/*
 * @File    :   include\Spawner.h
 * @Time    :   2026/03/29 20:03:33
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/Object.h"

class Player;

class Spawner : public Object {
 protected:
  int m_num = 20;
  float m_timer = 0.0f;
  float m_interval = 3.0f;

  Player *m_target_player = nullptr;

 public:
  void update(const float &delta_time) override;

  // getters
 public:
  int num() const { return m_num; }

  float timer() const { return m_timer; }

  float interval() const { return m_interval; }

  // setters
 public:
  void setNum(int num) { m_num = num; }

  void setTimer(float timer) { m_timer = timer; }

  void setInterval(float interval) { m_interval = interval; }

  void setTargetPlayer(Player *player) { m_target_player = player; }
};

