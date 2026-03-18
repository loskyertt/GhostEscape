/*
 * @File    :   lib\core\AssetStore.cpp
 * @Time    :   2026/03/16 15:42:57
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/AssetStore.h"

#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>

/* 设置 render 和 mixer */
AssetStore::AssetStore(SDL_Renderer *render, MIX_Mixer *mixer) : m_renderer(render), m_mixer(mixer) {}

/* 释放资源 */
void AssetStore::clean() {
  for (auto &iter : m_textures) {
    SDL_DestroyTexture(iter.second);
  }
  m_textures.clear();

  for (auto &iter : m_sounds) {
    MIX_DestroyAudio(iter.second);
  }
  m_sounds.clear();

  for (auto &iter : m_fonts) {
    TTF_CloseFont(iter.second);
  }
  m_fonts.clear();
}

/* 载入图片 */
void AssetStore::loadImage(const std::string &file_path) {
  SDL_Texture *texture = IMG_LoadTexture(m_renderer, file_path.c_str());
  if (!texture) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load texture: %s", SDL_GetError());
    return;
  }

  m_textures.emplace(file_path, texture);
}

/* 载入声音 */
void AssetStore::loadSound(const std::string &file_path, bool predecode) {
  // 已经加载过了，直接跳过，避免重复加载浪费内存
  if (m_sounds.count(file_path)) {
    SDL_Log("Sound '%s' already loaded, skipping.", file_path.c_str());
    return;
  }

  MIX_Audio *sound = MIX_LoadAudio(m_mixer, file_path.c_str(), predecode);
  if (!sound) {
    SDL_Log("Failed to load sound: %s", SDL_GetError());
    return;
  }

  m_sounds.emplace(file_path, sound);
}

/* 载入字体 */
void AssetStore::loadFont(const std::string &file_path, const float &font_size) {
  TTF_Font *font = TTF_OpenFont(file_path.c_str(), font_size);
  if (!font) {
    SDL_Log("Failed to load font: %s", SDL_GetError());
    return;
  }

  m_fonts.emplace(file_path, font);
}

/* 获取图片资源 */
SDL_Texture *AssetStore::getImage(const std::string &file_path) {
  auto iter = m_textures.find(file_path);

  // 第一次找：如果没找到，就载入容器
  if (iter == m_textures.end()) {
    loadImage(file_path);
    iter = m_textures.find(file_path);
  }

  // 第二次找：如果载入容器后也没找到，表明确实没有该资源
  if (iter == m_textures.end()) {
    SDL_Log("Failed to get image: %s", SDL_GetError());
    return nullptr;
  }

  return iter->second;
}

/* 获取声音资源 */
MIX_Audio *AssetStore::getSound(const std::string &file_path) {
  auto iter = m_sounds.find(file_path);
  if (iter == m_sounds.end()) {
    // 没找到就是真的没有，不尝试自动加载
    // 因为 getSound 不知道文件路径和 predecode 参数
    SDL_Log("Sound '%s' not found. Did you forget to call loadSound?", file_path.c_str());
    return nullptr;
  }

  return iter->second;
}

/* 获取字体资源 */
TTF_Font *AssetStore::getFont(const std::string &file_path, const float &font_size) {
  auto iter = m_fonts.find(file_path);

  // 第一次找：如果没找到，就载入容器
  if (iter == m_fonts.end()) {
    loadFont(file_path, font_size);
    iter = m_fonts.find(file_path);
  }

  // 第二次找：如果载入容器后也没找到，表明确实没有该资源
  if (iter == m_fonts.end()) {
    SDL_Log("Failed to get font: %s", SDL_GetError());
    return nullptr;
  }

  return iter->second;
}
