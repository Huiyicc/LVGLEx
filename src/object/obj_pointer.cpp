//
// Created by 19254 on 25-2-23.
//
#include "LVGLEx/object/obj_pointer.h"

#include <../../third_party/lvgl/src/core/lv_obj.h>
#include <../../third_party/lvgl/src/core/lv_obj_tree.h>
#include <../../third_party/lvgl/src/misc/lv_types.h>

namespace LVGLEx {

void WidgetPointerDeleter(lv_obj_t *ptr) {
  if (ptr && lv_obj_is_valid(ptr)) {
    lv_obj_delete(ptr);
  }
}

} // namespace LVGLEx