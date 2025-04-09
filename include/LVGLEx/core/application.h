//
// Created by 19254 on 24-12-15.
//

#ifndef LVGLEX_APPLICATION_H
#define LVGLEX_APPLICATION_H

#include "lvgl.h"
#include <memory>

namespace LVGLEx {

class Font;

struct AppConfig {
  std::shared_ptr<Font> font = nullptr;
};
extern AppConfig g_AppConfig;

void init();
void deInit();
void runExec();

}// namespace LVGLEx

#endif//LVGLEX_APPLICATION_H
