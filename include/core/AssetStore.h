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
  std::unordered_map<std::string, TTF_Font *> m_fonts;        // 容器：字体

 public:
  /* 设置 render 和 mixer */
  AssetStore(SDL_Renderer *render, MIX_Mixer *mixer);

 public:
  /* 释放资源 */
  void clean();

  // 载入资源
 public:
  /* 载入图片 */
  void loadImage(const std::string &file_path);

  /*
   * 载入声音：
   * - 音效（短音频）：isSound=true，提前解压到内存，播放时无延迟
   * - 背景音乐（长音频）：isSound=false，流式解码，节省内存
   */
  void loadSound(const std::string &file_path, bool isSound);

  /* 载入字体 */
  void loadFont(const std::string &file_path, const float &font_size);

  // getters
 public:
  /* 获取图片资源 */
  SDL_Texture *getImage(const std::string &file_path);

  /* 获取声音资源 */
  MIX_Audio *getSound(const std::string &file_path, bool isSound);

  /* 获取字体资源 */
  TTF_Font *getFont(const std::string &file_path, const float &font_size);
};
