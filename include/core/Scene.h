/*
 * @File    :   include\core\Scene.h
 * @Time    :   2026/03/15 19:04:48
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "Object.h"

#include <glm/glm.hpp>

#include <vector>

class Scene : public Object {
 protected:
  glm::vec2 m_camera_position = glm::vec2(0);  // 相机位置
  std::vector<Object *> m_objects;             // 场景中的物体

 public:
  Scene() = default;

  ~Scene() override {}

  void init() override {}  // 初始化

  void handleEvents(SDL_Event &event) override {}  // 事件处理

  void update(const float &deltaTime) override {}  // 更新

  void render() override {}  // 渲染

  void clean() override {}  // 清理
};
