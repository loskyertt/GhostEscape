/*
 * @File    :   src\utils\include\raw\BackgroundStar.h
 * @Time    :   2026/04/12 14:22:20
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "core/Object.h"

#include <glm/fwd.hpp>

#include <SDL3/SDL_pixels.h>

#include <vector>

class BackgroundStar : public Object {
 protected:
  std::vector<glm::vec2> m_star_far;
  std::vector<glm::vec2> m_star_middle;
  std::vector<glm::vec2> m_star_near;

  float m_scale_far = 0.2f;
  float m_scale_middle = 0.5f;
  float m_scale_near = 0.7f;

  SDL_FColor m_color_far = {0, 0, 0, 1.0f};
  SDL_FColor m_color_middle = {0, 0, 0, 1.0f};
  SDL_FColor m_color_near = {0, 0, 0, 1.0f};

  float m_timer = 0.0f;
  int m_num = 2000;  // 每一层的星星数量

 public:
  void update(const float &delta_time) override;

  void render() override;

 public:
  /**
  * @brief 添加星空背景
  *
  * - @param parent 父对象
  * - @param num 星星数量
  * - @param scale_far 远处星星缩放比例
  * - @param scale_middle 中间星星缩放比例
  * - @param scale_near 近处星星缩放比例
  * - @return BackgroundStar*
  */
  static BackgroundStar *addBackgroundStar(Object *parent,
      int num,
      float scale_far,
      float scale_middle,
      float scale_near);
};
