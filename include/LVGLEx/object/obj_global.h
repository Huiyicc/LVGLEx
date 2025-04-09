//
// Created by 19254 on 25-1-12.
//

#ifndef OBJ_GLOBAL_H
#define OBJ_GLOBAL_H

#include "lvgl.h"
#include <functional>


namespace LVGLEx {
class WidgetBase;
typedef std::function<lv_obj_tree_walk_res_t(WidgetBase &, void *)> LvObjTreeWalkCbHandel;

/**
* @brief 寻找坐标下的对象
* @param parent 父对象
* @param x x坐标
* @param y y坐标
* @return 对象指针, 如果找不到则返回NULL
* */
lv_obj_t *obj_find_at_coords(lv_obj_t *parent, lv_coord_t x, lv_coord_t y);

}

#endif //OBJ_GLOBAL_H
