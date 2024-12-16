//
// Created by 19254 on 24-12-16.
//
#include <LVGLEx/window.h>
#include <display/lv_display.h>
#include <iostream>

namespace LVGLEx {

lv_obj_t *WindowBase::GetScreenActive() const {
  return lv_display_get_screen_active(m_display);
};

WidgetBase *WindowBase::AddWidget(std::unique_ptr<WidgetBase> &&widget) {
  auto [iter, _] = m_widgets.insert(std::move(widget));
  return iter->get();
};

}// namespace LVGLEx
