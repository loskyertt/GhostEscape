/*
 * @File    :   lib\SceneMain.cpp
 * @Time    :   2026/03/15 19:21:35
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "SceneMain.h"
#include <SDL3/SDL_log.h>
#include "Enemy.h"
#include "Player.h"
#include "world/Effect.h"

#include <glm/fwd.hpp>

SceneMain::SceneMain() = default;
SceneMain::~SceneMain() = default;

/* 初始化 */
void SceneMain::init() {
  Scene::init();
  m_world_size = m_game.getScreenSize() * 3.0f;
  m_camera_position = m_world_size / 2.0f - m_game.getScreenSize() / 2.0f;

// 玩家初始化
#ifndef NDEBUG
  SDL_Log(">>> SceneMain::init() called: Player init");
#endif
  m_player = new Player();  // Player -> Entity -> ObjectWorld
  m_player->init();
  m_player->setPosition(m_world_size / 2.0f);
  addChild(m_player);
#ifndef NDEBUG
  SDL_Log("玩家已经添加到了容器中......");
  SDL_Log("");
#endif

// 敌人初始化
#ifndef NDEBUG
  SDL_Log(">>> SceneMain::init() calld: Enemy init");
#endif
  auto enemy = new Enemy();  // Enemy -> Entity -> ObjectWorld
  enemy->init();
  enemy->setTargetPlayer(m_player);
  enemy->setPosition(m_world_size / 2.0f + glm::vec2(200.0f));
  // addChild(enemy);

  // 敌人生成特效初始化
  auto effect =
      Effect::addEffect(this, "assets/effect/184_3.png", m_world_size / 2.0f + glm::vec2(200.0f), 2.0f, enemy);
#ifndef NDEBUG
  SDL_Log("敌人生成特效已经添加到了容器中......");
  SDL_Log("");
#endif
}

/* 事件处理 */
void SceneMain::handleEvents(SDL_Event &event) {
  Scene::handleEvents(event);
}

/* 更新 */
void SceneMain::update(const float &delta_time) {
  Scene::update(delta_time);
  // m_camera_position += glm::vec2(20.0f, 20.0f) * delta_time;
}

/* 渲染 */
void SceneMain::render() {
  renderBackground();
  Scene::render();
}

/* 清理 */
void SceneMain::clean() {
  Scene::clean();
}

/* 绘制背景 */
void SceneMain::renderBackground() {
  auto start = -m_camera_position;
  auto end = m_world_size - m_camera_position;
  m_game.drawGrid(start, end, 80.0f, {0.5f, 0.5f, 0.5f, 0.1f});
  m_game.drawBoundary(start, end, 5.0f, {1.0f, 1.0f, 1.0f, 1.0f});
}
