//
// Created by 19254 on 25-3-17.
//

#ifndef LVGLEX_MISC_POINT_H
#define LVGLEX_MISC_POINT_H

#include "misc/lv_area.h"

namespace LVGLEx {

class PointPrecise;

class Point {
private:
  lv_point_t m_point{};

public:
  Point();
  Point(const lv_point_t *matrix);
  Point(const lv_point_t &matrix);
  Point(const Point &matrix);
  ~Point();

  const lv_point_t *get() const;
  lv_point_t *getPtr();

  /**
   * @brief 变换一个点
   *
   * 该函数根据给定的角度和缩放因子对指定的点进行变换。
   *
   * @param angle 以0.1度为单位的角度（例如，123表示12.3°）
   * @param scale_x 水平缩放因子，256表示100%
   * @param scale_y 垂直缩放因子，256表示100%
   * @param pivot 指向变换中心点的指针
   * @param zoom_first 如果为true，则先进行缩放，再进行旋转；否则，先旋转再缩放
   *
   */
  Point &transform(int32_t angle, int32_t scale_x, int32_t scale_y,
                   const lv_point_t *pivot, bool zoom_first);

  /**
   * @brief 转换一个点数组
   *
   * 该函数对给定的点数组进行缩放和旋转变换。
   *
   * @param count 数组中点的数量
   * @param angle 旋转角度，单位为0.1度（例如，123表示12.3°）
   * @param scale_x 水平缩放因子，256表示100%
   * @param scale_y 垂直缩放因子，256表示100%
   * @param pivot 指向变换中心点的指针
   * @param zoom_first 如果为true，则先进行缩放，再进行旋转；否则，反之
   */
  Point &arrayTransform(size_t count, int32_t angle, int32_t scale_x,
                        int32_t scale_y, const lv_point_t *pivot,
                        bool zoom_first);
  static Point makeFromPrecise(const PointPrecise &p);
  [[nodiscard]] PointPrecise toPrecise() const;

  Point &set(int32_t x, int32_t y);

  /**
   * @brief 交换两个点的位置
   *
   * 该函数将两个点的位置进行交换。
   *
   * @param p 指向另一个点的指针
   */
  Point &swap(Point *p);
};

class PointPrecise {
private:
  lv_point_precise_t m_point{};

public:
  PointPrecise();
  PointPrecise(const lv_point_precise_t *matrix);
  PointPrecise(const lv_point_precise_t &matrix);
  PointPrecise(const PointPrecise &matrix);
  ~PointPrecise();

  const lv_point_precise_t *get() const;
  lv_point_precise_t *getPtr();

  PointPrecise &set(lv_value_precise_t x, lv_value_precise_t y);
  PointPrecise &swap(PointPrecise *p);
};

} // namespace LVGLEx

#endif // LVGLEX_MISC_POINT_H
