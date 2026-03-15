/*
 * @File    :   include\SceneMain.cpp
 * @Time    :   2026/03/15 19:17:35
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "core/Scene.h"
#include "glm/fwd.hpp"

class SceneMain : public Scene {
 private:
  glm::vec2 m_world_size = glm::vec2(0);  // 世界大小

 public:
  SceneMain() = default;
  ~SceneMain() override;

  /* 初始化 */
  void init() override;

  /* 事件处理 */
  void handleEvents(SDL_Event &event) override;

  /* 更新 */
  void update(const float &deltaTime) override;

  /* 渲染 */
  void render() override;

  /* 清理 */
  void clean() override;

 private:
  /* 绘制背景图片 */
  void renderBackground();
};
