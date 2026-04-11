/*
 * @File    :   include\Enemy.h
 * @Time    :   2026/03/18 23:55:47
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   Enemy class declaration
 */

#pragma once

#include "core/game/Player.h"
#include "core/Object.h"

#include "affiliate/SpriteAnim.h"

class Enemy : public Entity {
 private:
  Player *m_target_player = nullptr;     // 目标玩家
  SpriteAnim *m_current_anim = nullptr;  // 当前动画

  SpriteAnim *m_anim_normal = nullptr;  // 普通状态动画
  SpriteAnim *m_anim_hurt = nullptr;    // 受伤状态动画
  SpriteAnim *m_anim_die = nullptr;     // 死亡状态动画

 private:
  enum class State {
    NORMAL,
    HURT,
    DEAD,
  };

  State m_current_state = State::NORMAL;
  int m_score = 10;  // 击败敌人获得的分数

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

  /* 攻击玩家 */
  void attack();

 public:
  /* 创建敌人 */
  static Enemy *addEnemy(Object *parent, const glm::vec2 &position, Player *target_player);

  // getters
 public:
  Player *getTargetPlayer() const { return m_target_player; }

  // setters
 public:
  void setTargetPlayer(Player *target_player) { m_target_player = target_player; }
};
