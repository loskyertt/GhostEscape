/*
 * @File    :   src\core\include\core\game\SceneTitle.h
 * @Time    :   2026/04/11 19:50:37
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "core/Scene.h"

#include <SDL3/SDL_pixels.h>

class HUDButton;
class HUDText;
class UIMouse;

class SceneTitle : public Scene {
 protected:
  SDL_FColor m_boundary_color{0.5f, 0.5f, 0.5f, 1.0f};

  float m_color_timer = 0.0f;

  HUDButton *m_button_start = nullptr;
  HUDButton *m_button_credits = nullptr;
  HUDButton *m_button_quit = nullptr;

  HUDText *m_text_credits = nullptr;

  UIMouse *m_ui_mouse = nullptr;

 public:
  /* 初始化 */
  void init() override;

  /* 事件处理 */
  bool handleEvents(SDL_Event &event) override;

  /* 更新 */
  void update(const float &delta_time) override;

  /* 渲染 */
  void render() override;

  /* 清理 */
  void clean() override;

  /* 载入数据 */
  void loadDate(const std::string &file_path) override;

 private:
  /* 渲染背景 */
  void renderBackground();

  /* 更新颜色 */
  void updateColor();

  void checkButtonQuit();
  void checkButtonStart();
  void checkButtonCredits();
};
