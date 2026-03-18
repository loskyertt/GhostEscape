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
    if (child->getActiveState()) {
      child->handleEvents(event);
    }
  }
}

/* 更新 */
void Object::update(const float &delta_time) {
  for (auto &child : m_children) {
    if (child->getActiveState()) {
      child->update(delta_time);
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
  for (auto &child : m_children) {
    child->clean();
  }

  m_children.clear();  //触发所有子对象的析构
}

/* 添加 Object */
void Object::addObject(std::unique_ptr<Object> child) {
  m_children.push_back(std::move(child));
}

/* 移除 Object */
void Object::removeObject(Object *child) {
  m_children.erase(
      std::remove_if(
          m_children.begin(),
          m_children.end(),
          [child](const std::unique_ptr<Object> &p) {
            return p.get() == child;  // 比较原始指针地址
          }),
      m_children.end());
  // erase 时 unique_ptr 析构 → 自动 delete
}
