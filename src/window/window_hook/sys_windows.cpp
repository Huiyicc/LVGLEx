//
// Created by 19254 on 25-1-12.
//

#include "LVGLEx/window.h"
#include "global_def.h"

#ifdef _HOST_WINDOWS_
#include <Windows.h>
#include <SDL_syswm.h>
#include "./window_hook.h"

namespace LVGLEx {

void hook_windows(Window* window) {
  auto dsc = static_cast<lv_sdl_window_t *>(lv_display_get_driver_data(window->get_display()));

  SDL_SysWMinfo wmInfo;
  SDL_VERSION(&wmInfo.version);
  SDL_GetWindowWMInfo(dsc->window, &wmInfo);

  HWND hwnd = wmInfo.info.win.window;

  // ws_pop,这步主要是为了显示任务栏图标
  auto sty = GetWindowLongA(hwnd, GWL_STYLE);
  SetWindowLongA(hwnd, GWL_STYLE, sty | WS_POPUP);

  sty = GetWindowLongA(hwnd, GWL_STYLE);

  sty = sty & ~WS_SIZEBOX;
  SetWindowLongA(hwnd, GWL_STYLE, sty);

  sty = GetWindowLongA(hwnd, GWL_STYLE);
  sty = sty & ~WS_DLGFRAME;
  SetWindowLongA(hwnd, GWL_STYLE, sty);

  sty = GetWindowLongA(hwnd, GWL_STYLE);
  sty = sty & ~WS_BORDER;
  SetWindowLongA(hwnd, GWL_STYLE, sty);


  sty = GetWindowLongA(hwnd, GWL_STYLE);
  sty = sty | WS_SIZEBOX;
  SetWindowLongA(hwnd, GWL_STYLE, sty);



}

}

#else
#error "Not support this platform"
#endif
