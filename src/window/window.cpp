//
// Created by 19254 on 24-12-15.
//
#include "./window_hook/window_hook.h"
#include <LVGLEx/LVGLEx.h>
#include <Spinlock.h>
#include <atomic>
#include <display/lv_display.h>

#include "./window_hook/window_private_def.h"
#include <functional>
#include <iostream>
#include <lv_conf.h>
#include <misc/lv_event_private.h>
#include <widgets/label/lv_label.h>

#include <map>
#ifdef LV_USE_SDL

#include <SDL2/SDL.h>
#include <drivers/sdl/lv_sdl_private.h>
#include <drivers/sdl/lv_sdl_window.h>
namespace LVGLEx {
lv_display_t *create_window(int width, int height);
}
#if _HOST_WINDOWS_
#include <windows.h>
#endif
#define WINDOW_CREATE(hor_res, ver_res) create_window(hor_res, ver_res)
#define WINDOW_SETTITLE(display, title) lv_sdl_window_set_title(display, title)

#else
#error "unrealized"
#endif

#define CAST_WINDOW(e) static_cast<Window *>(e->user_data)

namespace LVGLEx {

std::map<lv_display_t *, Window *> g_window_map;

Window* Window::getByDisplay(lv_display_t* display) {
  return g_window_map[display];
};

Window::Window() {
  m_display = WINDOW_CREATE(800, 600);
  WINDOW_SETTITLE(m_display, "");
  auto dsc =
      static_cast<lv_sdl_window_t *>(lv_display_get_driver_data(m_display));

  SDL_HideWindow(dsc->window);
  register_event();

  // 注册常量
  SDL_SetWindowData(dsc->window, WINDOW_DATAMAP_NAME_TITLEBAR_HEIGHT,
                    &this->m_titleBarHeight);

  hook_windows(this);
  SDL_SetWindowData(dsc->window, "LVGLExWindow", this);
  g_window_map[m_display] = this;
}

Window::~Window() {
  lv_display_delete(m_display);
  g_window_map.erase(m_display);
}

void Window::register_event() {

  lv_display_add_event_cb(
      m_display, [](lv_event_t *e) { CAST_WINDOW(e)->onDelete(); },
      LV_EVENT_DELETE, this);
  lv_display_add_event_cb(
      m_display, [](lv_event_t *e) { CAST_WINDOW(e)->onLoadStart(); },
      LV_EVENT_SCREEN_LOAD_START, this);
  lv_display_add_event_cb(
      m_display, [](lv_event_t *e) { CAST_WINDOW(e)->onLoadEnd(); },
      LV_EVENT_SCREEN_LOADED, this);
  lv_display_add_event_cb(
      m_display, [](lv_event_t *e) {}, LV_EVENT_CLICKED, this);
  lv_sdl_window_set_event_callback(handel_sdl_window_event);
};

void Window::show() {
  // auto dsc = (lv_sdl_window_t *)lv_display_get_driver_data(m_display);

  // SDL_ShowWindow(dsc->window);
  m_show = true;
}

} // namespace LVGLEx