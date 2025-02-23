//
// Created by 19254 on 25-1-12.
//
#include "LVGLEx/obj_global.h"


namespace LVGLEx {

// 判断某个坐标 (x, y) 是否有对象
lv_obj_t *obj_find_at_coords(lv_obj_t *parent, lv_coord_t x, lv_coord_t y) {
  if (parent == nullptr) {
    return nullptr;
  }

  // 遍历所有子对象
  int32_t child_count = lv_obj_get_child_cnt(parent); // 获取子对象的数量
  for (int32_t i = 0; i < child_count; i++) {
    lv_obj_t *child = lv_obj_get_child(parent, i); // 获取第 i 个子对象

    // 获取子对象的坐标范围
    lv_area_t coords;
    lv_obj_get_coords(child, &coords);

    // 检查目标坐标是否在子对象范围内
    if (x >= coords.x1 && x <= coords.x2 && y >= coords.y1 && y <= coords.y2) {
      return child; // 找到对象，返回对象指针
    }

    // 如果子对象有嵌套的子对象，递归检查
    lv_obj_t *nested_child = obj_find_at_coords(child, x, y);
    if (nested_child != nullptr) {
      return nested_child;
    }
  }

  // 没有找到对象
  return nullptr;
}

}
