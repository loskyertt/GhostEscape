/*
 * @File    :   include\core\AssetStore.h
 * @Time    :   2026/03/16 15:20:36
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include <SDL3/SDL_render.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <string>
#include <unordered_map>

class AssetStore {
 private:
  SDL_Renderer *m_renderer = nullptr;
  MIX_Mixer *m_mixer = nullptr;

  // 统一用容器管理资源
 private:
  std::unordered_map<std::string, SDL_Texture *> m_textures;  // 容器：材质
  std::unordered_map<std::string, MIX_Audio *> m_sounds;      // 容器：音效或音乐
  std::unordered_map<std::string, TTF_Font *> m_fonts;        // container: fonts (key: "path:size")

 public:
  /* 设置 render 和 mixer */
  AssetStore(SDL_Renderer *render, MIX_Mixer *mixer);

 public:
  /* 释放资源 */
  void clean();

  /* 检查声音资源是否存在 */
  bool hasSound(const std::string &file_path);

 public:
  /* 载入图片 */
  void loadImage(const std::string &file_path);

  /**
   * @brief 载入声音资源
   *
   * - @param file_path 文件路径，资源的唯一标识，后续用这个 key 来获取
   * - @param predecode true=预解码（音效），false=流式（背景音乐）
   */
  void loadSound(const std::string &file_path, bool predecode);

  /* 载入字体 */
  void loadFont(const std::string &file_path, const float &font_size);

 public:
  /* 获取图片资源 */
  SDL_Texture *getImage(const std::string &file_path);

  /**
   * @brief 获取声音资源（必须先 loadSound，否则返回 nullptr）
   *
   * - @param file_path 与 loadSound 时传入的 file_path 一致
   * - @return MIX_Audio*
   */
  MIX_Audio *getSound(const std::string &file_path);

  /* 获取字体资源 */
  TTF_Font *getFont(const std::string &file_path, const float &font_size);
};
