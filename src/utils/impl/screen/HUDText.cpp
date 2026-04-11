/*
 * @File    :   src\utils\impl\screen\HUDText.cpp
 * @Time    :   2026/04/11 14:53:03
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "screen/HUDText.h"
#include "affiliate/TextLable.h"
#include "affiliate/Sprite.h"

HUDText *HUDText::addHUDText(
    Object *parent,
    const std::string &text,
    const glm::vec2 &render_position,
    const glm::vec2 &size,
    const std::string &font_path,
    float font_size,
    const std::string &bg_path,
    Anchor anchor) {

  auto hud_text = new HUDText();
  hud_text->init();
  hud_text->setRenderPosition(render_position);
  hud_text->setSpriteBg(Sprite::addSprite(hud_text, bg_path));
  hud_text->setSize(size);
  hud_text->setTextLable(TextLable::addTextLable(hud_text, text, font_path, font_size, anchor));
  if (parent) {
    parent->addChild(hud_text);
  }
  return hud_text;
}

std::string HUDText::getText() const {
  if (m_text_lable) {
    return m_text_lable->getText();
  }
  return "";
}

void HUDText::setSize(const glm::vec2 &size) {
  m_size = size;
  if (m_sprite_bg) {
    m_sprite_bg->setSize(size);
  }
}

void HUDText::setText(const std::string &text) {
  if (m_text_lable) {
    m_text_lable->setText(text);
  }
}

void HUDText::setSpriteBackground(const std::string &file_path) {
  if (m_sprite_bg) {
    m_sprite_bg->setTexture(file_path);
  } else {
    m_sprite_bg = Sprite::addSprite(this, file_path);
  }
}
