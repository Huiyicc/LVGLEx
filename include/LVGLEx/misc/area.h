//
// Created by 19254 on 25-3-17.
//

#ifndef LVGLEX_MISC_AREA_H
#define LVGLEX_MISC_AREA_H
#include <LVGLEx/obj_pointer.h>
#include <cstdint>
#include <misc/lv_area.h>

namespace LVGLEx {

class Area {
private:
  struct AreaPointerDeleter {
    void operator()(lv_area_t *ptr) const;
  };
  typedef PointerPack<lv_area_t,AreaPointerDeleter> AreaPointer;
  AreaPointer m_area;

public:

  Area();
  Area(const lv_area_t *matrix);
  Area(const lv_area_t &matrix);
  Area(const Area &);
  ~Area();

  Area &operator=(const Area &);

  const lv_area_t *get() const;
  lv_area_t *getPtr() const;

  /**
   * 设置坐标
   * @param x1 左坐标(left)
   * @param y1 顶坐标(top)
   * @param x2 右坐标(right)
   * @param y2 底坐标(bottom)
   */
  Area& set(int32_t x1, int32_t y1, int32_t x2, int32_t y2);

  /**
   * 复制
   * @param src 需要复制的Area
   */
  Area& copy(const Area& src);

  /**
   * 获取宽度
   */
  [[nodiscard]] int32_t getWidth() const;

  /**
   * 获取高度
   */
  [[nodiscard]] int32_t getHeight() const;

  /**
   * 设置宽度
   * @param w 区域的新宽度(当 W == 1 则 x1 == x2)
   */
  Area& setWidth(int32_t w);

  /**
   * 设置高度
   * @param h 区域的新高度(当 H == 1 则 y1 == y2)
   */
  Area& setHeight(int32_t h);

  /**
   * 获取面积 (x * y)
   */
  [[nodiscard]] uint32_t getSize() const;

  /**
   * 增加边框
   * @param w_extra 左右边框宽度
   * @param h_extra 上下边框高度
   */
  Area& increase(int32_t w_extra, int32_t h_extra);

  /**
   * 移动
   * @param x_ofs x坐标偏移量
   * @param y_ofs y坐标偏移量
   */
  Area& move(int32_t x_ofs, int32_t y_ofs);

  /**
   * 对齐
   * @param to_align 需要对齐的Area
   * @param align 对齐方式
   * @param ofs_x x坐标偏移量
   * @param ofs_y y坐标偏移量
   */
  Area& align(Area* to_align, lv_align_t align, int32_t ofs_x,
             int32_t ofs_y);
};

} // namespace LVGLEx

#endif // LVGLEX_MISC_AREA_H
