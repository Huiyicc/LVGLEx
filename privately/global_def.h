//
// Created by 19254 on 24-12-16.
//

#ifndef LVGLEX_GLOBAL_DEF_H
#define LVGLEX_GLOBAL_DEF_H
#include <atomic>
#include <font/lv_font.h>

// LV_FONT_DECLARE(glyph_bitmap);
extern LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[];

namespace LVGLEx {
class Spinlock;

extern bool g_LVGLEx_initd;
extern Spinlock g_LVGLEx_event_locker;

}

#endif //LVGLEX_GLOBAL_DEF_H
