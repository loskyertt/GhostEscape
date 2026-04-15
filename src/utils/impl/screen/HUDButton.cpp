/*
 * @File    :   src\utils\impl\screen\HUDButton.cpp
 * @Time    :   2026/04/11 20:55:18
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "screen/HUDButton.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>
#include "affiliate/Sprite.h"
#include "core/ObjectScreen.h"

bool HUDButton::handleEvents(SDL_Event &event) {
  // 判断鼠标按键按下
  if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) {
    // 判断鼠标左键
    if (event.button.button == SDL_BUTTON_LEFT && m_is_hovered) {
      m_is_pressed = true;
      Game::getInstance().playSound("assets/sound/UI_button08.wav");
      return true;
    }
  } else if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
    // 判断鼠标左键
    if (event.button.button == SDL_BUTTON_LEFT) {
      m_is_pressed = false;
      // 如果在图片区域里抬起，则触发点击事件
      if (m_is_hovered) {
        m_is_triggered = true;
        return true;
      }
    }
  }
  return false;
}

void HUDButton::update(const float &delta_time) {
  ObjectScreen::update(delta_time);

  checkHover();
  checkState();
}

void HUDButton::checkHover() {
  bool new_hover;  // 检测状态改变

  auto pos = m_render_postion + m_sprite_normal->getOffset();
  auto size = m_sprite_normal->getSize();
  if (Game::getInstance().isMouseInRect(pos, pos + size)) {
    new_hover = true;
  } else {
    new_hover = false;
  }

  if (new_hover != m_is_hovered) {
    m_is_hovered = new_hover;
    if (m_is_hovered && !m_is_pressed) {
      Game::getInstance().playSound("assets/sound/UI_button12.wav");
    }
  }
}

void HUDButton::checkState() {
  if (!m_is_pressed && !m_is_hovered) {
    m_sprite_normal->setActive(true);
    m_sprite_hover->setActive(false);
    m_sprite_pressed->setActive(false);
  } else if (!m_is_pressed && m_is_hovered) {
    m_sprite_normal->setActive(false);
    m_sprite_hover->setActive(true);
    m_sprite_pressed->setActive(false);
  } else {
    m_sprite_normal->setActive(false);
    m_sprite_hover->setActive(false);
    m_sprite_pressed->setActive(true);
  }
}

HUDButton *HUDButton::addHUDButton(Object *parent,
    const glm::vec2 &render_position,
    const std::string &file_path1,
    const std::string &file_path2,
    const std::string &file_path3,
    float scale,
    Anchor anchor) {
  auto hud_button = new HUDButton();
  hud_button->init();
  hud_button->setRenderPosition(render_position);
  hud_button->m_sprite_normal = Sprite::addSprite(hud_button, file_path1, scale, anchor);
  hud_button->m_sprite_hover = Sprite::addSprite(hud_button, file_path2, scale, anchor);
  hud_button->m_sprite_pressed = Sprite::addSprite(hud_button, file_path3, scale, anchor);
  hud_button->m_sprite_normal->setActive(true);
  hud_button->m_sprite_hover->setActive(false);
  hud_button->m_sprite_pressed->setActive(false);
  if (parent) {
    parent->addChild(hud_button);
  }
  return hud_button;
}

bool HUDButton::getIsTriggered() {
  // 触发后需要重置（保证只触发一次）
  if (m_is_triggered) {
    m_is_triggered = false;
    m_is_pressed = false;
    m_is_hovered = false;
    return true;
  }
  return false;
}

void HUDButton::setScale(float scale) {
  m_sprite_normal->setScale(scale);
  m_sprite_hover->setScale(scale);
  m_sprite_pressed->setScale(scale);
}
