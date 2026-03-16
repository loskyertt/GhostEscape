/*
 * @File    :   lib\core\Scene.cpp
 * @Time    :   2026/03/16 13:58:29
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/Scene.h"

#include <glm/fwd.hpp>

Scene::Scene() = default;

Scene::~Scene() = default;

/* 初始化 */
void Scene::init() {}

/* 事件处理 */
void Scene::handleEvents(SDL_Event &event) {}

/* 更新 */
void Scene::update(const float &deltaTime) {}

/* 渲染 */
void Scene::render() {}

/* 清理 */
void Scene::clean() {}

/* 设置相机坐标 */
void Scene::setCameraPosition(const glm::vec2 &camera_position) {
  m_camera_position = camera_position;
  // 相机位置限制：[-30, world_size - screen_size + 30]
  m_camera_position =
      glm::clamp(m_camera_position, glm::vec2(-30.0f), m_world_size - m_game.getScreenSize() + glm::vec2(30.0f));
}
