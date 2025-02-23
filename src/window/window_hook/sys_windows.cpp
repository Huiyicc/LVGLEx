//
// Created by 19254 on 25-1-12.
//

#include "./window_private_def.h"
#include "LVGLEx/window.h"
#include "global_def.h"

#ifdef _HOST_WINDOWS_
#include "./window_hook.h"
#include <SDL_syswm.h>
#include <Windows.h>
#include <Windowsx.h>
// #include <dwmapi.h>
// #pragma comment(lib, "dwmapi.lib")

namespace LVGLEx {

int ProcNCCalcSize(SDL_Window *sdlWind, HWND hWnd, UINT message, WPARAM wParam,
                   LPARAM lParam) {
  int xFrame = 2;   /*左右边框的厚度*/
  int yFrame = 2;   /*下边框的厚度*/
  int nTHight = 25; /*标题栏的高度*/
  NCCALCSIZE_PARAMS *p;
  RECT *rc;
  RECT aRect;
  RECT bRect;
  RECT bcRect;

  if (wParam == TRUE) {
    PrintDebug("proc nc calc size");
    p = (NCCALCSIZE_PARAMS *)lParam; /*矩形是B A AC，目标是改成BC B A*/

    CopyRect(&aRect, &p->rgrc[1]);
    CopyRect(&bRect, &p->rgrc[0]);

    /*指定BC的矩形的位置*/
    bcRect.left = bRect.left + xFrame;
    bcRect.top = bRect.top + nTHight;
    bcRect.right = bRect.right - xFrame;
    bcRect.bottom = bRect.bottom - yFrame;

    /*各个矩形归位*/
    CopyRect(&p->rgrc[0], &bcRect);
    CopyRect(&p->rgrc[1], &bRect);
    CopyRect(&p->rgrc[2], &aRect);
  } else {
    rc = (RECT *)lParam;

    rc->left = rc->left + xFrame;
    rc->top = rc->top + nTHight;
    rc->right = rc->right - xFrame;
    rc->bottom = rc->bottom - yFrame;
  }
  return 0;
};

LRESULT CALLBACK SDLWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  auto wid = get_window_id(hwnd);
  if (wid == 0) {
    return DefWindowProc(hwnd, msg, wParam, lParam);
  }
  auto sdlWindow = SDL_GetWindowFromID(wid);
  auto OriginalWindowProc =
      (WNDPROC)SDL_GetWindowData(sdlWindow, "SDLExOriginalWindowProc");
  if (!OriginalWindowProc) {
    return DefWindowProc(hwnd, msg, wParam, lParam);
  }
  // PrintDebug("old proc:{}",(intptr_t)OriginalWindowProc);
  switch (msg) {
  case WM_NCCALCSIZE: {
    // 隐藏标题栏，扩展客户区到整个窗口
    if (wParam) {
      NCCALCSIZE_PARAMS *pParams = (NCCALCSIZE_PARAMS *)lParam;

      // 将客户区扩展到整个窗口区域
      pParams->rgrc[0].left = pParams->rgrc[1].left;
      pParams->rgrc[0].top = pParams->rgrc[1].top;
      pParams->rgrc[0].right = pParams->rgrc[1].right;
      pParams->rgrc[0].bottom = pParams->rgrc[1].bottom;

      return WVR_VALIDRECTS;
    }
    return 0;
  }
  case WM_NCHITTEST: {
    // 处理鼠标区域检测
    auto titlebarHeight = (int *)SDL_GetWindowData(
        sdlWindow, WINDOW_DATAMAP_NAME_TITLEBAR_HEIGHT);
    // 获取鼠标位置（屏幕坐标）
    POINT pt = {GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};

    // 转换为客户区坐标
    ScreenToClient(hwnd, &pt);
    RECT frameRect = {3, 3, 3, 3};

    // 检查是否在顶部标题栏内
    if (pt.y >= frameRect.top && pt.y < *titlebarHeight) {
      // 返回标题栏区域标识，允许拖动
      return HTCAPTION;
    }
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    const int width = clientRect.right;
    const int height = clientRect.bottom;
    if (pt.x < frameRect.left && pt.y < frameRect.top) {
      // 左上角（左 + 顶）
      return HTTOPLEFT;
    } else if (pt.x >= width - frameRect.right && pt.y < frameRect.top) {
      // 右上角（右 + 顶）
      return HTTOPRIGHT;
    } else if (pt.x < frameRect.left && pt.y >= height - frameRect.bottom) {
      // 左下角（左 + 底）
      return HTBOTTOMLEFT;
    } else if (pt.x >= width - frameRect.right &&
               pt.y >= height - frameRect.bottom) {
      // 右下角（右 + 底）
      return HTBOTTOMRIGHT;
    } else if (pt.y < frameRect.top) {
      // 顶部拖动区域
      return HTTOP;
    } else if (pt.x < frameRect.left) {
      // 左边框
      return HTLEFT;
    } else if (pt.x >= width - frameRect.right) {
      // 右边框
      return HTRIGHT;
    } else if (pt.y >= height - frameRect.bottom) {
      // 底边框
      return HTBOTTOM;
    }

    // 其他区域交由默认处理
    return DefWindowProc(hwnd, msg, wParam, lParam);
  }

  default:
    return OriginalWindowProc(hwnd, msg, wParam, lParam);
  }
  return 0;
}

