/*
 * @File    :   src\core\impl\game\SceneTitle.cpp
 * @Time    :   2026/04/11 19:50:48
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/game/SceneTitle.h"

#include "screen/HUDText.h"

#include <glm/fwd.hpp>

#include <string>
#include <cmath>

/* 初始化 */
void SceneTitle::init() {
  Scene::init();

  // 标题文本
  auto size = glm::vec2(m_game.getScreenSize().x / 2.0f, m_game.getScreenSize().y / 3.0f);
  HUDText::addHUDText(
      this,
      "幽灵逃生",
      m_game.getScreenSize() / 2.0f - glm::vec2(0.0f, 100.0f),
      size,
      "assets/font/VonwaonBitmap-16px.ttf",
      64.0f);

  // 得分文本
  auto score_text = "最高分：" + std::to_string(m_game.getHighScore());
  HUDText::addHUDText(
      this,
      score_text,
      m_game.getScreenSize() / 2.0f + glm::vec2(0.0f, 100.0f),
      glm::vec2(200.0f, 50.0f),
      "assets/font/VonwaonBitmap-16px.ttf",
      32.0f);
}

/* 事件处理 */
void SceneTitle::handleEvents(SDL_Event &event) {
  Scene::handleEvents(event);
}

/* 更新 */
void SceneTitle::update(const float &delta_time) {
  Scene::update(delta_time);

  m_color_timer += delta_time;
  updateColor();
}

/* 渲染 */
void SceneTitle::render() {
  renderBackground();
  Scene::render();
}

/* 清理 */
void SceneTitle::clean() {
  Scene::clean();
}

/* 渲染背景 */
void SceneTitle::renderBackground() {
  m_game.drawBoundary(glm::vec2(30.0f), m_game.getScreenSize() - glm::vec2(30.0f), 10.0f, m_boundary_color);
}

/* 更新颜色 */
void SceneTitle::updateColor() {
  // TODO: 实现颜色更新逻辑
  m_boundary_color.r = 0.5f + 0.5f * sinf(m_color_timer * 0.9f);
  m_boundary_color.g = 0.5f + 0.5f * sinf(m_color_timer * 0.8f);
  m_boundary_color.b = 0.5f + 0.5f * sinf(m_color_timer * 0.7f);
}
