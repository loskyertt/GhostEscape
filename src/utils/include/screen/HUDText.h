/*
 * @File    :   src\utils\include\screen\HUDText.h
 * @Time    :   2026/04/11 14:53:19
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "core/Defs.h"
#include "core/Object.h"
#include "core/ObjectScreen.h"

#include <glm/fwd.hpp>

#include <string>

class TextLable;
class Sprite;

class HUDText : public ObjectScreen {
 protected:
  TextLable *m_text_lable = nullptr;
  Sprite *m_sprite_bg = nullptr;

  glm::vec2 m_size = glm::vec2(0.0f);  // 背景图的大小

 public:
  /**
  * @brief 添加一个HUD文本
  *
  * @param parent 父对象
  * @param text 文本内容
  * @param position 位置
  * @param size 大小
  * @param font_path 字体路径
  * @param font_size 字体大小
  * @param bg_path 背景图片路径
  * @param anchor 锚点
  * @return HUDText*
  */
  static HUDText *addHUDText(
      Object *parent,
      const std::string &text,
      const glm::vec2 &render_position,
      const glm::vec2 &size,
      const std::string &font_path = "assets/font/VonwaonBitmap-16px.ttf",
      float font_size = 32.0f,
      const std::string &bg_path = "assets/UI/Textfield_01.png",
      Anchor anchor = Anchor::MIDDLE_CENTER);

  // getters
 public:
  TextLable *getTextLable() const { return m_text_lable; }

  Sprite *getSpriteBg() const { return m_sprite_bg; }

  std::string getText() const;

  // setters
 public:
  void setTextLable(TextLable *text_lable) { m_text_lable = text_lable; }

  void setSpriteBg(Sprite *sprite_bg) { m_sprite_bg = sprite_bg; }

  void setSize(const glm::vec2 &size);

  void setText(const std::string &text);

  void setSpriteBackground(const std::string &file_path);
};
