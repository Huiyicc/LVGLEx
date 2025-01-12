//
// Created by 19254 on 25-1-12.
//
#include "window_hook.h"

#include <iostream>

#ifdef LV_USE_SDL
#include <SDL_events.h>

namespace LVGLEx {

void handel_sdl_event(void* eventPtr) {
  auto event = static_cast<SDL_Event*>(eventPtr);
  std::cout<< "SDL event type: " << event->type << std::endl;
}

}

#endif