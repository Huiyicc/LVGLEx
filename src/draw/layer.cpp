//
// Created by 19254 on 25-3-20.
//
#include <LVGLEx/draw/layer.h>
#include <LVGLEx/misc/area.h>
#include <draw/lv_draw.h>

namespace LVGLEx {

Layer::Layer() noexcept : m_ptr(new lv_layer_t{}) {};
Layer::Layer(LayerPointer &other) noexcept { m_ptr = std::move(other); }
Layer::~Layer() = default;

Layer::Layer(Layer &&other) noexcept { *this = std::move(other); }
Layer &Layer::operator=(Layer &&other) noexcept {
  m_ptr = std::move(other.m_ptr);
  return *this;
}

const lv_layer_t *Layer::get() const { return m_ptr.get(); };
lv_layer_t *Layer::getPtr() { return m_ptr.get(); };

Layer Layer::make(Layer &parent_layer, lv_color_format_t color_format,
                  const Area &area) {
  Layer local;
  local.m_ptr = LayerPointer::makePrivatePtr(
      lv_draw_layer_create(parent_layer.getPtr(), color_format, area.get()));

  return local;
}

void*Layer::goToXY(int32_t x, int32_t y) const {
  return lv_draw_layer_go_to_xy(m_ptr.get(), x, y);
}
void *Layer::allocBuf() const {
  return lv_draw_layer_alloc_buf(m_ptr.get());
};

} // namespace LVGLEx
