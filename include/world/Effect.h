/*
 * @File    :   include\world\Effect.h
 * @Time    :   2026/03/20 22:04:26
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include <memory>
#include <string>
#include "affiliate/SpriteAnim.h"
#include "core/ObjectWorld.h"
#include "glm/fwd.hpp"

class Effect : public ObjectWorld {
 protected:
  SpriteAnim *m_sprite_anim = nullptr;
  std::unique_ptr<ObjectWorld> m_next_object;  // 播放完毕后，添加到场景中

 public:
  void update(const float &delta_time) override;

 public:
  void checkFinish();

 public:
  /*
   * @brief 添加特效到对象世界
   * @param parent 父对象
   * @param file_path 特效文件路径
   * @param pos 位置
   * @param scale 缩放
   * @param next_object 播放完毕后，添加到场景中的对象
   */
  static std::unique_ptr<Effect> addEffect(
      Object *parent,
      const std::string &file_path,
      glm::vec2 pos,
      float scale = 1.0f,
      std::unique_ptr<ObjectWorld> next_object = nullptr);

  // getters
 public:
  SpriteAnim *getSpriteAnim() const { return m_sprite_anim; }

  ObjectWorld *getNextObject() const { return m_next_object.get(); }

  // setters
 public:
  void setSpriteAnim(SpriteAnim *sprite_anim) { m_sprite_anim = sprite_anim; }

  void setNextObject(std::unique_ptr<ObjectWorld> next_object) { m_next_object = std::move(next_object); }
};
