/*
 * @File    :   src\utils\include\affiliate\Sprite.h
 * @Time    :   2026/03/17 16:20:51
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "engine/ObjectAffiliate.h"
#include "engine/Texture.h"
#include "glm/ext/vector_float2.hpp"

#include <string>

class Sprite : public ObjectAffiliate
{
protected:
    Texture m_texture;
    bool m_is_finished     = false;            // 是否播放完毕
    glm::vec2 m_percentage = glm::vec2(1.0f);  // 动画进度

public:
    Sprite();
    ~Sprite() override;

public:
    /* 渲染 */
    void render() override;

public:
    /**
     * @brief 创建精灵
     *
     * - @param parrent 父对象
     * - @param file_path 精灵文件路径
     * - @param scale 缩放比例
     * - @param anchor 锚点
     * - @return Sprite* 精灵对象
     */
    static Sprite* addSprite(ObjectScreen* parrent,
                             const std::string& file_path,
                             float scale   = 1.0f,
                             Anchor anchor = Anchor::MIDDLE_CENTER);

    // getters
public:
    Texture getTexture()
    {
        return m_texture;
    }

    bool getFlip()
    {
        return m_texture.is_flip;
    }

    float getAngle()
    {
        return m_texture.angle;
    }

    bool getIsFinished()
    {
        return m_is_finished;
    }

    glm::vec2 getPercentage()
    {
        return m_percentage;
    }

    // setters
public:
    virtual void setTexture(const Texture& texture);

    void setFlip(bool is_flip)
    {
        m_texture.is_flip = is_flip;
    }

    void setAngle(float angle)
    {
        m_texture.angle = angle;
    }

    void setIsFinished(bool is_finished)
    {
        m_is_finished = is_finished;
    }

    void setPercentage(glm::vec2 percentage)
    {
        m_percentage = percentage;
    }
};
