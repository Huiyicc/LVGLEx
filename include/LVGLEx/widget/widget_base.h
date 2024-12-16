//
// Created by 19254 on 24-12-16.
//

#ifndef LVGLEX_WIDGET_BASE_H
#define LVGLEX_WIDGET_BASE_H

#include "misc/lv_types.h"
#include "misc/lv_area.h"
#include <memory>
#include <set>

namespace LVGLEx {

class WindowBase;

class WidgetBase {
protected:
  lv_obj_t *m_obj = nullptr;
  WindowBase *m_parent = nullptr;
  std::set<std::unique_ptr<WidgetBase>> m_children;

public:
  virtual ~WidgetBase();

  [[nodiscard]] WindowBase *GetParent() const;
  WidgetBase *AddWidget(std::unique_ptr<WidgetBase> &&widget);

  /**
   * @brief 设置对象的位置。
   *
   * 该函数使用 LVGL 库的 lv_obj_set_pos 函数来设置对象的位置。
   * 它提供了类型安全的检查，以确保模板参数 T 是 WidgetBase 的派生类。
   *
   * @tparam T 类型参数，必须是 WidgetBase 的派生类。
   * @param x 对象的新 x 坐标。
   * @param y 对象的新 y 坐标。
   * @return 返回指向当前对象的指针，类型为 T*。
   *
   * @exception 如果 T 不是 WidgetBase 的派生类，将会触发编译时断言(static_assert)。
   */
  template<class T = WidgetBase>
  T *SetPos(const int32_t x, const int32_t y) {
    static_assert(std::is_base_of_v<WidgetBase, T>, "T must be derived from WidgetBase");
    lv_obj_set_pos(m_obj, x, y);
    return static_cast<T *>(this);
  }

  /**
 * @brief 设置对象的 x 坐标。
 *
 * 该函数使用 LVGL 库的 lv_obj_set_x 函数来设置对象的 x 坐标。
 * 它提供了类型安全的检查，以确保模板参数 T 是 WidgetBase 的派生类。
 *
 * @tparam T 类型参数，必须是 WidgetBase 的派生类。
 * @param x 对象的新 x 坐标。
 * @return 返回指向当前对象的指针，类型为 T*。
 *
 * @exception 如果 T 不是 WidgetBase 的派生类，将会触发编译时断言(static_assert)。
 */
  template<class T = WidgetBase>
  T *SetX(const int32_t x) {
    static_assert(std::is_base_of_v<WidgetBase, T>, "T must be derived from WidgetBase");
    lv_obj_set_x(m_obj, x);
    return static_cast<T *>(this);
  }

  /**
 * @brief 设置对象的 y 坐标。
 *
 * 该函数使用 LVGL 库的 lv_obj_set_y 函数来设置对象的 y 坐标。
 * 它提供了类型安全的检查，以确保模板参数 T 是 WidgetBase 的派生类。
 *
 * @tparam T 类型参数，必须是 WidgetBase 的派生类。
 * @param y 对象的新 y 坐标。
 * @return 返回指向当前对象的指针，类型为 T*。
 *
 * @exception 如果 T 不是 WidgetBase 的派生类，将会触发编译时断言(static_assert)。
 */
  template<class T = WidgetBase>
  T *SetY(const int32_t y) {
    static_assert(std::is_base_of_v<WidgetBase, T>, "T must be derived from WidgetBase");
    lv_obj_set_y(m_obj, y);
    return static_cast<T *>(this);
  }

  /**
   * @brief 设置对象的宽度和高度。
   *
   * 该函数使用 LVGL 库的 lv_obj_set_size 函数来调整对象的大小。
   * 它提供了类型安全的检查，以确保模板参数 T 是 WidgetBase 的派生类。
   *
   * @tparam T 类型参数，必须是 WidgetBase 的派生类。
   * @param w 对象的新宽度。
   * @param h 对象的新高度。
   * @return 返回指向当前对象的指针，类型为 T*。
   *
   * @exception 如果 T 不是 WidgetBase 的派生类，将会触发编译时断言(static_assert)。
   */
  template<class T = WidgetBase>
  T *SetSize(const int32_t w, const int32_t h) {
    static_assert(std::is_base_of_v<WidgetBase, T>, "T must be derived from WidgetBase");
    lv_obj_set_size(m_obj, w, h);
    return static_cast<T *>(this);
  }

  /**
   * @brief 将对象移动到前景。
   *
   * 该函数将对象移动到其父级的最上层，表现得就像是作为最后一个子对象创建的。
   * 这意味着它可以覆盖任何兄弟对象。
   *
   * @tparam T 类型参数，必须是 WidgetBase 的派生类。
   * @return 返回指向当前对象的指针，类型为 T*。
   *
   * @exception 如果 T 不是 WidgetBase 的派生类，将会触发编译时断言(static_assert)。
   */
  template<class T = WidgetBase>
  T * MoveForeground() {
    static_assert(std::is_base_of_v<WidgetBase, T>, "T must be derived from WidgetBase");
    lv_obj_move_foreground(m_obj);
    return static_cast<T *>(this);
  };

  template<class T = WidgetBase>
  T * Align(const lv_align_t align,const int32_t x_ofs,const int32_t y_ofs) {
    static_assert(std::is_base_of_v<WidgetBase, T>, "T must be derived from WidgetBase");
    lv_obj_align(m_obj, align, x_ofs,y_ofs);
    return static_cast<T *>(this);
  };

  template<class T = WidgetBase>
  T * MoveToIndex(const int32_t index) {
    static_assert(std::is_base_of_v<WidgetBase, T>, "T must be derived from WidgetBase");
    lv_obj_move_to_index(m_obj, index);
    return static_cast<T *>(this);
  };



};

}// namespace LVGLEx


#endif//LVGLEX_WIDGET_BASE_H
