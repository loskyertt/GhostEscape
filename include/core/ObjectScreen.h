/*
 * @File    :   include\core\ObjectScreen.h
 * @Time    :   2026/03/15 22:27:20
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "Object.h"

#include <glm/fwd.hpp>

class ObjectScreen : public Object {
 protected:
  glm::vec2 m_render_postion = glm::vec2(0);  // 物体的屏幕（渲染）位置

  // getters
 public:
  /* 获取物体的屏幕（渲染）位置 */
  glm::vec2 getRenderPosition() { return m_render_postion; }

  // setters
 public:
  /* 设置物体的屏幕（渲染）位置 */
  virtual void setRenderPosition(const glm::vec2 &render_position) { m_render_postion = render_position; }
};
