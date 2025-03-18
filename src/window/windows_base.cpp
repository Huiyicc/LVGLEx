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

WidgetPointer WindowBase::getScreenActive() const {
  return WidgetPointer::makeQuote(lv_display_get_screen_active(m_display));
};

DisplayPointer WindowBase::getDisplay() const { return DisplayPointer::makeQuote(m_display); }

void WindowBase::setTitle(const std::string &title) const {
  WINDOW_SETTITLE(m_display, title.c_str());
};

} // namespace LVGLEx
