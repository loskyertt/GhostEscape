/*
 * @File    :   src\core\include\core\Game.h
 * @Time    :   2026/03/15 16:28:26
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include <glm/glm.hpp>
#include <glm/fwd.hpp>

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <random>
#include <string>

class Scene;

class AssetStore;

struct Texture;

class Game final {
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
  bool m_is_running = true;                  // 游戏是否运行
  glm::vec2 m_screen_size = glm::vec2(0);    // 屏幕大小 (width, height)
  glm::vec2 m_mouse_pos = glm::vec2(0);      // 鼠标位置 (x, y)
  SDL_MouseButtonFlags m_mouse_buttons = 0;  // 鼠标按键状态

  SDL_Window *m_window = nullptr;          // 窗口
  SDL_Renderer *m_renderer = nullptr;      // 渲染器
  MIX_Mixer *m_mixer = nullptr;            // 混音器
  MIX_Track *m_music_track = nullptr;      // 音乐（长音频）轨道
  MIX_Track *m_sfx_track = nullptr;        // 音效（短音频）轨道
  TTF_TextEngine *m_ttf_engine = nullptr;  // 字体引擎

  Scene *m_current_scene;     // 当前场景
  AssetStore *m_asset_store;  // 资源库

 private:
  const Uint64 m_FPS = 60;    // 游戏帧率
  Uint64 m_frame_delay = 0;   // 帧延迟：1,000,000,000 / 60 ≈ 16,666,667 纳秒
  float m_delta_time = 0.0f;  // 帧间隔

  int m_score = 0;
  int m_high_score = 0;

  std::mt19937 gen = std::mt19937(std::random_device{}());

 public:
  /* 初始化游戏 */
  void init(const std::string &title, int width, int height);

  /* 运行游戏 */
  void run();

  /* 退出游戏 */
  void quit() { m_is_running = false; }

 private:
  /* 事件处理 */
  void handleEvents();

  /* 更新游戏场景 */
  void update(const float &delta_time);

  /* 渲染游戏 */
  void render();

  /* 清理游戏资源 */
  void clean();

  // 工具函数
 public:
  /* 绘制网格 */
  void drawGrid(const glm::vec2 &top_left, const glm::vec2 &bottom_right, float grid_width, const SDL_FColor &color);

  /**
   * @brief 绘制边框
   *
   * - @param top_left 左上角位置
   * - @param bottom_right 右下角位置
   * - @param boundary_width 边框宽度
   * - @param color 边框颜色
   */
  void
  drawBoundary(const glm::vec2 &top_left, const glm::vec2 &bottom_right, float boundary_width, const SDL_FColor &color);

  /**
   * @brief 渲染材质
   *
   * - @param texture 纹理
   * - @param position 位置
   * - @param size 大小
   * - @param mask 模板（默认为1.0f）
   */
  void renderTexture(
      const Texture &texture,
      const glm::vec2 &position,
      const glm::vec2 &size,
      const glm::vec2 &mask = glm::vec2(1.0f));

  /* 渲染碰撞体（用于调试） */
  void renderColliders(const glm::vec2 &position, const glm::vec2 &size, float alpha = 0.5f);

  /* 渲染血量条 */
  void renderHorizontalBar(const glm::vec2 &position, const glm::vec2 &size, float percentage, SDL_FColor color);

  /* 创建文本 */
  TTF_Text *createText(const std::string &text, const std::string &font_path, float font_size);

  /* 随机数函数 */
  float randomFloat(float min, float max);
  int randomInt(int min, int max);
  glm::vec2 randomVec2(glm::vec2 min, glm::vec2 max);
  glm::ivec2 randomIvec2(glm::ivec2 min, glm::ivec2 max);

  /* 音频函数 */
  void playMusic(const std::string &music_path, bool loop = true);
  void stopMusic();
  void pauseMusic();
  void resumeMusic();
  void playSound(const std::string &sound_path);
  void stopSound();
  void pauseSound();
  void resumeSound();

  /* 增加分数 */
  void addScore(int score);

  /* 判断鼠标是否在材质范围内 */
  bool isMouseInRect(const glm::vec2 &top_left, const glm::vec2 &bottom_right);

  // gettters
 public:
  /* 获取屏幕大小 */
  glm::vec2 getScreenSize() const { return m_screen_size; }

  /* 获取鼠标位置 */
  glm::vec2 getMousePosition() const { return m_mouse_pos; }

  /* 获取鼠标按键状态 */
  SDL_MouseButtonFlags getMouseButtons() const { return m_mouse_buttons; }

  /* 获取当前场景 */
  Scene *getCurrentScene() const { return m_current_scene; }

  /* 获取资源 */
  AssetStore *getAssetStore() const { return m_asset_store; }

  /* 获取分数 */
  int getScore() const { return m_score; }

  /* 获取最高分 */
  int getHighScore() const { return m_high_score; }

  // setters
 public:
  /* 设置鼠标位置 */
  void setMousePos(const glm::vec2 &pos) { m_mouse_pos = pos; }

  /* 设置鼠标按键状态 */
  void setMouseButtons(SDL_MouseButtonFlags buttons) { m_mouse_buttons = buttons; }

  /* 设置分数 */
  void setScore(int score);

  /* 设置最高分 */
  void setHighScore(int high_score) { m_high_score = high_score; }
};
