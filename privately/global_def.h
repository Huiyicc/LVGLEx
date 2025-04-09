//
// Created by 19254 on 24-12-16.
//

#ifndef LVGLEX_GLOBAL_DEF_H
#define LVGLEX_GLOBAL_DEF_H
#include <atomic>
#include "LVGLEx/misc/logs.h"
#include <font/lv_font.h>

// LV_FONT_DECLARE(glyph_bitmap);
extern LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[];

namespace LVGLEx {
class Spinlock;

extern bool g_LVGLEx_initd;
extern Spinlock g_LVGLEx_event_locker;

}

#ifdef LV_USE_SDL

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

typedef struct {
  SDL_Window * window;
  SDL_Renderer * renderer;
#if LV_USE_DRAW_SDL == 0
  SDL_Texture * texture;
  uint8_t * fb1;
  uint8_t * fb2;
  uint8_t * fb_act;
  uint8_t * buf1;
  uint8_t * buf2;
  uint8_t * rotated_buf;
  size_t rotated_buf_size;
#endif
  float zoom;
  uint8_t ignore_size_chg;
} lv_sdl_window_t;

#endif


#endif //LVGLEX_GLOBAL_DEF_H
