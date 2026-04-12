/*
 * @File    :   src\core\impl\game\SceneTitle.cpp
 * @Time    :   2026/04/11 19:50:48
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/game/SceneTitle.h"
#include "core/game/SceneMain.h"

#include "screen/HUDText.h"
#include "screen/HUDButton.h"

#include <glm/fwd.hpp>

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>

#include <string>
#include <cmath>

void SceneTitle::init() {
  Scene::init();
  SDL_ShowCursor();
  m_game.playMusic("assets/bgm/Spooky music.mp3");

  // 标题文本
  auto size = glm::vec2(m_game.getScreenSize().x / 2.0f, m_game.getScreenSize().y / 3.0f);
  HUDText::addHUDText(this,
      "幽灵逃生",
      m_game.getScreenSize() / 2.0f - glm::vec2(0.0f, 100.0f),
      size,
      "assets/font/VonwaonBitmap-16px.ttf",
      64.0f);

  // 得分文本
  auto score_text = "最高分：" + std::to_string(m_game.getHighScore());
  HUDText::addHUDText(this,
      score_text,
      m_game.getScreenSize() / 2.0f + glm::vec2(0.0f, 100.0f),
      glm::vec2(200.0f, 50.0f),
      "assets/font/VonwaonBitmap-16px.ttf",
      32.0f);

  // 开始按钮
  m_button_start = HUDButton::addHUDButton(this,
      m_game.getScreenSize() / 2.0f + glm::vec2(-200.0f, 200.0f),
      "assets/UI/A_Start1.png",
      "assets/UI/A_Start2.png",
      "assets/UI/A_Start3.png",
      2.0f);

  // 作者按钮
  m_button_credits = HUDButton::addHUDButton(this,
      m_game.getScreenSize() / 2.0f + glm::vec2(0.0f, 200.0f),
      "assets/UI/A_Credits1.png",
      "assets/UI/A_Credits2.png",
      "assets/UI/A_Credits3.png",
      2.0f);

  // 退出按钮
  m_button_quit = HUDButton::addHUDButton(this,
      m_game.getScreenSize() / 2.0f + glm::vec2(200.0f, 200.0f),
      "assets/UI/A_Quit1.png",
      "assets/UI/A_Quit2.png",
      "assets/UI/A_Quit3.png",
      2.0f);

  // 作者文本
  auto text = m_game.loadText("assets/credits.txt");
  m_text_credits = HUDText::addHUDText(this,
      text,
      m_game.getScreenSize() / 2.0f,
      glm::vec2(500.0f),
      "assets/font/VonwaonBitmap-16px.ttf",
      16.0f);
  m_text_credits->setBgSizeByText();
  m_text_credits->setActive(false);
}

bool SceneTitle::handleEvents(SDL_Event &event) {
  if (m_text_credits && m_text_credits->getActiveState() && event.type == SDL_EVENT_MOUSE_BUTTON_UP) {
    m_text_credits->setActive(false);
    return true;
  }

  return Scene::handleEvents(event);
}

void SceneTitle::update(const float &delta_time) {
  m_color_timer += delta_time;
  updateColor();

  if (m_text_credits && m_text_credits->getActiveState()) {
    return;  // 后续的更新部分不执行
  }

  Scene::update(delta_time);

  checkButtonQuit();
  checkButtonStart();
  checkButtonCredits();
}

void SceneTitle::render() {
  renderBackground();
  Scene::render();
}

void SceneTitle::clean() {
  Scene::clean();
}

void SceneTitle::renderBackground() {
  m_game.drawBoundary(glm::vec2(30.0f), m_game.getScreenSize() - glm::vec2(30.0f), 10.0f, m_boundary_color);
}

void SceneTitle::updateColor() {
  // 注：sinf函数返回值在 [-1, 1] 范围内，需要映射到 [0, 1] 范围
  // 保证频率不同，可实现颜色交替变化的功能
  m_boundary_color.r = 0.5f + 0.5f * sinf(m_color_timer * 0.9f);
  m_boundary_color.g = 0.5f + 0.5f * sinf(m_color_timer * 0.8f);
  m_boundary_color.b = 0.5f + 0.5f * sinf(m_color_timer * 0.7f);
}

void SceneTitle::checkButtonQuit() {
  // TODO: 实现按钮退出检查逻辑
  if (m_button_quit && m_button_quit->getIsTriggered()) {
    m_game.quit();
  }
}

void SceneTitle::checkButtonStart() {
  // TODO: 实现按钮开始检查逻辑
  if (m_button_start && m_button_start->getIsTriggered()) {
    auto scene_main = new SceneMain();
    m_game.safeChangeScene(scene_main);
  }
}

void SceneTitle::checkButtonCredits() {
  // TODO: 实现按钮凭据检查逻辑
  if (m_button_credits && m_button_credits->getIsTriggered()) {
    m_text_credits->setActive(true);
  }
}
