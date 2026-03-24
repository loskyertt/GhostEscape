/*
 * @File    :   include\Player.h
 * @Time    :   2026/03/15 23:44:48
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "affiliate/SpriteAnim.h"
#include "core/Entity.h"

class States;

class Effect;

class Player : public Entity {
 private:
  SpriteAnim *sprite_idle = nullptr;
  SpriteAnim *sprite_move = nullptr;

  bool m_is_moving = false;

  Effect *m_effect = nullptr;

 public:
  Player();

  ~Player() override;

 public:
  /* 初始化 */
  void init() override;

  /* 事件处理 */
  void handleEvents(SDL_Event &event) override;

  /* 更新 */
  void update(const float &delta_time) override;

  /* 渲染 */
  void render() override;

  /* 清理 */
  void clean() override;

 public:
  /* 键盘控制逻辑 */
  void keyboardControl();

  /* 相机跟随玩家 */
  void syncCamera();

  /* 判断当前物体状态 */
  void checkState();

  /* 改变物体运动状态，让运动状态切换更丝滑 */
  void changeState(bool is_moving);

  /* 检查玩家是否死亡 */
  void checkDeath();
};
