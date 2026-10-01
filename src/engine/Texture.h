/*
 * @File    :   src\engine\Texture.h
 * @Time    :   2026/10/01
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   渲染层纹理描述（由原 components/Sprite.h 迁移至 engine 层，供 Game 渲染接口使用）
 */

#pragma once

#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

#include <string>

struct Texture
{
    SDL_Texture* texture = nullptr;
    SDL_FRect src_rect   = {0, 0, 0, 0};  // 用于裁剪图片形成动画
    float angle          = 0;             // 材质旋转角度
    bool is_flip         = false;         // 材质是否翻转

    Texture() = default;  // 必须添加默认构造函数，因为在 Sprite 中声明了成员：Texture m_texture;
    Texture(const std::string& file_path);
};
