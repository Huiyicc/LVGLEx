//
// Created by 19254 on 24-12-16.
//
#include "global_def.h"
#include "lvgl.h"

#include <LVGLEx/core/application.h>
#include <iostream>
#include <thread>

namespace LVGLEx {

void runExec() {
  // 检查是否有多余的窗口
  auto check_display_num = []() {
    return lv_disp_get_next(nullptr) != nullptr;
  };
  while (g_LVGLEx_initd && check_display_num()) {
    uint32_t time_till_next = lv_timer_handler();
    // lv_delay_ms(time_till_next);
    std::this_thread::sleep_for(std::chrono::milliseconds(time_till_next));
  }
}



}