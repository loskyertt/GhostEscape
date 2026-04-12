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
class HUDStates;
class HUDText;
class HUDButton;
class Timer;

class SceneMain : public Scene {
 private:
  Player *m_player = nullptr;             // 玩家
  Spawner *m_spawner = nullptr;           // 敌人生成器
  UIMouse *m_ui_mouse = nullptr;          // UI 鼠标指针
  HUDStates *m_hud_states = nullptr;      // HUD 状态显示
  HUDText *m_text_score = nullptr;        // HUD 得分显示
  HUDButton *m_button_pause = nullptr;    // 暂停按钮
  HUDButton *m_button_restart = nullptr;  // 重新开始按钮
  HUDButton *m_button_back = nullptr;     // 返回按钮
  Timer *m_end_timer = nullptr;           // 结束计时器

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

  /* 保存数据 */
  void saveData(const std::string &file_path) override;

 private:
  /* 绘制背景 */
  void renderBackground();

  /* 更新得分 */
  void updateScore();

  void checkButtonPause();
  void checkButtonRestart();
  void checkButtonBack();

  void checkEndTimer();

  void checkSlowDown(float &delta_time);
};
