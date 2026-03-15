/*
@File    :   lib\Game.cpp
@Time    :   2026/03/15 16:31:31
@Author  :   loskyertt
@Github  :   https://github.com/loskyertt
@Desc    :   .....
*/

#include "Game.h"

#include <glm/fwd.hpp>

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

/* 单例模式实现 */
Game &Game::getInstance() {
  static Game instance;
  return instance;
}

/* 初始化游戏 */
void Game::init(const std::string &title, int width, int height) {
  m_screen_size = glm::vec2(width, height);

  // SDL 初始化
  if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Init Error: %s", SDL_GetError());
    return;
  }

  // SDL_mixer 初始化
  if (!MIX_Init()) {
    SDL_Log("MIX_Init Error: %s", SDL_GetError());
    return;
  }
  // 创建 Mixer，绑定到默认音频输出设备
  MIX_Mixer *mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
  if (!mixer) {
    SDL_Log("MIX_CreateMixerDevice Error: %s", SDL_GetError());
    MIX_Quit();
    return;
  }

  // SDL_ttf 初始化
  if (!TTF_Init()) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "TTF_Init Error: %s", SDL_GetError());
    SDL_Quit();
    return;
  }

  // 创建窗口与渲染器
  SDL_CreateWindowAndRenderer(title.c_str(), width, height, SDL_WINDOW_RESIZABLE, &m_window, &m_renderer);

  // 设置窗口逻辑分辨率
  SDL_SetRenderLogicalPresentation(m_renderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);
}

/* 运行游戏，执行主循环 */
void Game::run() {
  while (m_is_running) {
    handleEvent();
    update(0.0f);
    render();
  }
}

/* 事件处理 */
void Game::handleEvent() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      m_is_running = false;
      return;
    }
  }
}

/* 逻辑更新 */
void Game::update(const float &deltaTime) {}

/* 渲染游戏 */
void Game::render() {}

/* 清理游戏资源 */
void Game::clean() {}
