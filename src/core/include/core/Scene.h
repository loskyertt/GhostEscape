/*
 * @File    :   include\core\Scene.h
 * @Time    :   2026/03/15 19:04:48
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */
#pragma once

#include "ObjectScreen.h"
#include "ObjectWorld.h"

#include <glm/fwd.hpp>
#include <glm/glm.hpp>

#include <vector>

class Scene : public Object {
 protected:
  glm::vec2 m_world_size = glm::vec2(0);       // 世界大小
  glm::vec2 m_camera_position = glm::vec2(0);  // 相机位置

  std::vector<ObjectScreen *> m_children_screen;  // 固定在屏幕上的元素（比如按钮）
  std::vector<ObjectWorld *> m_children_world;    // 地图上的元素、实体（玩家、敌人）等

  bool m_is_pause = false;  // 是否暂停

 public:
  Scene();

  ~Scene() override;

  /* 事件处理 */
  bool handleEvents(SDL_Event &event) override;

  /* 更新 */
  void update(const float &delta_time) override;

  /* 渲染 */
  void render() override;

  /* 清理 */
  void clean() override;

  /* 添加 Object */
  void addChild(Object *child) override;

  /* 移除 Object */
  void removeChild(Object *child) override;

  /* 世界坐标 -> 渲染坐标 */
  glm::vec2 worldToScreen(const glm::vec2 &world_position) { return world_position - m_camera_position; }

  /* 渲染坐标 -> 世界坐标 */
  glm::vec2 screenToWorld(const glm::vec2 &screen_position) { return screen_position + m_camera_position; }

  void pause();
  void resume();

  // getters
 public:
  /* 获取世界大小 */
  glm::vec2 getWorldSize() const { return m_world_size; }

  /* 获取相机坐标 */
  glm::vec2 getCameraPosition() const { return m_camera_position; }

  /* 获取场景容器 */
  std::vector<ObjectScreen *> &getChildrenScreen() { return m_children_screen; }

  /* 获取世界容器 */
  std::vector<ObjectWorld *> &getChildrenWorld() { return m_children_world; }

  // setters
 public:
  /* 设置世界大小 */
  void setWorldSize(const glm::vec2 &world_size) { m_world_size = world_size; }

  /* 设置相机坐标 */
  void setCameraPosition(const glm::vec2 &camera_position);
};
