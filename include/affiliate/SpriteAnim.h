/*
 * @File    :   include\affiliate\SpriteAnim.h
 * @Time    :   2026/03/17 18:50:32
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "affiliate/Sprite.h"

#include <string>

class SpriteAnim : public Sprite {
 private:
  int m_current_frame = 0;        // 当前帧
  int m_total_frames = 0;         // 一张动画包含的总帧数
  int m_fps = 10;                 // 目标动画的帧率（不是整个游戏场景的帧率）
  float m_frame_interval = 0.1f;  // 一帧占的时间，即 1s/10帧=0.1s/帧
  float m_frame_timer = 0.0f;     // 累计计时器：记录"距离上一次切换帧，已经过去了多少时间"

 private:
  bool m_is_loop = true;  // 是否循环播放

 public:
  SpriteAnim();

  ~SpriteAnim() override;

 public:
  /* 更新动画 */
  void update(const float &delta_time) override;

  /* 设置材质 */
  void setTexture(const Texture &texture) override;

 public:
  /* 创建精灵动画 */
  static SpriteAnim *addSpriteAnimToObjects(ObjectScreen *parrent, const std::string &file_path, float scale = 1.0f);

  // getters
 public:
  int getCurrentFrame() { return m_current_frame; }

  int getTotalFrames() { return m_total_frames; }

  int getFPS() { return m_fps; }

  float getFrameTimer() { return m_frame_timer; }

  bool getIsLoop() { return m_is_loop; }

  // setters
 public:
  void setCurrentFrame(int current_frame) { m_current_frame = current_frame; }

  void setTotalFrames(int total_frames) { m_total_frames = total_frames; }

  void setFPS(int fps) { m_fps = fps; }

  void setFrameTimer(float frame_timer) { m_frame_timer = frame_timer; }

  void setIsLoop(bool is_loop) { m_is_loop = is_loop; }
};
