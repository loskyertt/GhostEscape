/*
 * @File    :   src\core\impl\Object.cpp
 * @Time    :   2026/03/16 20:37:58
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/Object.h"

#include <SDL3/SDL_log.h>

#include <algorithm>

Object::~Object() = default;

void Object::init() {}

bool Object::handleEvents(SDL_Event &event) {
  for (auto &child : m_children) {
    if (child->getActiveState()) {
      if (child->handleEvents(event)) {
        return true;  // 容器中后面的事件不会再处理
      }
    }
  }
  return false;
}

void Object::update(const float &delta_time) {
  for (auto &child : m_children_back) {
    addChild(child);
  }
  m_children_back.clear();

  for (auto it = m_children.begin(); it != m_children.end();) {
    auto child = *it;
    if (child->getNeedRemove()) {
      it = m_children.erase(it);  // 从容器中清除
      child->clean();             // 清理子对象
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

void Object::render() {
  for (auto &child : m_children) {
    if (child->getActiveState()) {
      child->render();
    }
  }
}

void Object::clean() {
  // #ifndef NDEBUG
  //   SDL_Log("调用 Object::clean()");
  // #endif
  for (auto &child : m_children) {
    child->clean();
    delete child;
    child = nullptr;
  }

  m_children.clear();  //触发所有子对象的析构
}

void Object::addChild(Object *child) {
  m_children.push_back(child);
}

void Object::removeChild(Object *child) {
  m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());
}

void Object::safeAddChild(Object *child) {
  m_children_back.push_back(child);
#ifndef NDEBUG
  SDL_Log("=> 调用 safeAddChild() -> m_children_back.push_back(child)");
#endif
}
