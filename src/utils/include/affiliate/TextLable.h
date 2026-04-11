/*
 * @File    :   src\utils\include\affiliate\TextLable.h
 * @Time    :   2026/04/11 12:18:25
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "core/Defs.h"
#include "core/ObjectAffiliate.h"
#include "core/ObjectScreen.h"

#include <SDL3_ttf/SDL_ttf.h>

#include <string>

class TextLable : public ObjectAffiliate {
 protected:
  TTF_Text *m_ttf_text = nullptr;
  std::string m_font_path;
  float m_font_size = 16;

 public:
  void render() override;

  void clean() override;

 public:
  /**
  * @brief 添加文本标签
  *
  * @param parent 父对象
  * @param text 文本内容
  * @param font_path 字体路径
  * @param font_size 字体大小
  * @param anchor 锚点位置
  * @return TextLable*
  */
  static TextLable *addTextLable(
      ObjectScreen *parent,
      const std::string &text,
      const std::string &font_path,
      float font_size,
      Anchor anchor = Anchor::MIDDLE_CENTER);

  // setters
 public:
  /* 用于初始化时设置字体和字体大小 */
  void setFont(const std::string &font_path, float font_size);

  /* 传入的是文本信息 */
  void setText(const std::string &text) { TTF_SetTextString(m_ttf_text, text.c_str(), text.length()); }

  /* 用于后期修改字体路径 */
  void setFontPath(const std::string &font_path);

  /* 用于后期修改字体大小 */
  void setFontSize(float font_size);

 private:
  /* 根据文字内容调节字体大小 */
  void updateFontSize();
};
