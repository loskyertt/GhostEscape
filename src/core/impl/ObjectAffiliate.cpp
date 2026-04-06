/*
 * @File    :   lib\core\ObjectAffiliate.cpp
 * @Time    :   2026/03/17 16:10:55
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/ObjectAffiliate.h"

ObjectAffiliate::ObjectAffiliate() = default;

ObjectAffiliate::~ObjectAffiliate() = default;

/* 设置大小 */
void ObjectAffiliate::setSize(const glm::vec2 &size) {
  m_size = size;
  setOffsetByAnchor(m_anchor);
}

/* 设置缩放 */
void ObjectAffiliate::setScale(float scale) {
  m_size *= scale;
  setOffsetByAnchor(m_anchor);
}

/* 设置物体锚点 */
void ObjectAffiliate::setOffsetByAnchor(Anchor anchor) {
  m_anchor = anchor;

  switch (anchor) {
    case Anchor::NONE:
      break;
    case Anchor::TOP_LEFT:
      m_offset = glm::vec2(0, 0);
      break;
    case Anchor::TOP_CENTER:
      m_offset = glm::vec2(-m_size.x / 2.0f, 0);
      break;
    case Anchor::TOP_RIGHT:
      m_offset = glm::vec2(-m_size.x, 0);
      break;
    case Anchor::MIDDLE_LEFT:
      m_offset = glm::vec2(0, -m_size.y / 2.0f);
      break;
    case Anchor::MIDDLE_CENTER:
      m_offset = glm::vec2(-m_size.x / 2.0f, -m_size.y / 2.0f);
      break;
    case Anchor::MIDDLE_RIGHT:
      m_offset = glm::vec2(-m_size.x, -m_size.y / 2.0f);
      break;
    case Anchor::BOTTOM_LEFT:
      m_offset = glm::vec2(0, m_size.y);
      break;
    case Anchor::BOTTOM_CENTER:
      m_offset = glm::vec2(m_size.x / 2.0f, m_size.y);
      break;
    case Anchor::BOTTOM_RIGHT:
      m_offset = glm::vec2(m_size.x, m_size.y);
      break;
  }
}
