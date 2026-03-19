/*
 * @File    :   include\Enemy.h
 * @Time    :   2026/03/18 23:55:47
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   Enemy class declaration
 */

#pragma once

#include "Player.h"
#include "affiliate/SpriteAnim.h"

enum class State {
  NORMAL,
  HURT,
  DEAD,
};

class Enemy : public Actor {
 private:
  Player *m_target_player = nullptr;
  SpriteAnim *m_current_anim = nullptr;

  SpriteAnim *m_anim_normal = nullptr;
  SpriteAnim *m_anim_hurt = nullptr;
  SpriteAnim *m_anim_die = nullptr;

 private:
  State m_current_state = State::NORMAL;

  float timer = 0.0f;

 public:
  void update(const float &delta_time) override;

  void init() override;

 public:
  /* 向玩家移动 */
  void aimTargetPlayer(Player *target_player);

  /* 检查当前状态 */
  void checkState();

  /* 切换当前状态 */
  void changeState(State new_state);

  /* 删除死亡的 Enemy */
  void remove();

  // getters
 public:
  Player *getTargetPlayer() { return m_target_player; }

  // setters
 public:
  void setTargetPlayer(Player *target_player) { m_target_player = target_player; }
};
