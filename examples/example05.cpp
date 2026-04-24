#include <SDL3/SDL.h>
#include <time.h>
#include <stdio.h>

// 自定义日志回调函数
void MyLogOutput(void *userdata, int category, SDL_LogPriority priority, const char *message) {
  time_t now;
  time(&now);
  char timeStr[20];
  strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(&now));

  // 注意：SDL 默认的 SDL_Log 并不直接传递 __FILE__，
  // 如果需要文件名，通常需要通过宏包装一下（见下文）
  printf("[%s] [Category:%d] [Priority:%d] %s\n", timeStr, category, priority, message);
}

int main(int argc, char *argv[]) {
  // 1. 注册自定义回调
  SDL_SetLogOutputFunction(MyLogOutput, NULL);

  // 2. 设置允许打印的等级
  SDL_SetLogPriorities(SDL_LOG_PRIORITY_VERBOSE);

  // 3. 测试打印
  SDL_Log("这是一条测试日志");

  return 0;
}
