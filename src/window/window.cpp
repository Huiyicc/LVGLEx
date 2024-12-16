//
// Created by 19254 on 24-12-15.
//
#include <LVGLEx/LVGLEx.h>
#include <Spinlock.h>
#include <atomic>
#include <display/lv_display.h>
#include <functional>
#include <iostream>
#include <lv_conf.h>
#include <misc/lv_event_private.h>
#include <widgets/label/lv_label.h>

#ifdef LV_USE_SDL
#include <drivers/sdl/lv_sdl_window.h>
#define WINDOW_CREATE(hor_res, ver_res) lv_sdl_window_create(hor_res, ver_res)
#define WINDOW_SETTITLE(display, title) lv_sdl_window_set_title(display, title)
#else
#error "unrealized"
#endif

#define CAST_WINDOW(e) static_cast<Window *>(e->user_data)

namespace LVGLEx {

Window::Window() {
  m_display = WINDOW_CREATE(800, 600);
  WINDOW_SETTITLE(m_display, "MainWindow");

  registerEvent();
}

Window::~Window() {
  lv_display_delete(m_display);
}

void Window::registerEvent() {
  lv_display_add_event_cb(m_display, [](lv_event_t *e) { CAST_WINDOW(e)->OnDelete(); }, LV_EVENT_DELETE, this);
  lv_display_add_event_cb(m_display, [](lv_event_t *e) { CAST_WINDOW(e)->OnLoadStart(); }, LV_EVENT_SCREEN_LOAD_START, this);
  lv_display_add_event_cb(m_display, [](lv_event_t *e) { CAST_WINDOW(e)->OnLoadEnd(); }, LV_EVENT_SCREEN_LOADED, this);
};

void Window::Show() {
  // lv_obj_t * scr = lv_display_get_screen_active(m_display);
  // lv_obj_t * label = lv_label_create(scr);
  // static lv_style_t style;
  // lv_style_init(&style);
  // lv_style_set_text_font(&style, *g_AppConfig.font);
  // lv_obj_add_style(label, &style, 0);
  // lv_label_set_text(label, "Hello, 中文!");
  // lv_obj_set_pos(label, 10, 10);
}

}// namespace LVGLEx