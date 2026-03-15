/*
 * @File    :   src\main.cpp
 * @Time    :   2026/03/15 17:04:17
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "core/Game.h"

int main() {
  Game &game = Game::getInstance();
  game.init("GhostEscape", 1280, 720);
  game.run();
}
