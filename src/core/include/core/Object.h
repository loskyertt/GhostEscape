/*
 * @File    :   include\core\Object.h
 * @Time    :   2026/03/15 18:52:06
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "Game.h"
#include "Defs.h"

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
  std::vector<Object *> m_children;       // 无实体，纯功能
  std::vector<Object *> m_children_back;  // 用于存储待添加的子对象

  bool m_is_activive = true;   // 物体是否处于活动状态
  bool m_need_remove = false;  // 是否需要移除该物体

  ObjectType m_type = ObjectType::NONE;  // 当前对象类型

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

  /* 添加 Object */
  virtual void addChild(Object *child);

  /* 移除 Object */
  virtual void removeChild(Object *child);

 public:
  /* 安全添加子节点 */
  void safeAddChild(Object *child);

  // getters
 public:
  bool getActiveState() const { return m_is_activive; }

  bool getNeedRemove() const { return m_need_remove; }

  ObjectType getType() const { return m_type; }

  // setters
 public:
  void setActive(bool is_active) { m_is_activive = is_active; }

  void setNeedRemove(bool need_remove) { m_need_remove = need_remove; }

  void setType(ObjectType type) { m_type = type; }
};
