/*
 * @File    :   src\core\impl\Game.cpp
 * @Time    :   2026/03/15 16:31:31
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/Game.h"
#include "core/AssetStore.h"
#include "core/game/SceneMain.h"
#include "affiliate/Sprite.h"

#include <glm/fwd.hpp>

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_surface.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_video.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <cstddef>

/* 单例模式实现 */
Game &Game::getInstance() {
  static Game instance;
  return instance;
}

Game::~Game() {
  SDL_Log("调用 ~Game()：程序退出");
}

/* 初始化游戏 */
void Game::init(const std::string &title, int width, int height) {
  m_screen_size = glm::vec2(width, height);

  // === SDL 初始化 ===
  if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Init Error: %s", SDL_GetError());
    return;
  }

  // === SDL_mixer 初始化 ===
  if (!MIX_Init()) {
    SDL_Log("MIX_Init Error: %s", SDL_GetError());
    return;
  }
  // 创建 Mixer，绑定到默认音频输出设备
  m_mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
  if (!m_mixer) {
    SDL_Log("MIX_CreateMixerDevice Error: %s", SDL_GetError());
    MIX_Quit();
    return;
  }

  // === SDL_ttf 初始化 ===
  if (!TTF_Init()) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "TTF_Init Error: %s", SDL_GetError());
    SDL_Quit();
    return;
  }

  // === 创建窗口与渲染器 ===
  SDL_CreateWindowAndRenderer(title.c_str(), width, height, SDL_WINDOW_RESIZABLE, &m_window, &m_renderer);
  if (!m_window || !m_renderer) {
    SDL_Log("SDL_CreateWindowAndRenderer Error: %s", SDL_GetError());
    SDL_Quit();
    return;
  }

  // === 设置窗口逻辑分辨率 ===
  SDL_SetRenderLogicalPresentation(m_renderer, width, height, SDL_LOGICAL_PRESENTATION_LETTERBOX);

  // === 设置字体 ===
  m_ttf_engine = TTF_CreateRendererTextEngine(m_renderer);
  if (!m_ttf_engine) {
    SDL_Log("TTF_CreateRendererTextEngine Error: %s", SDL_GetError());
    SDL_Quit();
    return;
  }

  // === 计算帧延迟 ===
  m_frame_delay = 1000000000 / m_FPS;

  // === 创建资源管理器 ===
  m_asset_store = new AssetStore(m_renderer, m_mixer);

  // === 创建场景 ===
  m_current_scene = new SceneMain();
  m_current_scene->init();
}

/* 运行游戏，执行主循环 */
void Game::run() {
  while (m_is_running) {
    auto start = SDL_GetTicksNS();

    handleEvents();
    update(m_delta_time);
    render();

    auto end = SDL_GetTicksNS();
    auto elapsed = end - start;  // 实际工作时间

    if (elapsed < m_frame_delay) {
      // SDL_DelayNS 补齐到 16ms，delta_time 始终是稳定的 1/60 秒
      SDL_DelayNS(m_frame_delay - elapsed);
      // 正常帧：delta_time 用目标帧时长（稳定）
      m_delta_time = static_cast<float>(static_cast<double>(m_frame_delay) / 1.0e9);
    } else {
      // 超时帧：delta_time 用实际耗时（游戏逻辑不会慢动作）
      m_delta_time = static_cast<float>(static_cast<double>(elapsed) / 1.0e9);
    }
    // SDL_Log("FPS: %f", 1.0 / static_cast<double>(m_delta_time));
  }
}

/* 事件处理 */
void Game::handleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_EVENT_QUIT) {
      m_is_running = false;
      break;
    }

    m_current_scene->handleEvents(event);
  }
}

/* 更新游戏场景 */
void Game::update(const float &delta_time) {
  m_mouse_buttons = SDL_GetMouseState(&m_mouse_pos.x, &m_mouse_pos.y);
  m_current_scene->update(delta_time);
}

/* 渲染游戏 */
void Game::render() {
  SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);  // 先设清屏色
  SDL_RenderClear(m_renderer);                       // 再清屏
  m_current_scene->render();                         // 渲染当前场景
  SDL_RenderPresent(m_renderer);
}

/* 清理游戏资源 */
void Game::clean() {
  // 清理场景
  if (m_current_scene) {
    m_current_scene->clean();
    delete m_current_scene;
  }

  // 清理资源
  if (m_asset_store) {
    m_asset_store->clean();
    delete m_asset_store;
  }

  if (m_ttf_engine) {
    TTF_DestroyRendererTextEngine(m_ttf_engine);
  }

  // 释放渲染器和窗口
  if (m_renderer) {
    SDL_DestroyRenderer(m_renderer);
  }
  if (m_window) {
    SDL_DestroyWindow(m_window);
  }

  // 关闭设备（销毁 Mixer）
  if (m_mixer) {
    MIX_DestroyMixer(m_mixer);
  }

  // 退出 MIX
  MIX_Quit();

  // 退出 TTF
  TTF_Quit();

  // 退出 SDL
  SDL_Quit();
}

