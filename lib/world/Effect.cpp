/*
 * @File    :   lib\world\Effect.cpp
 * @Time    :   2026/03/20 22:04:46
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "world/Effect.h"
#include "SceneMain.h"
#include "affiliate/SpriteAnim.h"

#include <SDL3/SDL_log.h>

void Effect::update(const float &delta_time) {
  ObjectWorld::update(delta_time);
  checkFinish();
}

void Effect::checkFinish() {
  if (m_sprite_anim && m_sprite_anim->getIsFinished()) {
    m_need_remove = true;
    if (m_next_object) {
      // 此时: m_next_object 指向有效对象
      m_game.getCurrentScene()->safeAddChild(std::move(m_next_object));
      /*
       * 此时:
       * - m_next_object 变为 nullptr
       * - Scene 中的容器现在拥有该对象的所有权
       * - 原对象没有被删除，只是所有权转移了
       */
    }
  }
}

/* 添加特效到对象世界 */
std::unique_ptr<Effect> Effect::addEffect(
    Object *parent,
    const std::string &file_path,
    glm::vec2 pos,
    float scale,
    std::unique_ptr<ObjectWorld> next_object) {

#ifndef NDEBUG
  SDL_Log("调用 Effect::addEffect()");
#endif

  auto effect = std::make_unique<Effect>();
  effect->init();
  // 让 SpriteAnim 挂在新创建的 Effect 下
  effect->m_sprite_anim = SpriteAnim::addSpriteAnim(effect.get(), file_path, scale);
  effect->m_sprite_anim->setIsLoop(false);
  effect->setPosition(pos);
  effect->setNextObject(std::move(next_object));

  // Effect 挂在 parent 下
  if (parent) {
    SDL_Log("=== addEffect 的分界线 ===");
    parent->addChild(std::move(effect));
    SDL_Log("=== addEffect 的分界线 ===");
    return nullptr;
  }

  return std::move(effect);  // 显式移动
}
