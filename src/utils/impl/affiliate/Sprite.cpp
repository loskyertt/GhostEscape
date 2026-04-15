/*
 * @File    :   lib\Sprite\Sprite.cpp
 * @Time    :   2026/03/17 16:22:18
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "affiliate/Sprite.h"
#include "core/AssetStore.h"
#include "core/Game.h"

#include <glm/fwd.hpp>

#include <SDL3/SDL_render.h>

Texture::Texture(const std::string &file_path) {
  AssetStore *asset_store = Game::getInstance().getAssetStore();

  texture = asset_store->getImage(file_path);
  // 获取的是整个图片的宽度和高度
  SDL_GetTextureSize(texture, &src_rect.w, &src_rect.h);
}

Sprite::Sprite() = default;

Sprite::~Sprite() = default;

/* 渲染 */
void Sprite::render() {
  if (!m_texture.texture || !m_parent || m_is_finished) {
    return;
  }

  auto pos = m_parent->getRenderPosition() + m_offset;
  Game::getInstance().renderTexture(m_texture, pos, m_size, m_percentage);
}

Sprite *Sprite::addSprite(ObjectScreen *parrent, const std::string &file_path, float scale, Anchor anchor) {
  auto sprite = new Sprite();
  sprite->init();
  sprite->setAnchor(anchor);
  sprite->setTexture(Texture(file_path));
  sprite->setScale(scale);
  sprite->setParent(parrent);

  if (parrent) {
    parrent->addChild(sprite);
  }

  return sprite;
}

void Sprite::setTexture(const Texture &texture) {
  m_texture = texture;
  m_size = glm::vec2(texture.src_rect.w, texture.src_rect.h);
}