lv_display_t *create_window(int width, int height) {
  HINSTANCE hInstance = GetModuleHandleW(nullptr);
  WNDCLASSW wc = {0};
  wc.lpfnWndProc = DefWindowProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = L"LVGLEx_WINDOW";
  RegisterClassW(&wc);

  HWND hwnd =
      CreateWindowExW(WS_EX_APPWINDOW | WS_EX_TOOLWINDOW, // 窗口扩展风格
                      wc.lpszClassName,                   // 窗口类名
                      L"",                                // 窗口标题
                      WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX |
                          WS_CLIPCHILDREN | WS_POPUP | WS_SIZEBOX, // 窗口风格
                      0, 0, width, height,                         // 位置和大小
                      nullptr, nullptr, hInstance, nullptr);

  auto resultWin = lv_sdl_window_create_from(width, height, hwnd);
  auto dsc =
      static_cast<lv_sdl_window_t *>(lv_display_get_driver_data(resultWin));
  register_window_id(hwnd, SDL_GetWindowID(dsc->window));

  return resultWin;
}

void hook_windows(Window *window) {
  auto dsc = static_cast<lv_sdl_window_t *>(
      lv_display_get_driver_data(window->get_display()));

  SDL_SysWMinfo wmInfo;
  SDL_VERSION(&wmInfo.version);
  SDL_GetWindowWMInfo(dsc->window, &wmInfo);

  HWND hwnd = wmInfo.info.win.window;
  register_window_id(hwnd, SDL_GetWindowID(dsc->window));

  auto OriginalWindowProc =
      (WNDPROC)SetWindowLongPtrW(hwnd, GWLP_WNDPROC, (LONG_PTR)SDLWndProc);
  // PrintDebug("old:{}",(intptr_t)OriginalWindowProc);
  SDL_SetWindowData(dsc->window, "SDLExOriginalWindowProc", OriginalWindowProc);

  // ws_pop,这步主要是为了显示任务栏图标
  auto sty = GetWindowLongPtrW(hwnd, GWL_STYLE);
  SetWindowLongPtrW(hwnd, GWL_STYLE, sty | WS_POPUP);

  sty = GetWindowLongPtrW(hwnd, GWL_STYLE);

  sty &= ~WS_SIZEBOX;
  sty &= ~WS_DLGFRAME;
  sty &= ~WS_BORDER;
  sty &= ~WS_CAPTION;
  sty = GetWindowLongPtrW(hwnd, GWL_STYLE);
  sty |= WS_SIZEBOX;
  sty |= WS_THICKFRAME;
  SetWindowLongPtrW(hwnd, GWL_STYLE, sty);

  // 修复非客户区边框引起的鼠错位
  SetWindowPos(hwnd, 0, 0, 0, 0, 0, 1 | 2 | 16);
  SetWindowPos(hwnd, 0, 0, 0, 0, 0, 1 | 2 | 32);
}

} // namespace LVGLEx

#else
#error "Not support this platform"
#endif
