/*
@File    :   example\example02.cpp
@Time    :   2026/03/15 15:35:42
@Author  :   loskyertt
@Github  :   https://github.com/loskyertt
@Desc    :   SDL3_mixer 使用示例
*/

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>

int main() {
  // =========================================================
  // 第一步：初始化 SDL 和 SDL_mixer
  // =========================================================

  if (!SDL_Init(SDL_INIT_AUDIO)) {
    SDL_Log("SDL_Init 失败: %s", SDL_GetError());
    return 1;
  }

  // MIX_Init 无参数，自动加载所有可用解码器（OGG/MP3/FLAC 等）
  if (!MIX_Init()) {
    SDL_Log("MIX_Init 失败: %s", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  // =========================================================
  // 第二步：创建 Mixer，绑定到默认音频输出设备
  // =========================================================

  // spec 传 NULL：让 SDL 自动选择最优格式，无需手动填 44100/stereo 等
  MIX_Mixer *mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);
  if (!mixer) {
    SDL_Log("MIX_CreateMixerDevice 失败: %s", SDL_GetError());
    MIX_Quit();
    SDL_Quit();
    return 1;
  }

  // =========================================================
  // 第三步：加载音频文件
  // =========================================================

  // 音效（短音频）：predecode=true，提前解压到内存，播放时无延迟
  MIX_Audio *sfx = MIX_LoadAudio(mixer, "assets/bgm/Spooky music.mp3", true);
  if (!sfx) {
    SDL_Log("加载音效失败: %s", SDL_GetError());
  }

  // 背景音乐（长音频）：predecode=false，流式解码，节省内存
  MIX_Audio *bgm = MIX_LoadAudio(mixer, "assets/bgm/OhMyGhost.ogg", false);
  if (!bgm) {
    SDL_Log("加载 BGM 失败: %s", SDL_GetError());
  }

  // =========================================================
  // 第四步：创建轨道并播放
  // =========================================================

  // 音效轨道（可重复使用，只需换绑的 Audio 即可）
  MIX_Track *sfxTrack = MIX_CreateTrack(mixer);
  MIX_SetTrackAudio(sfxTrack, sfx);
  MIX_PlayTrack(sfxTrack, 0);  // 0 = 使用全部默认参数，播放一次

  // BGM 轨道：无限循环 + 1 秒淡入
  MIX_Track *bgmTrack = MIX_CreateTrack(mixer);
  MIX_SetTrackAudio(bgmTrack, bgm);

  SDL_PropertiesID props = SDL_CreateProperties();
  SDL_SetNumberProperty(props, MIX_PROP_PLAY_LOOPS_NUMBER, -1);                   // 无限循环
  SDL_SetNumberProperty(props, MIX_PROP_PLAY_FADE_IN_MILLISECONDS_NUMBER, 1000);  // 1s 淡入
  MIX_PlayTrack(bgmTrack, props);
  SDL_DestroyProperties(props);  // props 用完即销毁，不影响播放

  // =========================================================
  // 游戏主循环（示意）
  // =========================================================

  SDL_Delay(5000);  // 等待 5 秒

  // =========================================================
  // 第五步：释放资源（顺序很重要：Track → Audio → Mixer → Quit）
  // =========================================================

  // 1. 先销毁轨道（停止播放）
  MIX_DestroyTrack(sfxTrack);
  MIX_DestroyTrack(bgmTrack);

  // 2. 再释放音频数据
  MIX_DestroyAudio(sfx);
  MIX_DestroyAudio(bgm);

  // 3. 销毁 Mixer（关闭设备）
  MIX_DestroyMixer(mixer);

  // 4. 最后退出
  MIX_Quit();
  SDL_Quit();

  return 0;
}
