/*
 * @File    :   include\core\Defs.h
 * @Time    :   2026/03/20 17:04:04
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#pragma once

// 对象类型
enum class ObjectType {
  NONE,
  OBJECT_SCREEN,
  OBJECT_WORLD,
};

// 锚点
enum class Anchor {
  NONE,
  TOP_LEFT,
  TOP_CENTER,
  TOP_RIGHT,
  MIDDLE_LEFT,
  MIDDLE_CENTER,
  MIDDLE_RIGHT,
  BOTTOM_LEFT,
  BOTTOM_CENTER,
  BOTTOM_RIGHT
};
