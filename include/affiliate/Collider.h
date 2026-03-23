/*
 * @File    :   include\affiliate\Collider.h
 * @Time    :   2026/03/20 14:59:33
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "core/ObjectAffiliate.h"

#include <glm/fwd.hpp>

class Collider : public ObjectAffiliate {
 protected:
  enum class Type {
    CIRCLE,  // m_size 的 x 轴为直径，默认 y = x
    RECTANGLE,
  };

  Type m_type = Type::CIRCLE;

 public:
  /* 添加碰撞体到对象 */
  static Collider *addCollider(
      ObjectScreen *parent,
      glm::vec2 size,
      Type type = Type::CIRCLE,
      Anchor anchor = Anchor::MIDDLE_CENTER);

 public:
  /* 绘制碰撞体的边界框 */
  void render() override;

 public:
  /* 检测是否碰撞 */
  bool isColliding(Collider *other);

  // getters
 public:
  Type getType() const { return m_type; }

  // setters
 public:
  void setType(Type type) { m_type = type; }
};
