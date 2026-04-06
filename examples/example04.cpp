/*
 * @File    :   example\example04.cpp
 * @Time    :   2026/03/15 15:37:14
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   glm 使用示例
 */

#include <SDL3/SDL_log.h>

#include <glm/glm.hpp>
#include "glm/fwd.hpp"

int main() {
  glm::vec2 a = glm::vec2(1.0f, 2.0f);
  glm::vec2 b = glm::vec2(3.0f, 4.0f);
  auto c = a * b;
  SDL_Log("c = (%f, %f)", c.x, c.y);
}
