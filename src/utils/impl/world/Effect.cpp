/*
 * @File    :   lib\world\Effect.cpp
 * @Time    :   2026/03/20 22:04:46
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "world/Effect.h"
#include "affiliate/SpriteAnim.h"
#include "core/Scene.h"

#include <SDL3/SDL_log.h>

void Effect::update(const float &delta_time) {
  ObjectWorld::update(delta_time);
  checkFinish();
}

void Effect::clean() {
  ObjectWorld::clean();
  if (m_next_object) {  // 如果 m_next_object 添加到了容器中，生命周期就应交给容器管理
    m_next_object->clean();
    delete m_next_object;
    m_next_object = nullptr;
  }
}

void Effect::checkFinish() {
  // #ifndef NDEBUG
  //   SDL_Log(">>> Effect::checkFinish() called");
  // #endif

  if (m_sprite_anim->getIsFinished()) {
    m_need_remove = true;
    if (m_next_object) {
      Game::getInstance().getCurrentScene()->safeAddChild(m_next_object);  // 添加到 SceneMain::m_children_back 中
      m_next_object = nullptr;
#ifndef NDEBUG
      SDL_Log("m_next_object 安全添加到了容器中......");
#endif
    }
  }
}

/* 添加特效到对象世界 */
Effect *Effect::addEffect(Object *parent,
    const std::string &file_path,
    glm::vec2 pos,
    float scale,
    ObjectWorld *next_object) {

#ifndef NDEBUG
  SDL_Log(">>> Effect::addEffect() called");
#endif

  auto effect = new Effect();
  effect->init();
  effect->m_sprite_anim = SpriteAnim::addSpriteAnim(effect, file_path, scale);
  effect->m_sprite_anim->setIsLoop(false);
  effect->setPosition(pos);
  effect->setNextObject(next_object);

  // Effect 挂在 parent 下
  if (parent) {
    parent->addChild(effect);
    // #ifndef NDEBUG
    //     SDL_Log("特效已经添加到了容器中......");
    // #endif
  }

  return effect;
}
