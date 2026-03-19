/*
 * @File    :   lib\core\Scene.cpp
 * @Time    :   2026/03/16 13:58:29
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/Scene.h"
#include <SDL3/SDL_log.h>

#include <glm/fwd.hpp>

Scene::Scene() = default;

Scene::~Scene() = default;

/* 初始化 */
void Scene::init() {}

/* 事件处理 */
void Scene::handleEvents(SDL_Event &event) {
  Object::handleEvents(event);
  for (auto &iter : m_children_screen) {
    if (m_is_activive) {
      iter->handleEvents(event);
    }
  }
  for (auto &iter : m_children_world) {
    if (m_is_activive) {
      iter->handleEvents(event);
    }
  }
}

/* 更新 */
void Scene::update(const float &delta_time) {
  Object::update(delta_time);

  for (auto it = m_children_world.begin(); it != m_children_world.end();) {
    auto &child = *it;  // 使用引用来避免复制 unique_ptr
    if (child->getNeedRmove()) {
      child->clean();  // 一定要在 erase 之前调用 clean()，
      it = m_children_world.erase(it);
      SDL_Log("world child removed");
    } else {
      if (child->getActiveState()) {
        child->update(delta_time);
      }
      ++it;
    }
  }

  for (auto it = m_children_screen.begin(); it != m_children_screen.end();) {
    auto &child = *it;  // 使用引用来避免复制 unique_ptr
    if (child->getNeedRmove()) {
      child->clean();  // 一定要在 erase 之前调用 clean()，
      it = m_children_screen.erase(it);
    } else {
      if (child->getActiveState()) {
        child->update(delta_time);
      }
      ++it;
    }
  }
}

/* 渲染 */
void Scene::render() {
  Object::render();
  for (auto &iter : m_children_world) {
    if (m_is_activive) {
      iter->render();
    }
  }
  for (auto &iter : m_children_screen) {
    if (m_is_activive) {
      iter->render();
    }
  }
}

/* 清理 */
void Scene::clean() {
  Object::clean();
  for (auto &iter : m_children_screen) {
    iter->clean();
  }
  m_children_screen.clear();
  for (auto &iter : m_children_world) {
    iter->clean();
  }
  m_children_world.clear();
}

/* 添加 ObjectScreen */
void Scene::addObjectScreen(std::unique_ptr<ObjectScreen> child) {
  m_children_screen.push_back(std::move(child));
}

/* 添加 ObjectWorld */
void Scene::addObjectWorld(std::unique_ptr<ObjectWorld> child) {
  m_children_world.push_back(std::move(child));
}

/* 移除 ObjectScreen */
void Scene::removeObjectScreen(ObjectScreen *child) {
  m_children_screen.erase(
      std::remove_if(
          m_children_screen.begin(),
          m_children_screen.end(),
          [child](const std::unique_ptr<ObjectScreen> &p) {
            return p.get() == child;  // 比较原始指针地址
          }),
      m_children_screen.end());
  // erase 时 unique_ptr 析构 → 自动 delete
}

/* 移除 ObjectWorld */
void Scene::removeObjectWorld(ObjectWorld *child) {
  m_children_world.erase(
      std::remove_if(
          m_children_world.begin(),
          m_children_world.end(),
          [child](const std::unique_ptr<ObjectWorld> &p) {
            return p.get() == child;  // 比较原始指针地址
          }),
      m_children_world.end());
  // erase 时 unique_ptr 析构 → 自动 delete
}

/* 设置相机坐标 */
void Scene::setCameraPosition(const glm::vec2 &camera_position) {
  m_camera_position = camera_position;
  // 相机位置限制：[-30, world_size - screen_size + 30]
  m_camera_position =
      glm::clamp(m_camera_position, glm::vec2(-30.0f), m_world_size - m_game.getScreenSize() + glm::vec2(30.0f));
}
