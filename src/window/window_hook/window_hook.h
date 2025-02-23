//
// Created by 19254 on 25-1-12.
//

#ifndef WINDOW_HOOK_H
#define WINDOW_HOOK_H

#include <LVGLEx/LVGLEx.h>

namespace LVGLEx {
class Window;
void hook_windows(Window* window);

}

#ifdef LV_USE_SDL
#include <SDL_events.h>
namespace LVGLEx {
void register_window_id(void* handel, uint32_t id);
uint32_t get_window_id(void* handel);
void handel_sdl_window_event(void* event);
}
#endif

#endif // WINDOW_HOOK_H
