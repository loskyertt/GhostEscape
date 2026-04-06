/*
 * @File    :   src\utils\include\screen\HUDStates.h
 * @Time    :   2026/04/06 20:44:50
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

#include "core/ObjectScreen.h"
#include "glm/ext/vector_float2.hpp"

class Sprite;
class Entity;

class HUDStates : public ObjectScreen {
 protected:
  Entity *m_target = nullptr;

  // 血条
  Sprite *m_health_bar = nullptr;
  Sprite *m_health_bar_bg = nullptr;
  Sprite *m_health_bar_icon = nullptr;

  // 蓝条
  Sprite *m_mana_bar = nullptr;
  Sprite *m_mana_bar_bg = nullptr;
  Sprite *m_mana_bar_icon = nullptr;

  float m_health_percentage = 1.0f;
  float m_mana_percentage = 1.0f;

 public:
  void init() override;

  void update(const float &delta_time) override;

 public:
  void updateHealthBar();

  void updateManaBar();

 public:
  /**
 * @brief 添加 HUD 状态显示
 *
 * @param parent 父对象
 * @param target 目标实体
 * @param render_position 渲染位置
 * @return HUDStates* HUD 状态显示对象
 */
  static HUDStates *addHUDStates(Object *parent, Entity *target, glm::vec2 render_position);

  // getters
 public:
  Entity *getTarget() const { return m_target; }

  Sprite *getHealthBar() const { return m_health_bar; }

  Sprite *getHealthBarBg() const { return m_health_bar_bg; }

  Sprite *getHealthBarIcon() const { return m_health_bar_icon; }

  Sprite *getManaBar() const { return m_mana_bar; }

  Sprite *getManaBarBg() const { return m_mana_bar_bg; }

  Sprite *getManaBarIcon() const { return m_mana_bar_icon; }

  float getHealthPercentage() const { return m_health_percentage; }

  float getManaPercentage() const { return m_mana_percentage; }

  // setters
 public:
  void setTarget(Entity *target) { m_target = target; }

  void setHealthBar(Sprite *bar) { m_health_bar = bar; }

  void setHealthBarBg(Sprite *bg) { m_health_bar_bg = bg; }

  void setHealthBarIcon(Sprite *icon) { m_health_bar_icon = icon; }

  void setManaBar(Sprite *bar) { m_mana_bar = bar; }

  void setManaBarBg(Sprite *bg) { m_mana_bar_bg = bg; }

  void setManaBarIcon(Sprite *icon) { m_mana_bar_icon = icon; }

  void setHealthPercentage(float percentage) { m_health_percentage = percentage; }

  void setManaPercentage(float percentage) { m_mana_percentage = percentage; }
};
