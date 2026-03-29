/*
 * @File    :   lib\core\Scene.cpp
 * @Time    :   2026/03/16 13:58:29
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/Scene.h"
#include "core/Object.h"
#include "core/Defs.h"
#include "core/ObjectScreen.h"
#include "core/ObjectWorld.h"

#include <glm/fwd.hpp>

#include <SDL3/SDL_log.h>

#include <algorithm>

Scene::Scene() = default;

Scene::~Scene() = default;

/* 事件处理 */
void Scene::handleEvents(SDL_Event &event) {
  Object::handleEvents(event);

  for (auto &child : m_children_screen) {
    if (child->getActiveState()) {
      child->handleEvents(event);
    }
  }
  for (auto &child : m_children_world) {
    if (child->getActiveState()) {
      child->handleEvents(event);
    }
  }
}

/* 更新 */
void Scene::update(const float &delta_time) {
  Object::update(delta_time);

  for (auto it = m_children_world.begin(); it != m_children_world.end();) {
    // 这里不能写成 &child
    // 由于 child 是一个引用，在 erase(it) 之后，child 变成了一个悬垂引用，它指向的内存已经被释放。
    auto child = *it;
    if (child->getNeedRemove()) {
      it = m_children_world.erase(it);
      child->clean();
      delete child;
      child = nullptr;
#ifndef NDEBUG
      SDL_Log("=> 调用 Scene::update() -> child 从 m_children_world 中移除");
#endif
    } else {
      if (child->getActiveState()) {
        child->update(delta_time);
      }
      ++it;
    }
  }

  for (auto it = m_children_screen.begin(); it != m_children_screen.end();) {
    auto child = *it;
    if (child->getNeedRemove()) {
      it = m_children_screen.erase(it);
      child->clean();
      delete child;
      child = nullptr;
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

  for (auto &child : m_children_world) {
    if (child->getActiveState()) {
      child->render();
    }
  }

  for (auto &child : m_children_screen) {
    if (child->getActiveState()) {
      child->render();
    }
  }
}

/* 清理 */
void Scene::clean() {
  Object::clean();

  for (auto &child : m_children_screen) {
    child->clean();
    delete child;
    child = nullptr;
  }
  m_children_screen.clear();

  for (auto &child : m_children_world) {
    child->clean();
    delete child;
    child = nullptr;
  }
  m_children_world.clear();
}

/* 添加 ObjectScreen */
void Scene::addChild(Object *child) {
  switch (child->getType()) {
    case ObjectType::NONE: {
      Object::addChild(child);
      SDL_Log("=> 调用 Scene::addChild() -> m_children.push_back(child)");
      break;
    }
    case ObjectType::OBJECT_SCREEN: {
      // 对于向下转型（父类 -> 子类），需要显示转换
      m_children_screen.push_back(static_cast<ObjectScreen *>(child));
      SDL_Log("=> 调用 Scene::addChild() -> m_children_screen.push_back(child)");
      break;
    }
    case ObjectType::OBJECT_WORLD: {
      m_children_world.push_back(static_cast<ObjectWorld *>(child));
      SDL_Log("=> 调用 Scene::addChild() -> m_children_world.push_back(child)");
      break;
    }
  }
}

/* 移除 ObjectScreen */
void Scene::removeChild(Object *child) {
  switch (child->getType()) {
    case ObjectType::NONE: {
      Object::removeChild(child);
      SDL_Log("=> 调用 Scene::removeChild() -> child 从 m_children 中移除");
      break;
    }
    case ObjectType::OBJECT_SCREEN: {
      m_children_screen.erase(
          std::remove(m_children_screen.begin(), m_children_screen.end(), static_cast<ObjectScreen *>(child)),
          m_children_screen.end());
      SDL_Log("=> 调用 Scene::removeChild() -> child 从 m_children_screen 中移除");
      break;
    }
    case ObjectType::OBJECT_WORLD: {
      m_children_world.erase(
          std::remove(m_children_world.begin(), m_children_world.end(), static_cast<ObjectWorld *>(child)),
          m_children_world.end());
      SDL_Log("=> 调用 Scene::removeChild() -> child 从 m_children_world 中移除");
      break;
    }
  }
}

/* 设置相机坐标 */
void Scene::setCameraPosition(const glm::vec2 &camera_position) {
  m_camera_position = camera_position;
  // 相机位置限制：[-30, world_size - screen_size + 30]
  m_camera_position =
      glm::clamp(m_camera_position, glm::vec2(-30.0f), m_world_size - m_game.getScreenSize() + glm::vec2(30.0f));
}
