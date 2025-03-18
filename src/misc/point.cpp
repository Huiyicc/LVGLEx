//
// Created by 19254 on 25-3-17.
//
#include <LVGLEx/misc/point.h>

namespace LVGLEx {

Point::Point() = default;
Point::Point(const lv_point_t *matrix) { m_point = *matrix; };
Point::Point(const lv_point_t &matrix) { m_point = matrix; };
Point::Point(const Point &matrix) { m_point = matrix.m_point; };
Point::~Point() = default;

const lv_point_t *Point::get() const { return &m_point; };
lv_point_t *Point::getPtr() { return &m_point; };

Point &Point::transform(int32_t angle, int32_t scale_x, int32_t scale_y,
                        const lv_point_t *pivot, bool zoom_first) {
  lv_point_transform(&m_point, angle, scale_x, scale_y, pivot, zoom_first);
  return *this;
}
Point &Point::arrayTransform(size_t count, int32_t angle, int32_t scale_x,
                             int32_t scale_y, const lv_point_t *pivot,
                             bool zoom_first) {
  lv_point_array_transform(&m_point, count, angle, scale_x, scale_y, pivot,
                           zoom_first);
  return *this;
}

Point Point::makeFromPrecise(const PointPrecise &p) {
  return lv_point_from_precise(p.get());
}

PointPrecise Point::toPrecise() const {
  return lv_point_to_precise(&m_point);
}
Point &Point::set(int32_t x, int32_t y) {
  lv_point_set(&m_point, x, y);
  return *this;
}

Point &Point::swap(Point *p) {
  lv_point_swap(&m_point, &p->m_point);
  return *this;
}

PointPrecise::PointPrecise() = default;
PointPrecise::PointPrecise(const lv_point_precise_t *matrix) {
  m_point = *matrix;
};
PointPrecise::PointPrecise(const lv_point_precise_t &matrix) {
  m_point = matrix;
};
PointPrecise::PointPrecise(const PointPrecise &matrix) {
  m_point = matrix.m_point;
};
PointPrecise::~PointPrecise() = default;

const lv_point_precise_t *PointPrecise::get() const { return &m_point; };
lv_point_precise_t *PointPrecise::getPtr() { return &m_point; };

PointPrecise &PointPrecise::set(lv_value_precise_t x, lv_value_precise_t y) {
  lv_point_precise_set(&m_point, x, y);
  return *this;
}
PointPrecise &PointPrecise::swap(PointPrecise *p) {
  lv_point_precise_swap(&m_point, &p->m_point);
  return *this;
}

} // namespace LVGLEx