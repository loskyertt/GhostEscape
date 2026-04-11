/*
 * @File    :   src\utils\impl\affiliate\TextLable.cpp
 * @Time    :   2026/04/11 12:24:00
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/AssetStore.h"

#include "affiliate/TextLable.h"
#include "glm/fwd.hpp"

#include <SDL3_ttf/SDL_ttf.h>

void TextLable::render() {
  ObjectAffiliate::render();

  auto pos = m_parent->getRenderPosition() + m_offset;
  TTF_DrawRendererText(m_ttf_text, pos.x, pos.y);
}

void TextLable::clean() {
  if (m_ttf_text) {
    TTF_DestroyText(m_ttf_text);
    m_ttf_text = nullptr;
  }
}

TextLable *TextLable::addTextLable(
    ObjectScreen *parent,
    const std::string &text,
    const std::string &font_path,
    float font_size,
    Anchor anchor) {
  auto text_lable = new TextLable();
  text_lable->init();
  text_lable->setFont(font_path, font_size);
  text_lable->setText(text);
  text_lable->setAnchor(anchor);
  text_lable->updateFontSize();
  if (parent) {
    parent->addChild(text_lable);
    text_lable->setParent(parent);
  }
  return text_lable;
}

void TextLable::setFont(const std::string &font_path, float font_size) {
  m_font_path = font_path;
  m_font_size = font_size;
  // 有可新的 ttf_font，需要载入到 AssetStore 里
  auto font = m_game.getAssetStore()->getFont(font_path, font_size);
  if (!m_ttf_text) {
    m_ttf_text = m_game.createText("", font_path, font_size);
  }
  TTF_SetTextFont(m_ttf_text, font);
}

void TextLable::setFontPath(const std::string &font_path) {
  m_font_path = font_path;
  // 从 AssetStore 里获取字体
  auto font = m_game.getAssetStore()->getFont(font_path, m_font_size);
  TTF_SetTextFont(m_ttf_text, font);
}

void TextLable::setFontSize(float font_size) {
  m_font_size = font_size;
  // 从 AssetStore 里获取字体
  auto font = m_game.getAssetStore()->getFont(m_font_path, m_font_size);
  TTF_SetTextFont(m_ttf_text, font);
}

void TextLable::updateFontSize() {
  int w, h;
  TTF_GetTextSize(m_ttf_text, &w, &h);
  setSize(glm::vec2(w, h));
}
