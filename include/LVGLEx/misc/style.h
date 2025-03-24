//
// Created by 19254 on 25-3-18.
//

#ifndef LVGLEX_MISC_STYLE_H
#define LVGLEX_MISC_STYLE_H

#include "misc/lv_style.h"

#include <LVGLEx/obj_pointer.h>

namespace LVGLEx {

class Style {
private:
  struct StylePointerDeleter {
    void operator()(lv_style_t *ptr) const;
  };
  typedef PointerPack<lv_style_t, StylePointerDeleter> StylePointer;
  StylePointer m_style;

public:
  Style();
  Style(const lv_style_t *matrix);
  Style(const lv_style_t &matrix);
  Style(const Style &);
  ~Style();

  Style &operator=(const Style &);

  const lv_style_t *get() const;
  lv_style_t *getPtr();

  /**
   * @brief 重置样式。
   */
  void reset();

  /**
   * @brief 检查样式是否为常量。
   *
   * @return 如果样式为常量则返回 true，否则返回 false。
   */
  bool isConst() const;

  /**
   * @brief 注册样式属性。
   *
   * @param flag 属性标志。
   * @return 返回注册的属性。
   */
  static lv_style_prop_t registerProp(uint8_t flag);

  /**
   * @brief 获取自定义属性的数量。
   *
   * @return 返回自定义属性的数量。
   */
  static lv_style_prop_t getNumCustomProps();

  /**
   * @brief 移除样式属性。
   *
   * @param prop 要移除的属性。
   * @return 如果移除成功则返回 true，否则返回 false。
   */
  bool removeProp(lv_style_prop_t prop) const;

  /**
   * @brief 设置样式属性。
   *
   * @param prop 要设置的属性。
   * @param value 属性值。
   */
  void setProp(lv_style_prop_t prop, lv_style_value_t value) const;

  /**
   * @brief 获取样式属性。
   *
   * @param prop 要获取的属性。
   * @param value 指向属性值的指针，用于存储获取的值。
   * @return 返回获取结果。
   */
  lv_style_res_t getProp(lv_style_prop_t prop, lv_style_value_t *value) const;

  /**
   * @brief 初始化样式过渡描述。
   *
   * @param tr 指向样式过渡描述的指针。
   * @param props 属性数组。
   * @param path_cb 动画路径回调函数。
   * @param time 动画时间。
   * @param delay 动画延迟。
   * @param user_data 用户数据。
   */
  static void transitionDscInit(lv_style_transition_dsc_t *tr,
                                const lv_style_prop_t props[],
                                lv_anim_path_cb_t path_cb, uint32_t time,
                                uint32_t delay, void *user_data);

  /**
   * @brief 获取属性的默认值。
   *
   * @param prop 要获取默认值的属性。
   * @return 返回属性的默认值。
   */
  static lv_style_value_t propGetDefault(lv_style_prop_t prop);

  /**
   * @brief 获取样式属性的值（内联优化）。
   *
   * @param prop 要获取的属性。
   * @param value 指向存储结果的值的指针。
   * @return 属性获取结果，参见 `lv_style_res_t`。
   */
  lv_style_res_t getPropInlined(lv_style_prop_t prop,
                                lv_style_value_t *value) const;

  /**
   * @brief 检查样式是否为空。
   *
   * @return 如果样式为空，返回 true，否则返回 false。
   */
  bool isEmpty() const;

  /**
   * @brief 获取样式属性的分组。
   *
   * @param prop 要查询的属性。
   * @return 属性分组值。
   */
  static uint32_t getPropGroup(lv_style_prop_t prop);

  /**
   * @brief 查询样式属性的标志。
   *
   * @param prop 要查询的属性。
   * @return 属性标志值。
   */
  static uint8_t propLookupFlags(lv_style_prop_t prop);

  /**
   * @brief 设置样式的宽度和高度。
   *
   * @param width 宽度值。
   * @param height 高度值。
   */
  void setSize(int32_t width, int32_t height) const;

  /**
   * @brief 设置样式的全部内边距。
   *
   * @param value 内边距值。
   */
  void setPadAll(int32_t value) const;

  /**
   * @brief 设置样式的水平内边距。
   *
   * @param value 水平内边距值。
   */
  void setPadHor(int32_t value) const;

  /**
   * @brief 设置样式的垂直内边距。
   *
   * @param value 垂直内边距值。
   */
  void setPadVer(int32_t value) const;

  /**
   * @brief 设置样式的间距。
   *
   * @param value 间距值。
   */
  void setPadGap(int32_t value) const;

  /**
   * @brief 设置样式的水平外边距。
   *
   * @param value 水平外边距值。
   */
  void setMarginHor(int32_t value) const;

  /**
   * @brief 设置样式的垂直外边距。
   *
   * @param value 垂直外边距值。
   */
  void setMarginVer(int32_t value) const;

  /**
   * @brief 设置样式的全部外边距。
   *
   * @param value 外边距值。
   */
  void setMarginAll(int32_t value) const;

  /**
   * @brief 设置样式的缩放比例。
   *
   * @param value 缩放比例值。
   */
  void setTransformScale(int32_t value) const;

  /**
   * @brief 检查样式属性是否具有指定标志。
   *
   * @param prop 要检查的属性。
   * @param flag 要检查的标志。
   * @return 如果属性具有指定标志，返回 true，否则返回 false。
   */
  static bool propHasFlag(lv_style_prop_t prop, uint8_t flag);
};

} // namespace LVGLEx

#endif // LVGLEX_MISC_STYLE_H
