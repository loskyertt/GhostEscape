/*
 * @File    :   src\utils\impl\raw\BackGroundStar.cpp
 * @Time    :   2026/04/12 14:22:10
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/Game.h"
#include "core/Object.h"
#include "core/Scene.h"

#include "raw/BackgroundStar.h"

#include <cmath>

void BackgroundStar::update(const float &delta_time) {
  Object::update(delta_time);

  m_timer += delta_time;
  m_color_far = {0.5f + 0.5f * sinf(m_timer * 0.9f),
      0.5f + 0.5f * sinf(m_timer * 0.8f),
      0.5f + 0.5f * sinf(m_timer * 0.7f),
      1.0f};
  m_color_middle = {0.5f + 0.5f * sinf(m_timer * 0.8f),
      0.5f + 0.5f * sinf(m_timer * 0.7f),
      0.5f + 0.5f * sinf(m_timer * 0.6f),
      1.0f};
  m_color_near = {0.5f + 0.5f * sinf(m_timer * 0.7f),
      0.5f + 0.5f * sinf(m_timer * 0.6f),
      0.5f + 0.5f * sinf(m_timer * 0.5f),
      1.0f};
}

void BackgroundStar::render() {
  Object::render();
  auto pos = -Game::getInstance().getCurrentScene()->getCameraPosition();
  Game::getInstance().drawPoints(m_star_far, pos * m_scale_far, m_color_far);
  Game::getInstance().drawPoints(m_star_middle, pos * m_scale_middle, m_color_middle);
  Game::getInstance().drawPoints(m_star_near, pos * m_scale_near, m_color_near);
}

BackgroundStar *BackgroundStar::addBackgroundStar(Object *parent,
    int num,
    float scale_far,
    float scale_middle,
    float scale_near) {
  auto bg_star = new BackgroundStar();
  bg_star->init();
  bg_star->m_num = num;
  bg_star->m_scale_far = scale_far;
  bg_star->m_scale_middle = scale_middle;
  bg_star->m_scale_near = scale_near;

  // 预先把内存分配好，避免重写分配
  bg_star->m_star_far.reserve(static_cast<size_t>(num));
  bg_star->m_star_middle.reserve(static_cast<size_t>(num));
  bg_star->m_star_near.reserve(static_cast<size_t>(num));
  auto extra = Game::getInstance().getCurrentScene()->getWorldSize() - Game::getInstance().getScreenSize();
  for (int i = 0; i < num; i++) {
    bg_star->m_star_far.push_back(
        Game::getInstance().randomVec2(glm::vec2(0.0f), Game::getInstance().getScreenSize() + extra * scale_far));
    bg_star->m_star_middle.push_back(
        Game::getInstance().randomVec2(glm::vec2(0.0f), Game::getInstance().getScreenSize() + extra * scale_middle));
    bg_star->m_star_near.push_back(
        Game::getInstance().randomVec2(glm::vec2(0.0f), Game::getInstance().getScreenSize() + extra * scale_near));
  }

  if (parent) {
    parent->addChild(bg_star);
  }
  return bg_star;
}
