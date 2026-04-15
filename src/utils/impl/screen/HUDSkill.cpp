/*
 * @File    :   src\utils\impl\screen\HUDSkill.cpp
 * @Time    :   2026/04/11 13:51:01
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/ObjectScreen.h"

#include "screen/HUDSkill.h"
#include "affiliate/Sprite.h"

#include <glm/fwd.hpp>

#include <SDL3/SDL_render.h>

#include <algorithm>

HUDSkill *
HUDSkill::addHUDSkill(Object *parent, const std::string &file_path, glm::vec2 position, float scale, Anchor anchor) {
  auto hud_skill = new HUDSkill();
  hud_skill->init();
  hud_skill->m_icon = Sprite::addSprite(hud_skill, file_path, scale, anchor);
  hud_skill->setRenderPosition(position);
  if (parent) {
    parent->addChild(hud_skill);
  }
  return hud_skill;
}

void HUDSkill::render() {
  // 先绘制浅色背景
  SDL_SetTextureColorModFloat(m_icon->getTexture().texture, 0.3f, 0.3f, 0.3f);
  auto pos = getRenderPosition() + m_icon->getOffset();
  Game::getInstance().renderTexture(m_icon->getTexture(), pos, m_icon->getSize());
  SDL_SetTextureColorModFloat(m_icon->getTexture().texture, 1.0f, 1.0f, 1.0f);

  // 然后正常绘制
  ObjectScreen::render();
}

void HUDSkill::setPercentage(float percentage) {
  percentage = std::clamp(percentage, 0.0f, 1.0f);
  m_percentage = percentage;
  if (m_icon) {
    m_icon->setPercentage(glm::vec2(1.0f, percentage));
  }
}
