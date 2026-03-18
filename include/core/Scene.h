/*
 * @File    :   include\core\Scene.h
 * @Time    :   2026/03/15 19:04:48
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/ObjectScreen.h"
#include "core/ObjectWorld.h"

#include <glm/fwd.hpp>
#include <glm/glm.hpp>

#include <memory>
#include <vector>

class Scene : public Object {
 protected:
  glm::vec2 m_world_size = glm::vec2(0);       // 世界大小
  glm::vec2 m_camera_position = glm::vec2(0);  // 相机位置

  std::vector<std::unique_ptr<ObjectWorld>> m_children_world;    // 地图上的元素、角色
  std::vector<std::unique_ptr<ObjectScreen>> m_children_screen;  // 固定在屏幕上的元素

 public:
  Scene();

  ~Scene() override;

  /* 初始化 */
  void init() override;

  /* 事件处理 */
  void handleEvents(SDL_Event &event) override;

  /* 更新 */
  void update(const float &delta_time) override;

  /* 渲染 */
  void render() override;

  /* 清理 */
  void clean() override;

  // 坐标转换
 public:
  /* 世界坐标 -> 渲染坐标 */
  glm::vec2 worldToScreen(const glm::vec2 &world_position) { return world_position - m_camera_position; }

  /* 渲染坐标 -> 世界坐标 */
  glm::vec2 screenToWorld(const glm::vec2 &screen_position) { return screen_position + m_camera_position; }

 public:
  // 关键：告诉编译器，我也要用基类的 addChild
  // using Object::addChild;

  /* 添加 ObjectScreen */
  void addObjectScreen(std::unique_ptr<ObjectScreen> child);

  /* 添加 ObjectWorld */
  void addObjectWorld(std::unique_ptr<ObjectWorld> child);

  /* 移除 ObjectScreen */
  void removeObjectScreen(ObjectScreen *child);

  /* 移除 ObjectWorld */
  void removeObjectWorld(ObjectWorld *child);

  // getters
 public:
  /* 获取世界大小 */
  glm::vec2 getWorldSize() { return m_world_size; }

  /* 获取相机坐标 */
  glm::vec2 getCameraPosition() { return m_camera_position; }

  // setters
 public:
  /* 设置世界大小 */
  void setWorldSize(const glm::vec2 &world_size) { m_world_size = world_size; }

  /* 设置相机坐标 */
  void setCameraPosition(const glm::vec2 &camera_position);
};