/* 绘制网格 */
void Game::drawGrid(
    const glm::vec2 &top_left,
    const glm::vec2 &bottom_right,
    float grid_width,
    const SDL_FColor &color) {
  SDL_SetRenderDrawColorFloat(m_renderer, color.r, color.g, color.b, color.a);

  for (float x = top_left.x; x <= bottom_right.x; x += grid_width) {
    /*
     * 起点坐标 -> 终点坐标
     * (x, top_left.y) -> (x, bottom_right.y) 构成一条竖线
     */
    SDL_RenderLine(m_renderer, x, top_left.y, x, bottom_right.y);
  }
  for (float y = top_left.y; y <= bottom_right.y; y += grid_width) {
    SDL_RenderLine(m_renderer, top_left.x, y, bottom_right.x, y);
  }

  // 还原颜色
  SDL_SetRenderDrawColorFloat(m_renderer, 0.0f, 0.0f, 0.0f, 1.0f);
}

/* 绘制边框 */
void Game::drawBoundary(
    const glm::vec2 &top_left,
    const glm::vec2 &bottom_right,
    float boundary_width,
    const SDL_FColor &color) {
  SDL_SetRenderDrawColorFloat(m_renderer, color.r, color.g, color.b, color.a);

  for (float i = 0; i < boundary_width; i++) {
    SDL_FRect rect = {
        top_left.x - i,
        top_left.y - i,
        bottom_right.x - top_left.x + i * 2,
        bottom_right.y - top_left.y + i * 2,
    };
    SDL_RenderRect(m_renderer, &rect);
  }

  // 还原颜色
  SDL_SetRenderDrawColorFloat(m_renderer, 0.0f, 0.0f, 0.0f, 1.0f);
}

/* 渲染材质 */
void Game::renderTexture(
    const Texture &texture,
    const glm::vec2 &position,
    const glm::vec2 &size,
    const glm::vec2 &mask) {
  SDL_FRect src_rect = {
      texture.src_rect.x,
      texture.src_rect.y,
      texture.src_rect.w * mask.x,
      texture.src_rect.h * mask.y,
  };

  SDL_FRect dst_rect = {
      position.x,
      position.y,
      size.x * mask.x,
      size.y * mask.y,
  };

  SDL_RenderTextureRotated(
      m_renderer,
      texture.texture,
      &src_rect,
      &dst_rect,
      static_cast<double>(texture.angle),
      nullptr,
      texture.is_flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

/* 渲染碰撞体（用于调试） */
void Game::renderColliders(const glm::vec2 &position, const glm::vec2 &size, float alpha) {
  auto texture = m_asset_store->getImage("assets/UI/circle.png");
  SDL_FRect rect = {
      position.x,
      position.y,
      size.x,
      size.y,
  };
  SDL_SetTextureAlphaModFloat(texture, alpha);
  SDL_RenderTexture(m_renderer, texture, NULL, &rect);
}

/* 渲染血量条 */
void Game::renderHorizontalBar(const glm::vec2 &position, const glm::vec2 &size, float percentage, SDL_FColor color) {
  SDL_SetRenderDrawColorFloat(m_renderer, color.r, color.g, color.b, color.a);

  SDL_FRect boundary_rect = {
      position.x,
      position.y,
      size.x,
      size.y,
  };
  SDL_FRect fill_rect = {
      position.x,
      position.y,
      size.x * percentage,
      size.y,
  };
  SDL_RenderRect(m_renderer, &boundary_rect);
  SDL_RenderFillRect(m_renderer, &fill_rect);
  SDL_SetRenderDrawColorFloat(m_renderer, 0.0f, 0.0f, 0.0f, 1.0f);
}

/* 创建文本 */
TTF_Text *Game::createText(const std::string &text, const std::string &font_path, float font_size) {
  return TTF_CreateText(m_ttf_engine, m_asset_store->getFont(font_path, font_size), text.c_str(), 0);
}

/* 随机数函数 */
float Game::randomFloat(float min, float max) {
  std::uniform_real_distribution<float> distribution(min, max);
  return distribution(gen);
}

int Game::randomInt(int min, int max) {
  std::uniform_int_distribution<int> distribution(min, max);
  return distribution(gen);
}

glm::vec2 Game::randomVec2(glm::vec2 min, glm::vec2 max) {
  return glm::vec2(randomFloat(min.x, max.x), randomFloat(min.y, max.y));
}

glm::ivec2 Game::randomIvec2(glm::ivec2 min, glm::ivec2 max) {
  return glm::ivec2(randomInt(min.x, max.x), randomInt(min.y, max.y));
}
