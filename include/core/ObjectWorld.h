/*
 * @File    :   include\core\ObjectWorld.h
 * @Time    :   2026/03/15 22:36:12
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "ObjectScreen.h"

#include "glm/fwd.hpp"

class ObjectWorld : public ObjectScreen {
 protected:
  glm::vec2 m_position = glm::vec2(0);  // 物体的世界坐标（绝对坐标）

 public:
  /* 同步更新物体的坐标 */
  void update(const float &delta_time) override;

  // getters
 public:
  /* 获取物体的世界坐标 */
  glm::vec2 getPosition() { return m_position; }

  // setters
 public:
  /* 设置物体的世界坐标（同时更新物体的屏幕坐标） */
  void setPosition(const glm::vec2 &position);

  /* 设置物体的屏幕（渲染）位置（同时更新物体的世界坐标） */
  void setRenderPosition(const glm::vec2 &render_position) override;
};
