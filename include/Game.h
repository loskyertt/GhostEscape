/*
@File    :   include\Game.h
@Time    :   2026/03/15 16:28:26
@Author  :   loskyertt
@Github  :   https://github.com/loskyertt
@Desc    :   .....
*/

#pragma once

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <glm/glm.hpp>
#include <glm/fwd.hpp>

#include <string>

class Game {
 private:
  Game() = default;

  // 删除拷贝与赋值构造函数
  Game(const Game &) = delete;
  Game &operator=(const Game &) = delete;

 public:
  /* 单例模式 */
  static Game &getInstance();

 private:
  bool m_is_running = true;                // 游戏是否运行
  glm::vec2 m_screen_size = glm::vec2(0);  // 屏幕大小
  SDL_Window *m_window = nullptr;          // 窗口
  SDL_Renderer *m_renderer = nullptr;      // 渲染器

 public:
  /* 初始化游戏 */
  void init(const std::string &title, int width, int height);

  /* 运行游戏 */
  void run();

 private:
  /* 事件处理 */
  void handleEvent();

  /* 逻辑更新 */
  void update(const float &deltaTime);

  /* 渲染游戏 */
  void render();

  /* 清理游戏资源 */
  void clean();
};
