/*
 * @File    :   lib\SceneMain.cpp
 * @Time    :   2026/03/15 19:21:35
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/Defs.h"
#include "core/game/SceneMain.h"
#include "core/game/SceneTitle.h"
#include "core/game/Player.h"
#include "core/game/Spawner.h"

#include "raw/BackgroundStar.h"
#include "raw/Timer.h"
#include "world/Spell.h"
#include "screen/UIMouse.h"
#include "screen/HUDStates.h"
#include "screen/HUDText.h"
#include "screen/HUDButton.h"

#include <glm/fwd.hpp>

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_mouse.h>

#include <fstream>
#include <ios>

void SceneMain::init() {
  Scene::init();

  SDL_HideCursor();

  Game::getInstance().playMusic("assets/bgm/OhMyGhost.ogg");

  m_world_size = Game::getInstance().getScreenSize() * 3.0f;
  m_camera_position = m_world_size / 2.0f - Game::getInstance().getScreenSize() / 2.0f;

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

  BackgroundStar::addBackgroundStar(this, 2000, 0.2f, 0.5f, 0.7f);

  m_end_timer = Timer::addTimer(this);

  m_spawner = new Spawner();
  m_spawner->init();
  m_spawner->setTargetPlayer(m_player);
  addChild(m_spawner);

  m_button_pause = HUDButton::addHUDButton(this,
      Game::getInstance().getScreenSize() - glm::vec2(230.0f, 30.0f),
      "assets/UI/A_Pause1.png",
      "assets/UI/A_Pause2.png",
      "assets/UI/A_Pause3.png");
  m_button_restart = HUDButton::addHUDButton(this,
      Game::getInstance().getScreenSize() - glm::vec2(140.0f, 30.0f),
      "assets/UI/A_Restart1.png",
      "assets/UI/A_Restart2.png",
      "assets/UI/A_Restart3.png");
  m_button_back = HUDButton::addHUDButton(this,
      Game::getInstance().getScreenSize() - glm::vec2(50.0f, 30.0f),
      "assets/UI/A_Back1.png",
      "assets/UI/A_Back2.png",
      "assets/UI/A_Back3.png");

  m_hud_states = HUDStates::addHUDStates(this, m_player, glm::vec2(30.0f));
  m_text_score = HUDText::addHUDText(this,
      "Score: 0",
      glm::vec2(Game::getInstance().getScreenSize().x - 120.0f, 30.0f),
      glm::vec2(200.0f, 50.0f));

  m_ui_mouse = UIMouse::addUIMouse(this, "assets/UI/29.png", "assets/UI/30.png", 1.0f, Anchor::MIDDLE_CENTER);

  // // 敌人初始化
  // #ifndef NDEBUG
  //   SDL_Log(">>> SceneMain::init() calld: Enemy init");
  // #endif
  //   auto enemy = new Enemy();  // Enemy -> Entity -> ObjectWorld
  //   enemy->init();
  //   enemy->setTargetPlayer(m_player);
  //   enemy->setPosition(m_world_size / 2.0f + glm::vec2(200.0f));
  //   // addChild(enemy);

  //   // 敌人生成特效初始化
  //   auto effect =
  //       Effect::addEffect(this, "assets/effect/184_3.png", m_world_size / 2.0f + glm::vec2(200.0f), 2.0f, enemy);
  // #ifndef NDEBUG
  //   SDL_Log("敌人生成特效已经添加到了容器中......");
  //   SDL_Log("");
  // #endif
}

bool SceneMain::handleEvents(SDL_Event &event) {
  return Scene::handleEvents(event);
}

void SceneMain::update(const float &delta_time) {
  checkSlowDown(const_cast<float &>(delta_time));

  Scene::update(delta_time);
  updateScore();
  // m_camera_position += glm::vec2(20.0f, 20.0f) * delta_time;

  checkButtonPause();
  checkButtonRestart();
  checkButtonBack();

  if (m_player && !m_player->getActiveState()) {
    m_end_timer->start();
    saveData("data/score.dat");
  }
  checkEndTimer();
}

void SceneMain::render() {
  renderBackground();
  Scene::render();
}

void SceneMain::clean() {
  Scene::clean();
}

void SceneMain::saveData(const std::string &file_path) {
  auto score = Game::getInstance().getHighScore();
  std::ofstream file(file_path, std::ios::binary);  // 以二进制形式保存
  if (file.is_open()) {
    file.write(reinterpret_cast<const char *>(&score), sizeof(score));
    file.close();
  }
}

void SceneMain::renderBackground() {
  auto start = -m_camera_position;
  auto end = m_world_size - m_camera_position;
  Game::getInstance().drawGrid(start, end, 80.0f, {0.5f, 0.5f, 0.5f, 0.1f});
  Game::getInstance().drawBoundary(start, end, 5.0f, {1.0f, 1.0f, 1.0f, 1.0f});
}

void SceneMain::updateScore() {
  if (m_text_score) {
    m_text_score->setText("Score: " + std::to_string(Game::getInstance().getScore()));
  }
}

void SceneMain::checkButtonPause() {
  // TODO: 实现按钮暂停检查逻辑
  if (m_button_pause && m_button_pause->getIsTriggered()) {
    // TODO: 暂停游戏
    if (m_is_pause) {
      resume();
    } else {
      pause();
    }
  }
}

void SceneMain::checkButtonRestart() {
  // TODO: 实现按钮重新开始检查逻辑
  if (m_button_restart && m_button_restart->getIsTriggered()) {
    // TODO: 重新开始游戏
    Game::getInstance().setScore(0);
    auto new_scene = new SceneMain();
    Game::getInstance().safeChangeScene(new_scene);  // 或者当前场景先 clean 再 init
  }
}

void SceneMain::checkButtonBack() {
  // TODO: 实现按钮返回检查逻辑
  if (m_button_back && m_button_back->getIsTriggered()) {
    // TODO: 返回主菜单
    saveData("data/score.dat");
    Game::getInstance().setScore(0);
    auto scene_title = new SceneTitle();
    Game::getInstance().safeChangeScene(scene_title);
  }
}

void SceneMain::checkEndTimer() {
  if (m_end_timer && !m_end_timer->timeOut()) {
    return;
  }
  // TODO: 游戏结束
  pause();
  m_button_restart->setRenderPosition(Game::getInstance().getScreenSize() / 2.0f - glm::vec2(200.0f, 0));
  m_button_restart->setScale(4.0f);
  m_button_back->setRenderPosition(Game::getInstance().getScreenSize() / 2.0f + glm::vec2(200.0f, 0));
  m_button_back->setScale(4.0f);
  m_button_pause->setActive(false);
  m_end_timer->stop();
}

void SceneMain::checkSlowDown(float &delta_time) {
  if (Game::getInstance().getMouseButtons() & SDL_BUTTON_RMASK) {
    delta_time *= 0.4f;
  }
}
