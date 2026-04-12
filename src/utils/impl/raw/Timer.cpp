/*
 * @File    :   src\utils\impl\raw\Timer.cpp
 * @Time    :   2026/04/12 13:21:21
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "raw/Timer.h"

void Timer::update(const float &delta_time) {
  m_timer += delta_time;
  if (m_timer >= m_interval) {
    m_timer = 0;
    m_time_out = true;
  }
}

void Timer::start() {
  m_is_activive = true;
}

bool Timer::timeOut() {
  if (m_time_out) {
    m_time_out = false;
    return true;
  }
  return false;
}

void Timer::stop() {
  m_is_activive = false;
}

Timer *Timer::addTimer(Object *parent, float interval) {
  Timer *timer = new Timer();
  timer->setInterval(interval);
  timer->setActive(false);
  if (parent) {
    parent->addChild(timer);
  }
  return timer;
}
