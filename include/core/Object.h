/*
 * @File    :   include\core\Object.h
 * @Time    :   2026/03/15 18:52:06
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "Game.h"

#include <memory>
#include <vector>

/*
 * - 约定：
 * - 所有的类，不在构造函数和析构函数做任何事
 * - 初始化：init 中进行
 * - 清理：clean 中进行
 */
class Object {
 protected:
  Game &m_game = Game::getInstance();
  std::vector<std::unique_ptr<Object>> m_children;  // 无实体，纯功能

  bool m_is_activive = true;

 public:
  Object();

  virtual ~Object();

  /* 初始化 */
  virtual void init();

  /* 事件处理 */
  virtual void handleEvents(SDL_Event &event);

  /* 更新 */
  virtual void update(const float &delta_time);

  /* 渲染 */
  virtual void render();

  /* 清理 */
  virtual void clean();

 public:
  /* 添加 Object */
  void addObject(std::unique_ptr<Object> child);

  /* 移除 Object */
  void removeObject(Object *child);

  // getters
 public:
  bool getActiveState() { return m_is_activive; }

  // setters
 public:
  void setActive(bool is_active) { m_is_activive = is_active; }
};
