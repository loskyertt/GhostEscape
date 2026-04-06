/*
 * @File    :   example\example03.cpp
 * @Time    :   2026/03/15 14:08:22
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   SDL3_ttf 使用示例
 */

#include <SDL3/SDL.h>
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

  // === 方式二：TTF_Text 对象路径（SDL3 新增，推荐）===
  // SDL3_ttf 引入了 TTF_TextEngine + TTF_Text 体系，文字内容可以动态修改而无需重建 Texture，内部自动管理 glyph atlas，性能更好
  // SDL_TTF初始化
  if (!TTF_Init()) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "TTF_Init Error: %s", SDL_GetError());
    return 1;
  }
  TTF_Font *font = TTF_OpenFont("assets/font/VonwaonBitmap-16px.ttf", 24);

  TTF_TextEngine *engine = TTF_CreateRendererTextEngine(renderer);
  TTF_Text *text = TTF_CreateText(engine, font, "SDL3 新的文本渲染方式", 0);

  // 渲染循环
  while (true) {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        break;
      }
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
    TTF_SetTextColor(text, 255, 255, 50, 255);
    TTF_DrawRendererText(text, 20.f, 20.f);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // 黑色背景

    // 更新屏幕
    SDL_RenderPresent(renderer);
  }

  // 清理图片资源
  SDL_DestroyTexture(texture);

  // 清理字体资源
  TTF_DestroyText(text);
  TTF_DestroyRendererTextEngine(engine);
  TTF_CloseFont(font);
  TTF_Quit();

  // 清理并退出
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
