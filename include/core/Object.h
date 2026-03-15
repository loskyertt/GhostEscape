/*
 * @File    :   include\core\Object.h
 * @Time    :   2026/03/15 18:52:06
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "Game.h"

/*
 * - 约定：
 * - 所有的类，不在构造函数和析构函数做任何事
 * - 初始化：init 中进行
 * - 清理：clean 中进行
 */
class Object {
 protected:
  Game &m_game = Game::getInstance();

 public:
  Object() = default;
  virtual ~Object() = default;

  virtual void init() = 0;                          // 初始化
  virtual void handleEvents(SDL_Event &event) = 0;                  // 事件处理
  virtual void update(const float &deltaTime) = 0;  // 更新
  virtual void render() = 0;                        // 渲染
  virtual void clean() = 0;                         // 清理
};
