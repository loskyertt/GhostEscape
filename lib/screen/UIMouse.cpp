/*
 * @File    :   lib\screen\UIMouse.cpp
 * @Time    :   2026/03/29 22:08:42
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "screen/UiMouse.h"
#include "affiliate/Sprite.h"

void UIMouse::update(const float &deltaTime) {
  m_timer += deltaTime;
  if (m_timer < 0.3f) {
    m_sprite1->setActive(true);
    m_sprite2->setActive(false);
  } else if (m_timer < 0.6f) {
    m_sprite1->setActive(false);
    m_sprite2->setActive(true);
  } else {
    m_timer = 0.0f;
  }

  setRenderPosition(m_game.getMousePos());
}

UIMouse *UIMouse::addUIMouse(
    Object *parent,
    const std::string &sprite1Path,
    const std::string &sprite2Path,
    float scale,
    Anchor anchor) {
  UIMouse *ui_mouse = new UIMouse();
  ui_mouse->init();
  ui_mouse->m_sprite1 = Sprite::addSprite(ui_mouse, sprite1Path, scale, anchor);
  ui_mouse->m_sprite2 = Sprite::addSprite(ui_mouse, sprite2Path, scale, anchor);

  if (parent) {
    parent->addChild(ui_mouse);
  }

  return ui_mouse;
}
