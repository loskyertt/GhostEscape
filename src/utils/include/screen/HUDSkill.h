/*
 * @File    :   src\utils\include\screen\HUDSkill.h
 * @Time    :   2026/04/11 13:41:37
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "core/Defs.h"
#include "core/Object.h"
#include "core/ObjectScreen.h"
#include "glm/fwd.hpp"

class Sprite;

class HUDSkill : public ObjectScreen {
 protected:
  Sprite *m_icon = nullptr;
  float m_percentage = 1.0f;

 public:
  void render() override;

 public:
  /**
  * @brief 添加技能HUD
  *
  * @param parent 父对象
  * @param file_path 图标文件路径
  * @param position 位置
  * @param scale 缩放
  * @param anchor 锚点
  * @return HUDSkill*
  */
  static HUDSkill *addHUDSkill(
      Object *parent,
      const std::string &file_path,
      glm::vec2 position,
      float scale = 1.0f,
      Anchor anchor = Anchor::MIDDLE_CENTER);

  // getters
 public:
  Sprite *getIcon() const { return m_icon; }

  float getPercentage() const { return m_percentage; }

  // setters
 public:
  void setIcon(Sprite *icon) { m_icon = icon; }

  void setPercentage(float percentage);
};
