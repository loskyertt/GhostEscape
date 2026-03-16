/*
 * @File    :   include\Player.h
 * @Time    :   2026/03/15 23:44:48
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "core/Actor.h"

class Player : public Actor {
 public:
  Player();
  ~Player() override;

  /* 初始化 */
  void init() override;

  /* 事件处理 */
  void handleEvents(SDL_Event &event) override;

  /* 更新 */
  void update(const float &deltaTime) override;

  /* 渲染 */
  void render() override;

  /* 清理 */
  void clean() override;

 public:
  /* 键盘控制逻辑 */
  void keyboardControl();

  /* 玩家位置移动 */
  void move(const float &deltaTime);

  /* 相机跟随玩家 */
  void syncCamera();
};
