/*
 * @File    :   include\core\ObjectAffiliate.h
 * @Time    :   2026/03/17 16:10:17
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "Defs.h"
#include "Object.h"
#include "core/ObjectScreen.h"

#include "glm/fwd.hpp"

class ObjectAffiliate : public Object {
 protected:
  ObjectScreen *m_parent = nullptr;   // 父节点
  glm::vec2 m_offset = glm::vec2(0);  // 物体的偏移量
  glm::vec2 m_size = glm::vec2(0);    // 物体的大小

  Anchor m_anchor = Anchor::MIDDLE_CENTER;  // 物体的锚点

 public:
  ObjectAffiliate();
  ~ObjectAffiliate() override;

  // getters
 public:
  /* 获取父节点 */
  ObjectScreen *getParent() { return m_parent; }

  /* 获取偏移量 */
  glm::vec2 getOffset() { return m_offset; }

  /* 获取大小 */
  glm::vec2 getSize() { return m_size; }

  /* 获取锚点 */
  Anchor getAnchor() { return m_anchor; }

  // setters
 public:
  /* 设置父节点 */
  void setParent(ObjectScreen *screen) { m_parent = screen; }

  /* 设置偏移量 */
  void setOffset(glm::vec2 offsset) { m_offset = offsset; }

  /* 设置大小 */
  void setSize(const glm::vec2 &size);

  /* 设置锚点 */
  void setAnchor(Anchor anchor) { m_anchor = anchor; }

  /* 设置缩放 */
  void setScale(float scale);

  /* 设置物体锚点 */
  void setOffsetByAnchor(Anchor anchor);
};
