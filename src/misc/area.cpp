//
// Created by 19254 on 25-3-17.
//
#include <LVGLEx/misc/area.h>

namespace LVGLEx {

void Area::AreaPointerDeleter::operator()(lv_area_t *ptr) const {
  if (ptr) {
    delete ptr;
  }
}

Area::Area() : m_area(new lv_area_t) {};
Area::Area(const lv_area_t &matrix) {
  m_area = AreaPointer::makeQuote(&matrix);
};
Area::Area(const lv_area_t *matrix) {
  m_area = AreaPointer::makeQuote(matrix);
};
Area::Area(const Area &matrix) {
  m_area = AreaPointer::makePrivatePtr(new lv_area_t{0});
  *m_area = *matrix.m_area;
};

Area::~Area() =default;
Area &Area::operator=(const Area &data) {
  m_area = AreaPointer::makePrivatePtr(new lv_area_t{0});
  *m_area = *data.m_area;
  return *this;
};

const lv_area_t *Area::get() const { return m_area.get(); };
lv_area_t *Area::getPtr() const { return m_area.get(); };

Area &Area::set(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
  m_area->x1 = x1;
  m_area->y1 = y1;
  m_area->x2 = x2;
  m_area->y2 = y2;
  return *this;
}
Area &Area::copy(const Area &src) {
  if (m_area.isOwning()) {
    *m_area = *src.m_area;
  } else {
    m_area = AreaPointer::makePrivatePtr(new lv_area_t{0});
    *m_area = *src.m_area;
  }
  return *this;
}
int32_t Area::getWidth() const { return lv_area_get_width(m_area.get()); }
int32_t Area::getHeight() const { return lv_area_get_height(m_area.get()); }
Area &Area::setWidth(int32_t w) {
  lv_area_set_width(m_area.get(), w);
  return *this;
}
Area &Area::setHeight(int32_t h) {
  lv_area_set_height(m_area.get(), h);
  return *this;
}
uint32_t Area::getSize() const { return lv_area_get_size(m_area.get()); }
Area &Area::increase(int32_t w_extra, int32_t h_extra) {
  lv_area_increase(m_area.get(), w_extra, h_extra);
  return *this;
}
Area &Area::move(int32_t x_ofs, int32_t y_ofs) {
  lv_area_move(m_area.get(), x_ofs, y_ofs);
  return *this;
}
Area &Area::align(Area *to_align, lv_align_t align, int32_t ofs_x,
                  int32_t ofs_y) {
  lv_area_align(m_area.get(), to_align->m_area.get(), align, ofs_x, ofs_y);
  return *this;
}

} // namespace LVGLEx