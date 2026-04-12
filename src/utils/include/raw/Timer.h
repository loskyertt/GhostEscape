/*
 * @File    :   src\utils\include\raw\Timer.h
 * @Time    :   2026/04/12 13:21:15
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "core/Object.h"

class Timer : public Object {
 protected:
  float m_timer = 0;
  float m_interval = 0;

  bool m_time_out = false;

 public:
  void update(const float &delta_time) override;

  void start();
  bool timeOut();
  void stop();

  // getters
 public:
  float getInterval() const { return m_interval; }

  float getTimer() const { return m_timer; }

  float getProgress() const { return m_timer / m_interval; }

  // setters
 public:
  void setInterval(float interval) { m_interval = interval; }

  void setTimer(float timer) { m_timer = timer; }

 public:
  static Timer *addTimer(Object *parent, float interval = 3.0f);
};
