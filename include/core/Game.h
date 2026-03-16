/*
 * @File    :   include\Game.h
 * @Time    :   2026/03/15 16:28:26
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include <glm/glm.hpp>
#include <glm/fwd.hpp>

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>
#include <SDL3_mixer/SDL_mixer.h>

#include <string>

class Scene;

class AssetStore;

class Game {
 private:
  Game() = default;

  // 删除拷贝与赋值构造函数
  Game(const Game &) = delete;
  Game &operator=(const Game &) = delete;

 public:
  /* 单例模式 */
  static Game &getInstance();
  ~Game();

 private:
  bool m_is_running = true;                // 游戏是否运行
  glm::vec2 m_screen_size = glm::vec2(0);  // 屏幕大小

  SDL_Window *m_window = nullptr;      // 窗口
  SDL_Renderer *m_renderer = nullptr;  // 渲染器
  MIX_Mixer *m_mixer = nullptr;        // 混音器

  Scene *m_current_scene;     // 资源库
  AssetStore *m_asset_store;  // 当前场景

 private:
  const Uint64 m_FPS = 60;    // 游戏帧率
  Uint64 m_frame_delay = 0;   // 帧延迟：1,000,000,000 / 60 ≈ 16,666,667 纳秒
  float m_delta_time = 0.0f;  // 帧间隔

 public:
  /* 初始化游戏 */
  void init(const std::string &title, int width, int height);

  /* 运行游戏 */
  void run();

 private:
  /* 事件处理 */
  void handleEvents();

  /* 逻辑更新 */
  void update(const float &deltaTime);

  /* 渲染游戏 */
  void render();

  /* 清理游戏资源 */
  void clean();

  // 工具函数
 public:
  /* 绘制网格 */
  void drawGrid(const glm::vec2 &top_left, const glm::vec2 &bottom_right, float grid_width, const SDL_FColor &color);

  /* 绘制边框 */
  void
  drawBoundary(const glm::vec2 &top_left, const glm::vec2 &bottom_right, float boundary_width, const SDL_FColor &color);

  // gettters
 public:
  /* 获取屏幕大小 */
  glm::vec2 getScreenSize() { return m_screen_size; }

  /* 获取当前场景 */
  Scene *getCurrentScene() { return m_current_scene; }

  /* 获取资源 */
  AssetStore *getAssetStore() { return m_asset_store; }
};
