//
// Created by 19254 on 24-12-16.
//
#include <LVGLEx/window.h>
#include <display/lv_display.h>
#include <iostream>

#ifdef LV_USE_SDL
#include <drivers/sdl/lv_sdl_window.h>
#define WINDOW_CREATE(hor_res, ver_res) lv_sdl_window_create(hor_res, ver_res)
#define WINDOW_SETTITLE(display, title) lv_sdl_window_set_title(display, title)
#else
#error "unrealized"
#endif

namespace LVGLEx {

lv_obj_t *WindowBase::get_screen_active() const {
  return lv_display_get_screen_active(m_display);
};

lv_display_t* WindowBase::get_display() const {
  return m_display;
}

WidgetBase *WindowBase::add_widget(std::unique_ptr<WidgetBase> &&widget) {
  auto [iter, _] = m_widgets.insert(std::move(widget));
  return iter->get();
};

void WindowBase::set_title(const std::string& title) const {
  WINDOW_SETTITLE(m_display, title.c_str());
};

}// namespace LVGLEx
