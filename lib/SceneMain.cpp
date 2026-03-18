/*
 * @File    :   lib\SceneMain.cpp
 * @Time    :   2026/03/15 19:21:35
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "SceneMain.h"
#include "Player.h"

#include <glm/fwd.hpp>

#include <memory>
#include <utility>

SceneMain::SceneMain() = default;
SceneMain::~SceneMain() = default;

/* 初始化 */
void SceneMain::init() {
  m_world_size = m_game.getScreenSize() * 3.0f;
  m_camera_position = m_world_size / 2.0f - m_game.getScreenSize() / 2.0f;

  // 玩家初始化
  auto player = std::make_unique<Player>();
  player->init();
  player->setPosition(m_world_size / 2.0f);
  m_player = player.get();            // 先保存原始指针负责日常访问，Scene 存 unique_ptr 负责生命周期
  addObjectWorld(std::move(player));  // Player -> Actor -> ObjectWorld
}

/* 事件处理 */
void SceneMain::handleEvents(SDL_Event &event) {
  Scene::handleEvents(event);
}

/* 更新 */
void SceneMain::update(const float &delta_time) {
  Scene::update(delta_time);
  // m_camera_position += glm::vec2(20.0f, 20.0f) * delta_time;
}

/* 渲染 */
void SceneMain::render() {
  renderBackground();
  Scene::render();
}

/* 清理 */
void SceneMain::clean() {
  Scene::clean();
}

/* 绘制背景 */
void SceneMain::renderBackground() {
  auto start = -m_camera_position;
  auto end = m_world_size - m_camera_position;
  m_game.drawGrid(start, end, 80.0f, {0.5f, 0.5f, 0.5f, 0.1f});
  m_game.drawBoundary(start, end, 5.0f, {1.0f, 1.0f, 1.0f, 1.0f});
}
