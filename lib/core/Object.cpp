/*
 * @File    :   lib\core\Object.cpp
 * @Time    :   2026/03/16 20:37:58
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/Object.h"

Object::Object() = default;

Object::~Object() = default;

/* 初始化 */
void Object::init() {}

/* 事件处理 */
void Object::handleEvents(SDL_Event &event) {
  for (auto &child : m_children) {
    child->handleEvents(event);
  }
}

/* 更新 */
void Object::update(const float &deltaTime) {
  for (auto &child : m_children) {
    child->update(deltaTime);
  }
}

/* 渲染 */
void Object::render() {
  for (auto &child : m_children) {
    child->render();
  }
}

/* 清理 */
void Object::clean() {
  for (auto &child : m_children) {
    child->clean();
  }

  m_children.clear();
}
