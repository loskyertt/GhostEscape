/*
 * @File    :   src\utils\impl\affiliate\AffiliateBar.cpp
 * @Time    :   2026/04/06 19:03:30
 * @Author  :   loskyertt
 * @Github  :   https://github.com/loskyertt
 * @Desc    :   .....
 */

#include "affiliate/AffiliateBar.h"

void AffiliateBar::render() {
  auto pos = m_parent->getRenderPosition() + m_offset;
  if (m_percentage > 0.7f) {
    m_game.renderHorizontalBar(pos, m_size, m_percentage, m_color_high);
  } else if (m_percentage > 0.3f) {
    m_game.renderHorizontalBar(pos, m_size, m_percentage, m_color_mid);
  } else {
    m_game.renderHorizontalBar(pos, m_size, m_percentage, m_color_low);
  }
}

AffiliateBar *AffiliateBar::addAffiliateBar(ObjectScreen *parent, glm::vec2 size, Anchor anchor) {
  auto bar = new AffiliateBar();
  bar->init();
  bar->setAnchor(anchor);
  bar->setSize(size);
  if (parent) {
    bar->setParent(parent);
    parent->addChild(bar);
  }
  return bar;
}
