//
// Created by 19254 on 25-3-18.
//
#include "LVGLEx/misc/style.h"

namespace LVGLEx {

Style::Style() { lv_style_init(&m_style); }
Style::Style(const lv_style_t *style) { m_style = *style; }
Style::Style(const Style &style) { m_style = style.m_style; }
Style::~Style() =default;
const lv_style_t *Style::get() const{
  return &m_style;
}

lv_style_t *Style::getPtr() {
  return &m_style;
}

} // namespace LVGLEx