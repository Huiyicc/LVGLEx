//
// Created by 19254 on 25-1-12.
//
#include "window_hook.h"

#include <LVGLEx/object/obj_global.h>
#include <iostream>
#include <map>

#ifdef LV_USE_SDL
#include <SDL_events.h>

namespace LVGLEx {

// 窗口句柄与对应的SDL窗口id
std::map<void *, uint32_t> window_handel_id_map;

void register_window_id(void *handel, uint32_t id) {
  window_handel_id_map[handel] = id;
}

uint32_t get_window_id(void *handel) { return window_handel_id_map[handel]; }

void WindowBase::initHal() {
  auto disp = m_display;
  // 注册鼠标事件
  lv_indev_t *mouse = lv_sdl_mouse_create();
  lv_indev_set_display(mouse, disp);
  lv_display_set_default(disp);
  // 注册鼠标滚轮事件
  lv_indev_t *mousewheel = lv_sdl_mousewheel_create();
  lv_indev_set_display(mousewheel, disp);
  // 注册键盘事件
  lv_indev_t *kb = lv_sdl_keyboard_create();
  lv_indev_set_display(kb, disp);
}

void handel_sdl_window_event(void *eventPtr) {
  auto event = static_cast<SDL_Event *>(eventPtr);
  auto w = SDL_GetWindowFromID(event->window.windowID);
  if (w == nullptr)
    return;
  auto selfWindowPtr =
      static_cast<Window *>(SDL_GetWindowData(w, "LVGLExWindow"));
  if (selfWindowPtr == nullptr)
    return;
  selfWindowPtr->handelEvent(eventPtr);
}

void WindowBase::handelEvent(void *eventPtr) {

  handelFirstRender(eventPtr);
  // 假定所有的窗口事件都是由handel_sdl_window_event触发
  //
  // handelMouseEvent(event);
};

void WindowBase::handelFirstRender(void *eventPtr) {
  auto event = static_cast<SDL_Event *>(eventPtr);
  if (event->type != SDL_WINDOWEVENT) {
    return;
  }
  auto currSDLWindow = SDL_GetWindowFromID(event->window.windowID);
  if (event->window.type == SDL_WINDOWEVENT_EXPOSED) {
    PrintDebug("WindowBase::handelFirstRender");
  }
  // 后渲染,解决窗口第一次显示渲染的问题
  if (!m_firstRender) {
    if (m_show) {
      SDL_ShowWindow(currSDLWindow);
      m_firstRender = true;
    }
  }
}

void WindowBase::setData(const char *name, void *data) const {
  auto dsc = static_cast<lv_sdl_window_t *>(
      lv_display_get_driver_data(this->getDisplay().get()));
  SDL_SetWindowData(dsc->window, name, data);
};

void WindowBase::handelWindowMoveEvent(void *eventPtr) {
  auto event = static_cast<SDL_Event *>(eventPtr);
  auto checkObj = [](lv_display_t *dispaly, int x, int y) -> bool {
    auto obj = obj_find_at_coords(lv_display_get_screen_active(dispaly), x, y);
    return obj != nullptr;
  };
  auto currSDLWindow = SDL_GetWindowFromID(event->button.windowID);
  switch (event->type) {
    /// -------------------------
  case SDL_MOUSEBUTTONDOWN: {
    // 鼠标被按下
    switch (event->button.button) {
    case SDL_BUTTON_LEFT: {
      // 鼠标左键被按下
      if (!m_status.MousePress) {
        // 获取鼠标位置
        int x = event->button.x;
        int y = event->button.y;
        if (checkObj(m_display, x, y)) {
          // 下属有对象,放弃处理
          m_status.MousePress = false;
          break;
        }

        m_status.MousePress = true;
        m_status.MousePressPos = {x, y};
        SDL_GetGlobalMouseState(&m_status.MousePressGlobalPos.x,
                                &m_status.MousePressGlobalPos.y);
        SDL_GetWindowPosition(currSDLWindow, &m_status.MousePressPosWindow.x,
                              &m_status.MousePressPosWindow.y);
      }
    } break;
    case SDL_BUTTON_RIGHT: {
      // 鼠标右键被按下

    } break;
    }
  } break;
    /// -------------------------
  case SDL_MOUSEBUTTONUP: {
    // 鼠标被释放
    switch (event->button.button) {
    case SDL_BUTTON_LEFT: {
      // 鼠标左键被释放
      if (event->button.button == SDL_BUTTON_LEFT && m_status.MousePress) {
        m_status.MousePress = false;
      }
    } break;
    case SDL_BUTTON_RIGHT: {
      // 鼠标右键被释放

    } break;
    }
  } break;
    /// -------------------------
  case SDL_MOUSEMOTION: {
    // 鼠标移动
    auto checkPress = [](int *x, int *y) -> bool {
      if (SDL_GetGlobalMouseState(x, y) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        return true;
      }
      return false;
    };
    int x, y;
    if (event->button.button == SDL_BUTTON_LEFT && m_status.MousePress &&
        checkPress(&x, &y)) {
      // 鼠标正按下, 移动窗口
      SDL_SetWindowPosition(
          currSDLWindow,
          m_status.MousePressPosWindow.x + x - m_status.MousePressGlobalPos.x,
          m_status.MousePressPosWindow.y + y - m_status.MousePressGlobalPos.y);
    }
  }
    /// -------------------------
  }
}

void WindowBase::handelMouseEvent(void *eventPtr) {
  // handelWindowMoveEvent(eventPtr);
  auto event = static_cast<SDL_Event *>(eventPtr);
  auto checkObj = [](lv_display_t *dispaly, int x, int y) -> bool {
    auto obj = obj_find_at_coords(lv_display_get_screen_active(dispaly), x, y);
    return obj != nullptr;
  };
  auto currSDLWindow = SDL_GetWindowFromID(event->button.windowID);
  switch (event->type) {}
}

} // namespace LVGLEx

#endif