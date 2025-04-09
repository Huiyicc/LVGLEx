//
// Created by 19254 on 24-12-15.
//
#include "lvgl.h"
#include <LVGLEx/LVGLEx.h>
#include  "../../container/window/window_hook/window_hook.h"

namespace LVGLEx {

bool g_LVGLEx_initd = false;
AppConfig g_AppConfig;

void init() {
  lv_init();
  lv_sdl_window_set_event_callback(handel_sdl_window_event);
#ifdef _HOST_WINDOWS_
  g_AppConfig.font = Font::MakeFromFile(R"(C:\Windows\Fonts\msyh.ttc)",14);
#elif
#error "Not supported platform"
#endif
  g_LVGLEx_initd = true;

};

void deInit() {
  g_LVGLEx_initd = false;
  lv_deinit();
}


}// namespace LVGLEx