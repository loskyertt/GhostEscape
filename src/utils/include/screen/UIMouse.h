/*
 * @File    :   include\screen\UIMouse.h
 * @Time    :   2026/03/29 22:08:38
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/Defs.h"
#include "core/ObjectScreen.h"
#include "affiliate/Sprite.h"

class UIMouse : public ObjectScreen {
 protected:
  Sprite *m_sprite1 = nullptr;
  Sprite *m_sprite2 = nullptr;
  float m_timer = 0.0f;

 public:
  void update(const float &delta_time) override;

 public:
  /**
  * @brief 添加鼠标对象
  *
  * - @param parent 父对象
  * - @param sprite1Path 精灵1路径
  * - @param sprite2Path 精灵2路径
  * - @param scale 缩放比例
  * - @param anchor 锚点
  * - @return UIMouse* 鼠标对象指针
  */
  static UIMouse *addUIMouse(Object *parent,
      const std::string &sprite1Path,
      const std::string &sprite2Path,
      float scale = 1.0f,
      Anchor anchor = Anchor::MIDDLE_CENTER);

  //getters
 public:
  Sprite *getSprite1() const { return m_sprite1; }

  Sprite *getSprite2() const { return m_sprite2; }

  float getTimer() const { return m_timer; }

  //setters
 public:
  void setSprite1(Sprite *sprite) { m_sprite1 = sprite; }

  void setSprite2(Sprite *sprite) { m_sprite2 = sprite; }

  void setTimer(float timer) { m_timer = timer; }
};
