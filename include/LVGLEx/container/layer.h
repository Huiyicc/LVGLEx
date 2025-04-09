//
// Created by 19254 on 25-3-20.
//

#ifndef LVGLEX_DRAW_LAYER_H
#define LVGLEX_DRAW_LAYER_H

#include <LVGLEx/object/obj_pointer.h>

namespace LVGLEx {
class Area;

class Layer {
private:
  LayerPointer m_ptr;

  Layer() noexcept;

public:
  // Layer(const lv_layer_t *matrix);
  // Layer(const lv_layer_t &matrix);
  // Layer(const Layer &matrix);
  virtual ~Layer();
  Layer(Layer &&other) noexcept;
  explicit Layer(LayerPointer &other) noexcept;
  Layer &operator=(Layer &&other) noexcept;

  const lv_layer_t *get() const;
  lv_layer_t *getPtr();

  static Layer make(Layer &parent_layer, lv_color_format_t color_format,
                    const Area &area);

  /**
   * @brief 移动到图层上的指定像素坐标
   *
   * 此函数将光标移动到指定图层的X和Y坐标处。
   *
   * @param x 目标X坐标
   * @param y 目标Y坐标
   * @return 返回指向给定X和Y坐标的缓冲区偏移量
   *
   */
  void *goToXY(int32_t x, int32_t y) const;

  /**
 * @brief 为图层分配缓冲区
 *
 * 该函数尝试为指定的图层分配一个缓冲区。
 *
 * @return 返回指向分配的对齐缓冲区的指针，如果分配失败则返回 NULL
 *
 * @exception 如果内存分配失败，将返回 NULL。
 *
 */
  void *allocBuf() const;
};

} // namespace LVGLEx

#endif // LVGLEX_DRAW_LAYER_H
