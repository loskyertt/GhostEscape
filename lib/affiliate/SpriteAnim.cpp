/*
 * @File    :   lib\Sprite\SpriteAnim.cpp
 * @Time    :   2026/03/17 18:53:13
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include <SDL3/SDL_log.h>
#include <affiliate/SpriteAnim.h>
#include <utility>
#include "glm/fwd.hpp"

SpriteAnim::SpriteAnim() = default;

SpriteAnim::~SpriteAnim() = default;

/* 更新动画 */
void SpriteAnim::update(const float &delta_time) {
  if (m_is_finished) {
    return;
  }

  m_frame_timer += delta_time;
  if (m_frame_timer >= m_frame_interval) {
    m_frame_timer -= m_frame_interval;
    m_current_frame++;
    if (!m_is_loop && m_current_frame >= m_total_frames) {
      m_current_frame = m_total_frames - 1;  // 停在最后一帧
      m_is_finished = true;
    } else {
      m_current_frame = m_current_frame % m_total_frames;
    }
  }

  // 计算材质的 src_rect 的 x 坐标，即从精灵图片的哪处开始裁剪
  m_texture.src_rect.x = m_texture.src_rect.w * static_cast<float>(m_current_frame);
}

/* 设置材质 */
void SpriteAnim::setTexture(const Texture &texture) {
  m_texture = texture;

  // 计算总帧数
  m_total_frames = static_cast<int>(texture.src_rect.w / texture.src_rect.h);
  m_texture.src_rect.w = texture.src_rect.h;
  m_size = glm::vec2(m_texture.src_rect.w, m_texture.src_rect.h);  // 设置图片每一帧的宽和高
}

/* 创建精灵动画 */
SpriteAnim *SpriteAnim::addSpriteAnim(ObjectScreen *parrent, const std::string &file_path, float scale, Anchor anchor) {
  auto sprite_anim = std::make_unique<SpriteAnim>();
  sprite_anim->init();
  sprite_anim->setTexture(Texture(file_path));
  sprite_anim->setScale(scale);
  sprite_anim->setParent(parrent);

  SpriteAnim *raw = sprite_anim.get();  // 1.先保存裸指针
  if (parrent) {
    // SDL_Log("=== addSpriteAnim 的分界线 ===");
    parrent->addChild(std::move(sprite_anim));  // 2.再转移所有权
    // SDL_Log("=== addSpriteAnim 的分界线 ===");
  }
  return raw;  // 3.返回裸指针（观察者）
}
