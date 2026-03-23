/*
 * @File    :   lib\core\Object.cpp
 * @Time    :   2026/03/16 20:37:58
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/Object.h"
#include <SDL3/SDL_log.h>

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
    m_children.push_back(std::move(child));
  }
  m_children_back.clear();

  for (auto it = m_children.begin(); it != m_children.end();) {
    auto &child = *it;  // 使用引用来避免复制 unique_ptr
    if (child->getNeedRmove()) {
      child->clean();  // 清理子对象
      it = m_children.erase(it);
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
#ifndef NDEBUG
  SDL_Log("调用 Object::clean()");
#endif
  for (auto &child : m_children) {
    child->clean();
  }

  m_children.clear();  //触发所有子对象的析构
}

/* 添加 Object */
void Object::addChild(std::unique_ptr<Object> child) {
  m_children.push_back(std::move(child));
}

/* 移除 Object */
void Object::removeChild(Object *child) {
  m_children.erase(
      // 返回要删除元素的新终点
      std::remove_if(
          m_children.begin(),
          m_children.end(),
          [child](const std::unique_ptr<Object> &p) {
            return p.get() == child;  // 比较原始指针地址
          }),
      m_children.end());  // 删除从新终点到原终点的所有元素
  // erase 时 unique_ptr 析构 → 自动 delete
}

/* 安全添加子节点 */
void Object::safeAddChild(std::unique_ptr<Object> child) {
  m_children_back.push_back(std::move(child));
}
