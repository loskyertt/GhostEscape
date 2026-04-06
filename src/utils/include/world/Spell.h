/*
 * @File    :   include\world\Spell.h
 * @Time    :   2026/04/05 00:10:07
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/Defs.h"
#include "core/ObjectWorld.h"
#include "affiliate/SpriteAnim.h"

#include <string>

class Spell : public ObjectWorld {
 protected:
  SpriteAnim *m_sprite_anim;
  float m_damage = 60.0f;

 public:
  void update(const float &delta_time) override;

 public:
  void attack();

 public:
  static Spell *addSpell(
      Object *parent,
      const std::string &file_path,
      const glm::vec2 &position,
      float damage,
      float scale = 1.0f,
      Anchor anchor = Anchor::MIDDLE_CENTER);

  // getters
 public:
  SpriteAnim *getSpriteAnim() const { return m_sprite_anim; }

  float getDamage() const { return m_damage; }

  // setters
 public:
  void setSpriteAnim(SpriteAnim *sprite_anim) { m_sprite_anim = sprite_anim; }

  void setDamage(float damage) { m_damage = damage; }
};
