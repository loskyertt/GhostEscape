/*
 * @File    :   src\utils\include\affiliate\AffiliateBar.h
 * @Time    :   2026/04/06 19:03:34
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */
#pragma once

#include "core/Defs.h"
#include "core/ObjectAffiliate.h"
#include "core/ObjectScreen.h"

#include <glm/ext/vector_float2.hpp>

#include <SDL3/SDL_pixels.h>

class AffiliateBar : public ObjectAffiliate {
 protected:
  float m_percentage = 1.0f;
  SDL_FColor m_color_high = {0, 1, 0, 1};     // 绿色
  SDL_FColor m_color_mid = {1, 0.65f, 0, 1};  // 橙色
  SDL_FColor m_color_low = {1, 0, 0, 1};      // 红色

 public:
  void render() override;

 public:
  /**
  * @brief 添加血量条
  *
  * @param parent 父对象
  * @param size 血量条大小
  * @param anchor 锚点
  * @return AffiliateBar* 血量条对象
  */
  static AffiliateBar *
  addAffiliateBar(ObjectScreen *parent, glm::vec2 size = glm::vec2(0.0f, 0.0f), Anchor anchor = Anchor::MIDDLE_CENTER);

  // getters
 public:
  float getPercentage() const { return m_percentage; }

  SDL_FColor getColorHigh() const { return m_color_high; }

  SDL_FColor getColorMid() const { return m_color_mid; }

  SDL_FColor getColorLow() const { return m_color_low; }

  // setters
 public:
  void setPercentage(float percentage) { m_percentage = percentage; }

  void setColorHigh(SDL_FColor color) { m_color_high = color; }

  void setColorMid(SDL_FColor color) { m_color_mid = color; }

  void setColorLow(SDL_FColor color) { m_color_low = color; }
};
