/*
 * @File    :   lib\core\ObjectWorld.cpp
 * @Time    :   2026/03/15 22:41:58
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/ObjectWorld.h"
#include "core/game/SceneMain.h"
#include "core/Defs.h"

void ObjectWorld::init() {
  m_type = ObjectType::OBJECT_WORLD;
}

/* 同步更新物体的坐标 */
void ObjectWorld::update(const float &delta_time) {
  ObjectScreen::update(delta_time);
  // 根据当前的世界坐标同步更新渲染坐标
  m_render_postion = Game::getInstance().getCurrentScene()->worldToScreen(m_position);
}

/* 设置物体的世界坐标（同时更新物体的屏幕坐标） */
void ObjectWorld::setPosition(const glm::vec2 &position) {
  m_position = position;
  m_render_postion = Game::getInstance().getCurrentScene()->worldToScreen(position);
}

/* 设置物体的屏幕（渲染）位置（同时更新物体的世界坐标） */
void ObjectWorld::setRenderPosition(const glm::vec2 &render_position) {
  m_render_postion = render_position;
  m_position = Game::getInstance().getCurrentScene()->screenToWorld(render_position);
}
