/*
 * @File    :   lib\affiliate\Collider.cpp
 * @Time    :   2026/03/20 15:17:41
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "affiliate/Collider.h"

/* 添加碰撞体到对象 */
Collider *Collider::addCollider(ObjectScreen *parent, glm::vec2 size, Type type, Anchor anchor) {
  auto collider = new Collider();
  collider->init();
  collider->setParent(parent);
  collider->setSize(size);
  collider->setType(type);
  collider->setOffsetByAnchor(anchor);

  if (parent) {
    parent->addChild(std::move(collider));
  }

  return collider;
}

/* 绘制碰撞体的边界框 */
void Collider::render() {
#ifndef NDEBUG
  ObjectAffiliate::render();

  auto pos = m_parent->getRenderPosition() + m_offset;
  m_game.renderColliders(pos, m_size);
#endif
}

bool Collider::isColliding(Collider *other) {
  if (!other) {
    return false;
  }

  // 两个圆的情况
  if (m_type == Type::CIRCLE && other->m_type == Type::CIRCLE) {
    // 计算两个圆的中心点
    auto point1 = m_parent->getPosition() + m_offset + m_size / 2.0f;
    auto point2 = other->m_parent->getPosition() + other->m_offset + other->m_size / 2.0f;
    /*
     * - glm::length()：计算两个坐标点之间的距离
     * - (m_size.x + other->m_size.x) / 2.0f：两个圆的半径之和
     * - 如果两点之间的距离小于半径之和，则说明两个圆相交
     */
    return glm::length(point1 - point2) < (m_size.x + other->m_size.x) / 2.0f;
  }

  // TODO：其他形状的碰撞检查

  return false;
}
