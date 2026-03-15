/*
@File    :   example\example01.cpp
@Time    :   2026/03/15 14:08:22
@Author  :   loskyertt
@Github  :   https://github.com/loskyertt
@Desc    :   SDL3 使用示例
*/

#include <glm/glm.hpp>
#include <glm/fwd.hpp>

#include <SDL3/SDL.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>

#include <iostream>

int main(int argc, char *argv[]) {
  std::cout << "Hello, World!" << std::endl;
  // SDL初始化
  if (!SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO)) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "SDL_Init Error: %s", SDL_GetError());
    return 1;
  }
  // 创建窗口
  SDL_Window *window = SDL_CreateWindow("Hello World!", 800, 600, 0);
  // 创建渲染器
  SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

  // SDL3_Image不需要手动初始化

  // 加载图片
  SDL_Texture *texture = IMG_LoadTexture(renderer, "assets/UI/Electric-Icon.png");

  // === 方式一：经典 Surface 路径（兼容 SDL2 思路）===
  // 适合一次性渲染、静态文字（如 HUD 标签），逻辑简单但每次改文字都要重新生成 Texture。
  // SDL_TTF初始化
  if (!TTF_Init()) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "TTF_Init Error: %s", SDL_GetError());
    return 1;
  }
  // 加载字体，ptsize 现在是 float, SDL2 是 int
  TTF_Font *font = TTF_OpenFont("assets/font/VonwaonBitmap-16px.ttf", 24.0f);

  // 创建文本纹理
  SDL_Color color = {255, 255, 255, 255};
  // Blended：抗锯齿最好，透明背景
  SDL_Surface *surface = TTF_RenderText_Solid(font, "Hello, SDL! 中文也可以", 0, color);
  SDL_Texture *textTexture = SDL_CreateTextureFromSurface(renderer, surface);

  glm::vec2 mousePos = glm::vec2(0.0f, 0.0f);

  // 渲染循环
  bool is_running = true;
  while (is_running) {
    // 声明一个事件容器，SDL 会把事件信息填进这个结构体
    SDL_Event event;
    // ✅ while：每帧清空整个事件队列（推荐）
    // ⚠️ if：每帧只处理一个事件
    while (SDL_PollEvent(&event)) {
      // SDL_PollEvent 从事件队列里取出一个事件放入 event
      // 如果队列里还有事件就返回 true，队列空了就返回 false
      // 所以这个 while 会一次性处理掉本帧所有积压的事件
      if (event.type == SDL_EVENT_QUIT) {
        is_running = false;
        break;
      }
    }

    auto state = SDL_GetMouseState(&mousePos.x, &mousePos.y);
    // SDL_Log("Mouse Pos: (%f, %f)", mousePos.x, mousePos.y);
    if (state & SDL_BUTTON_LMASK) {
      SDL_Log("Left Button Down");
    }

    // 清屏
    SDL_RenderClear(renderer);
    // 画一个长方形
    SDL_FRect rect = {100, 100, 200, 200};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);

    // 画图片
    SDL_FRect dstrect = {200, 200, 200, 200};
    SDL_RenderTexture(renderer, texture, NULL, &dstrect);

    // 画文本
    SDL_FRect textRect = {300, 300, static_cast<float>(surface->w), static_cast<float>(surface->h)};
    SDL_RenderTexture(renderer, textTexture, NULL, &textRect);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    // 更新屏幕
    SDL_RenderPresent(renderer);
  }

  // 清理图片资源
  SDL_DestroyTexture(texture);

  // 清理字体资源
  SDL_DestroySurface(surface);
  SDL_DestroyTexture(textTexture);
  TTF_CloseFont(font);
  TTF_Quit();

  // 清理并退出
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
