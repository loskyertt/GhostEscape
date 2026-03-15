/*
 * @File    :   lib\SceneMain.cpp
 * @Time    :   2026/03/15 19:21:35
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "SceneMain.h"
#include "glm/fwd.hpp"

SceneMain::~SceneMain() {}

/* 初始化 */
void SceneMain::init() {
  m_world_size = m_game.getScreenSize() * 3.0f;
  // m_camera_position = glm::vec2(-100.0f);
}

/* 事件处理 */
void SceneMain::handleEvents(SDL_Event &event) {}

/* 更新 */
void SceneMain::update(const float &deltaTime) {
  // m_camera_position += glm::vec2(20.0f, 20.0f) * deltaTime;
}

/* 渲染 */
void SceneMain::render() {
  renderBackground();
}

/* 清理 */
void SceneMain::clean() {}

/* 绘制背景图片 */
void SceneMain::renderBackground() {
  auto start = -m_camera_position;
  auto end = m_world_size - m_camera_position;
  m_game.drawGrid(start, end, 80.0f, {0.5f, 0.5f, 0.5f, 0.1f});
  m_game.drawBoundary(start, end, 5.0f, {1.0f, 1.0f, 1.0f, 1.0f});
}
