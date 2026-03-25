/*
 * @File    :   lib\core\Object.cpp
 * @Time    :   2026/03/16 20:37:58
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/Object.h"

#include <SDL3/SDL_log.h>

#include <algorithm>

Object::Object() = default;

Object::~Object() = default;

/* 初始化 */
void Object::init() {}

/* 事件处理 */
void Object::handleEvents(SDL_Event &event) {
  for (auto &child : m_children) {
    if (child->getActiveState()) {
      child->handleEvents(event);
    }
  }
}

/* 更新 */
void Object::update(const float &delta_time) {
  for (auto &child : m_children_back) {
    addChild(child);
  }
  m_children_back.clear();

  for (auto it = m_children.begin(); it != m_children.end();) {
    auto &child = *it;  // 使用引用来避免复制 unique_ptr
    if (child->getNeedRmove()) {
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

/* 渲染 */
void Object::render() {
  for (auto &child : m_children) {
    if (child->getActiveState()) {
      child->render();
    }
  }
}

/* 清理 */
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

/* 添加 Object */
void Object::addChild(Object *child) {
  m_children.push_back(child);
}

/* 移除 Object */
void Object::removeChild(Object *child) {
  m_children.erase(std::remove(m_children.begin(), m_children.end(), child), m_children.end());
}

/* 安全添加子节点 */
void Object::safeAddChild(Object *child) {
  m_children_back.push_back(child);
}
