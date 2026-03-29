/*
 * @File    :   lib\Enemy.cpp
 * @Time    :   2026/03/19 00:08:27
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "Enemy.h"
#include "affiliate/Collider.h"
#include "affiliate/SpriteAnim.h"
#include "core/Entity.h"
#include "SceneMain.h"
#include "raw/States.h"

#include <glm/geometric.hpp>

#include <SDL3/SDL_log.h>

void Enemy::update(const float &delta_time) {
  Entity::update(delta_time);

  if (!m_target_player->getActiveState()) {
    return;
  }

  aimTargetPlayer(m_target_player);
  move(delta_time);

  // === 测试代码 ===
  // timer += delta_time;
  // if (timer > 2.0f && timer < 4.0f) {
  //   // SDL_Log("状态改变为 HURT");
  //   changeState(State::HURT);
  // } else if (timer > 4.0f) {
  //   changeState(State::DEAD);
  //   // SDL_Log("状态改变为 DEAD");
  // }

  // remove();
  // m_target_player->getPosition();  // 测试是否当前对象被销毁引发程序崩溃

  attack();
}

void Enemy::init() {
  Entity::init();

  m_anim_normal = SpriteAnim::addSpriteAnim(this, "assets/sprite/ghost-Sheet.png", 2.0f);
  m_anim_hurt = SpriteAnim::addSpriteAnim(this, "assets/sprite/ghostHurt-Sheet.png", 2.0f);
  m_anim_die = SpriteAnim::addSpriteAnim(this, "assets/sprite/ghostDead-Sheet.png", 2.0f);
  m_anim_hurt->setActive(false);
  m_anim_die->setActive(false);
  m_anim_die->setIsLoop(false);

  m_current_anim = m_anim_normal;

  m_collider = Collider::addCollider(this, m_current_anim->getSize());
  m_states = States::addStates(this);
}

/* 向玩家移动 */
void Enemy::aimTargetPlayer(Player *target_player) {
  if (!target_player) {
    return;
  }

  auto direction = target_player->getPosition() - this->getPosition();
  direction = glm::normalize(direction);
  m_velocity = direction * m_max_speed;
}

/* 检查当前状态 */
void Enemy::checkState() {}

/* 切换当前状态 */
void Enemy::changeState(State new_state) {
  // SDL_Log(
  //     "changeState 被调用: new_state=%d, m_current_state=%d",
  //     static_cast<int>(new_state),
  //     static_cast<int>(m_current_state));

  if (new_state == m_current_state) {
    return;
  }

  m_current_anim->setActive(false);

  switch (new_state) {
    case State::NORMAL:
      m_current_anim = m_anim_normal;
      m_current_anim->setActive(true);
      break;
    case State::HURT:
      m_current_anim = m_anim_hurt;
      m_current_anim->setActive(true);
      break;
    case State::DEAD:
      m_current_anim = m_anim_die;
      m_current_anim->setActive(true);
      break;
  }
  m_current_state = new_state;
}

/* 删除死亡的 Enemy */
void Enemy::remove() {
  // SDL_Log("调用 Enemy::remove()");

  if (m_anim_die->getIsFinished()) {
    m_need_remove = true;
  }
}

/* 攻击玩家 */
void Enemy::attack() {
  // SDL_Log("调用 Enemy::attack()");
  if (!m_collider || !m_target_player || !m_target_player->getCollider()) {
    return;
  }

  if (m_collider->isColliding(m_target_player->getCollider())) {
    // TODO: 实现攻击逻辑
    // SDL_Log("调用 Enemy::attack()：Enemy 正在攻击 player!");
    if (m_states && m_target_player->getStates()) {
      m_target_player->takeDamage(m_states->getDamage());
    }
  }
}

/* 创建敌人 */
Enemy *Enemy::addEnemy(Object *parent, const glm::vec2 &position, Player *target_player) {
  auto enemy = new Enemy();
  enemy->init();
  enemy->setPosition(position);
  enemy->setTargetPlayer(target_player);
  if (parent) {
    parent->addChild(enemy);
  }
  return enemy;
}
