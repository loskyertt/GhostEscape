/*
 * @File    :   include\SceneMain.h
 * @Time    :   2026/03/15 19:17:35
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "core/Scene.h"

class Player;
class Spawner;
class UIMouse;

class SceneMain : public Scene {
 private:
  Player *m_player;    // 玩家
  Spawner *m_spawner;  // 敌人生成器
  UIMouse *m_ui_mouse;  // UI 鼠标指针

 public:
  SceneMain();
  ~SceneMain() override;

  /* 初始化 */
  void init() override;

  /* 事件处理 */
  void handleEvents(SDL_Event &event) override;

  /* 更新 */
  void update(const float &delta_time) override;

  /* 渲染 */
  void render() override;

  /* 清理 */
  void clean() override;

 private:
  /* 绘制背景 */
  void renderBackground();
};
