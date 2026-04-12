/*
 * @File    :   src\utils\include\screen\HUDButton.h
 * @Time    :   2026/04/11 20:55:15
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

class HUDButton : public ObjectScreen {
 protected:
  /**
   * - 按钮触发的逻辑：
   * - 当按下时，并不会触发，只有在松开时且鼠标仍悬浮在按钮上时才触发，
   * - 防止误触
   */

  bool m_is_triggered = false;  // 是否被触发
  bool m_is_hovered = false;    // 是否悬停
  bool m_is_pressed = false;    // 是否按下

  Sprite *m_sprite_normal = nullptr;   // 正常状态
  Sprite *m_sprite_hover = nullptr;    // 悬停状态
  Sprite *m_sprite_pressed = nullptr;  // 按下（event）状态

 public:
  bool handleEvents(SDL_Event &event) override;

  void update(const float &delta_time) override;

  void checkHover();
  void checkState();

 public:
  /**
  * @brief 添加HUD按钮
  *
  * - @param parent 父对象
  * - @param render_position 渲染位置
  * - @param file_path1 正常状态图片路径
  * - @param file_path2 悬停状态图片路径
  * - @param file_path3 按下状态图片路径
  * - @param scale 缩放比例
  * - @param anchor 锚点
  * - @return HUDButton*
  */
  static HUDButton *addHUDButton(Object *parent,
      const glm::vec2 &render_position,
      const std::string &file_path1,
      const std::string &file_path2,
      const std::string &file_path3,
      float scale = 1.0f,
      Anchor anchor = Anchor::BOTTOM_CENTER);

  // getters
 public:
  bool getIsTriggered();

  bool getIsHovered() const { return m_is_hovered; }

  bool getIsPressed() { return m_is_pressed; }

  // setters
 public:
  void setIsTriggered(bool triggered) { m_is_triggered = triggered; }

  void setIsHovered(bool hovered) { m_is_hovered = hovered; }

  void setIsPressed(bool pressed) { m_is_pressed = pressed; }
};
