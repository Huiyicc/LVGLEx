//
// Created by 19254 on 24-12-16.
//

#ifndef LVGLEX_WIDGET_BASE_H
#define LVGLEX_WIDGET_BASE_H

#include "../misc/matrix.h"
#include "../misc/point.h"
#include "../obj_pointer.h"
#include "./widget_event_base.h"
#include <LVGLEx/misc/area.h>
#include <LVGLEx/misc/style.h>
#include <lvgl.h>
#include <memory>
#include <optional>
#include <set>

namespace LVGLEx {

class WindowBase;

/*
void func_name_end(int32_t size) const;
void func_name_end(lv_cover_res_t res) const;
void delete() const;
void clean() const;
lv_refr_now(lv_display_t* disp) -> void
lv_refr_init(void) -> void
lv_refr_deinit(void)->void
lv_inv_area(lv_display_t* disp, const lv_area_t* area_p) -> void
lv_refr_set_disp_refreshing(lv_display_t* disp) -> void
lv_display_refr_timer(lv_timer_t* timer) -> void
void lv_obj_delete_anim_completed_cb(lv_anim_t *a) const;
* */

#define WIDGET_OBJ_CREATE_H(TYPE)                                              \
  static TYPE create(WidgetBase *parent);                                      \
  static TYPE create(WindowBase *parent);
#define WIDGET_OBJ_CREATE_CPP(TYPE, OBJCREATE_FUNC)                            \
  TYPE TYPE::create(WindowBase *parent) {                                      \
    TYPE r;                                                                    \
    auto scr = parent->getScreenActive();                                      \
    r.m_obj = WidgetPointer::makeQuote(OBJCREATE_FUNC(scr.get()));             \
    r.init();                                                                  \
    return r;                                                                  \
  }                                                                            \
  TYPE TYPE::create(WidgetBase *parent) {                                      \
    TYPE r;                                                                    \
    auto scr = parent->getScreenActive();                                      \
    r.m_obj = WidgetPointer::makeQuote(OBJCREATE_FUNC(scr.get()));             \
    r.init();                                                                  \
    return r;                                                                  \
  };

class WidgetBase : public WidgetEventBase {
protected:
  WidgetPointer m_obj;
  // lv_obj_t *m_obj = nullptr;
  // WindowBase *m_parent = nullptr;
  // std::set<std::unique_ptr<WidgetBase>> m_children;

  virtual void init() final;

public:
  WidgetBase();
  ~WidgetBase() override;

  lv_obj_t *getObj() const;

  static WidgetBase makeFromPtr(lv_obj_t *ptr);

  [[nodiscard]] std::optional<WidgetBase> getParent() const;
  [[nodiscard]] WindowBase *getWindow() const;
  [[nodiscard]] WidgetPointer getScreenActive() const;
  virtual WidgetPointer release() final;

  /**
   * @brief 以相对坐标的方式设置对象的相对位置
   * @param x 新x坐标
   * @param y 新y坐标
   * */
  void setPos(int32_t x, int32_t y) const;

  /**
   * @brief 以相对坐标的方式设置对象的x坐标
   * @param x 新x坐标
   * */
  void setX(int32_t x) const;

  /**
   * @brief 以相对坐标的方式设置对象的y坐标
   * @param y 新y坐标
   * */
  void setY(int32_t y) const;

  /**
   * @brief 以相对坐标的方式设置对象的尺寸
   * @param w 新宽度
   * @param h 新高度
   * */
  void setSize(int32_t w, int32_t h) const;

  /**
   * @brief 以相对坐标的方式设置对象的宽度
   * @param w 新宽度
   * */
  void setWidth(int32_t w) const;

  /**
   * @brief 以相对坐标的方式设置对象的高度
   * @param h 新高度
   * */
  void setHeight(int32_t h) const;

  /**
   * @brief 设置对象的内容宽度
   * 此函数设置对象的内容宽度，宽度会减去左右的内边距和边框宽度。
   *
   * @param w 不包含内边距的宽度
   * */
  void setContentWidth(int32_t w) const;

  /**
   * @brief 设置对象的内容高度
   * 此函数设置对象的内容高度，高度会减去上下的边框高度。
   *
   * @param h 不包含上下边距的高度
   * */
  void setContentHeight(int32_t h) const;

  /**
   * @brief 设置对象的布局
   * @param layout 指向要设置的布局描述符的指针
   * */
  void setLayout(uint32_t layout) const;

  /**
   * @brief 标记对象以进行布局更新
   *
   * 此函数将指定对象标记为需要更新其子对象的布局.
   * (或者说将对象所在矩阵标记为脏矩阵)
   */
  void markLayoutAsDirty() const;

  /**
   * @brief 更新对象的布局
   */
  void updateLayout() const;

  /**
   * @brief 设置对象的对齐方式
   * @param align 对齐方式, 参见`LV_ALIGN_OUT_`
   * */
  void setAlign(lv_align_t align) const;

  /**
   * @brief 设置对象的对齐方式,并以相对坐标的方式设置新坐标
   *
   * 等价于: setAlign(align);
   * setPos(x_ofs,y_ofs);
   *
   * @param align 对齐方式, 参见`LV_ALIGN_OUT_`
   * @param x_ofs x坐标偏移
   * @param y_ofs y坐标偏移
   * */
  void align(lv_align_t align, int32_t x_ofs, int32_t y_ofs) const;

  /**
   * @brief 将对象与基准对象对齐
   * */
  void alignTo(const WidgetPointer &base, lv_align_t align, int32_t x_ofs,
               int32_t y_ofs) const;

  /**
   * @brief 将对象与其父对象的中心对齐
   * */
  void center() const;

  /**
   * @brief 设置变换矩阵
   * @param matrix 指向要设置的变换矩阵的指针
   * @note 需要启用`LV_DRAW_TRANSFORM_USE_MATRIX`
   * */
  void setTransform(const Matrix &matrix) const;

  /**
   * @brief 重置变换矩阵为单位矩阵
   *
   * 此函数将指定对象的变换矩阵重置为单位矩阵。
   *
   * @note 需要启用 `LV_DRAW_TRANSFORM_USE_MATRIX`。
   */
  void resetTransform() const;

  /**
   * @brief 获取对象的坐标
   * */
  [[nodiscard]] Area getCoords() const;

  /**
   * @brief 获取对象的内容坐标
   * @return 该区域在不导致父对象溢出的情况下仍然适合父对象（使父对象可滚动）
   * @note 对象的位置仅在下次重绘时重新计算。要强制重新计算坐标，请调用
   * `lv_obj_update_layout(obj)`。
   * */
  [[nodiscard]] Area getContentCoords() const;

  /**
   * @brief 刷新位置
   * */
  void refrPos() const;

  /**
   * @brief 移动到新坐标
   * @param x 新x坐标
   * @param y 新y坐标
   * */
  void moveTo(int32_t x, int32_t y) const;

  /**
   * @brief 移动所有子对象。
   *
   * 根据给定的 x 和 y 偏移量移动所有子对象。
   *
   * @param x_diff x 方向的偏移量，单位为像素。
   * @param y_diff y 方向的偏移量，单位为像素。
   * @param ignore_floating 如果为 true，则忽略浮动对象的移动。
   */
  void moveChildrenBy(int32_t x_diff, int32_t y_diff,
                      bool ignore_floating) const;

  /**
   * @brief 使用对象的角度和缩放样式属性转换一个点。
   *
   * @param flags 参见 `lv_obj_point_transform_flag_t`
   * @return 转换后的点。
   */
  Point transformPoint(lv_obj_point_transform_flag_t flags) const;

  /**
   * @brief 使用对象的角度和缩放样式属性转换一个点数组。
   *
   * @param points 指向要转换的点数组的指针，转换结果将写回到此处。
   * @param count 要转换的点的数量。
   * @param flags 参见 `lv_obj_point_transform_flag_t`
   */
  void transformPointArray(std::vector<Point> &points,
                           lv_obj_point_transform_flag_t flags) const;
  /**
   * @brief 获取转换后的区域。
   *
   * @param flags 参见 `lv_obj_point_transform_flag_t`
   * @return 转换后的区域。
   */
  Area getTransformedArea(lv_obj_point_transform_flag_t flags) const;

  /**
   * @brief 使指定区域无效，需要重绘。
   *
   * @param area 指向要使无效的区域。
   */
  void invalidateArea(const Area &area) const;

  /**
   * @brief 使对象无效，需要重绘。
   */
  void invalidate() const;

  /**
   * @brief 设置扩展点击区域的大小。
   *
   * @param size 扩展点击区域的大小。
   */
  void setExtClickArea(int32_t size) const;

  /**
   * @brief 获取点击区域。
   *
   * @return 指向用于存储点击的区域。
   */
  [[nodiscard]] Area getClickArea() const;

  /**
   * @brief 将对象移动到前景。
   */
  void moveForeground() const;

  /**
   * @brief 添加标志。
   *
   * @param f 要添加的标志。
   */
  void addFlag(lv_obj_flag_t f) const;

  /**
   * @brief 移除标志。
   *
   * @param f 要移除的标志。
   */
  void removeFlag(lv_obj_flag_t f) const;

  /**
   * @brief 更新标志。
   *
   * @param f 要更新的标志。
   * @param v 标志的新值。
   */
  void updateFlag(lv_obj_flag_t f, bool v) const;

  /**
   * @brief 添加状态。
   *
   * @param state 要添加的状态。
   */
  void addState(lv_state_t state) const;

  /**
   * @brief 移除状态。
   *
   * @param state 要移除的状态。
   * 例如: `LV_STATE_xx`
   */
  void removeState(lv_state_t state) const;

  /**
   * @brief 设置状态。
   *
   * @param state 要设置的状态。
   * @param v 状态的新值。
   * 例如: `LV_STATE_xx`
   */
  void setState(lv_state_t state, bool v) const;

  /**
   * @brief 设置用户数据。
   *
   * @param user_data 指向用户数据的指针。
   */
  void setUserData(void *user_data) const;

  /**
   * @brief 如果尚未分配，则为对象分配特殊数据。
   */
  void allocateSpecAttr() const;

  void classInitObj() const;

  /**
   * @brief 从对象的样式初始化矩形绘制描述符
   *
   * 该函数根据对象当前状态的样式初始化一个矩形绘制描述符。
   *
   * @param part 对象的部分，例如
   * `LV_PART_MAIN`、`LV_PART_SCROLLBAR`、`LV_PART_KNOB` 等
   * @param draw_dsc 要初始化的描述符。如果某个 `..._opa` 字段被设置为
   * `LV_OPA_TRANSP`，则相关属性将不会被初始化。 应该使用
   * `lv_draw_rect_dsc_init(draw_dsc)` 进行初始化。
   *
   * @note 仅会设置相关字段。例如，如果 `border width ==
   * 0`，则其他边框属性将不会被评估。
   */
  void initDrawRectDsc(lv_part_t part, lv_draw_rect_dsc_t *draw_dsc) const;

  /**
   * @brief 初始化绘制标签的描述符。
   *
   * @param part 部件类型。
   * @param draw_dsc 指向绘制标签描述符的指针。
   */
  void initDrawLabelDsc(lv_part_t part, lv_draw_label_dsc_t *draw_dsc) const;

  /**
   * @brief 初始化绘制图像的描述符。
   *
   * @param part 部件类型。
   * @param draw_dsc 指向绘制描述符的指针。
   */
  void initDrawImageDsc(lv_part_t part, lv_draw_image_dsc_t *draw_dsc) const;

  /**
   * @brief 初始化绘制线条的描述符。
   *
   * @param part 部件类型。
   * @param draw_dsc 指向绘制描述符的指针。
   */
  void initDrawLineDsc(lv_part_t part, lv_draw_line_dsc_t *draw_dsc) const;

  /**
   * @brief 初始化绘制弧形的描述符。
   *
   * @param part 部件类型。
   * @param draw_dsc 指向绘制描述符的指针。
   */
  void initDrawArcDsc(lv_part_t part, lv_draw_arc_dsc_t *draw_dsc) const;

  /**
   * @brief 刷新对象的扩展绘制大小
   *
   * 发送 'LV_EVENT_REFR_EXT_DRAW_SIZE'
   * 事件，并调用对象的祖先事件处理程序以刷新扩展绘制大小的值。 结果将保存在
   * `obj` 中。
   */
  void refreshExtDrawSize() const;

  /**
   * @brief 设置滚动条模式。
   *
   * @param mode 滚动条模式。
   * LV_SCROLL_MODE_ON/OFF/AUTO/ACTIVE
   */
  void setScrollbarMode(lv_scrollbar_mode_t mode) const;

  /**
   * @brief 设置滚动方向。
   *
   * @param dir 滚动方向。
   */
  void setScrollDir(lv_dir_t dir) const;

  /**
   * @brief 设置水平滚动对齐方式。
   *
   * @param align 水平滚动对齐方式。
   */
  void setScrollSnapX(lv_scroll_snap_t align) const;

  /**
   * @brief 设置垂直滚动对齐方式。
   *
   * @param align 垂直滚动对齐方式。
   */
  void setScrollSnapY(lv_scroll_snap_t align) const;

  /**
   * @brief 获取可滚动对象的滚动结束坐标。
   *
   * 如果正在进行滚动动画，则返回滚动结束时的 X 和 Y 坐标。
   * 如果没有滚动动画，则返回当前的 X 或 Y 滚动位置。
   *
   * @param end 指向 `lv_point_t` 对象的指针，用于存储结果。
   */
  void getScrollEnd(lv_point_t *end) const;

  /**
   * @brief 按指定的偏移量滚动。
   *
   * @param dx 水平滚动的偏移量。
   * @param dy 垂直滚动的偏移量。
   * @param anim_en 是否启用动画。
   */
  void scrollBy(int32_t dx, int32_t dy, lv_anim_enable_t anim_en) const;

  /**
   * @brief 按指定的偏移量在边界内滚动。
   *
   * @param dx 水平滚动的偏移量。
   * @param dy 垂直滚动的偏移量。
   * @param anim_en 是否启用动画。
   */
  void scrollByBounded(int32_t dx, int32_t dy, lv_anim_enable_t anim_en) const;

  /**
   * @brief 滚动到指定位置。
   *
   * @param x 水平位置。
   * @param y 垂直位置。
   * @param anim_en 是否启用动画。
   */
  void scrollTo(int32_t x, int32_t y, lv_anim_enable_t anim_en) const;

  /**
   * @brief 滚动到指定水平位置。
   *
   * @param x 水平位置。
   * @param anim_en 是否启用动画。
   */
  void scrollToX(int32_t x, lv_anim_enable_t anim_en) const;

  /**
   * @brief 滚动到指定垂直位置。
   *
   * @param y 垂直位置。
   * @param anim_en 是否启用动画。
   */
  void scrollToY(int32_t y, lv_anim_enable_t anim_en) const;

  /**
   * @brief 滚动到视图内。
   *
   * @param anim_en 是否启用动画。
   */
  void scrollToView(lv_anim_enable_t anim_en) const;

  /**
   * @brief 递归滚动到视图内。
   *
   * @param anim_en 是否启用动画。
   */
  void scrollToViewRecursive(lv_anim_enable_t anim_en) const;

  /**
   * @brief 更新滚动对齐。
   *
   * @param anim_en 是否启用动画。
   */
  void updateSnap(lv_anim_enable_t anim_en) const;

  /**
   * @brief 获取滚动条区域。
   *
   * @param hor 指向存储水平滚动条区域的指针。
   * @param ver 指向存储垂直滚动条区域的指针。
   */
  void getScrollbarArea(Area &hor, Area &ver) const;

  /**
   * @brief 使滚动条无效。
   */
  void scrollbarInvalidate() const;

  /**
   * @brief 重新调整滚动。
   *
   * @param anim_en 是否启用动画。
   */
  void readjustScroll(lv_anim_enable_t anim_en) const;

  /**
   * @brief 添加样式到对象。
   *
   * @param style 指向要添加的样式的指针。
   * @param selector 样式选择器。
   */
  void addStyle(const Style &style, lv_style_selector_t selector) const;

  /**
   * @brief 从对象中移除样式。
   *
   * @param style 指向要移除的样式的指针。
   * @param selector 样式选择器。
   */
  void removeStyle(const Style &style, lv_style_selector_t selector) const;

  /**
   * @brief 移除对象的所有样式。
   */
  void removeStyleAll() const;

  /**
   * @brief 报告样式变化。
   *
   * @param style 指向发生变化的样式的指针。
   */
  static void reportStyleChange(Style &style);

  /**
   * @brief 刷新对象的样式。
   *
   * @param part 部分选择器。
   * @param prop 样式属性。
   */
  void refreshStyle(lv_part_t part, lv_style_prop_t prop) const;

  /**
   * @brief 启用样式刷新。
   */
  void enableStyleRefresh() const;

  /**
   * @brief 设置本地样式属性。
   *
   * @param prop 样式属性。
   * @param value 样式值。
   * @param selector 样式选择器。
   */
  void setLocalStyleProp(lv_style_prop_t prop, lv_style_value_t value,
                         lv_style_selector_t selector) const;

  /**
   * @brief 使对象淡入。
   *
   * @param time 淡入时间（毫秒）。
   * @param delay 延迟时间（毫秒）。
   */
  void fadeIn(uint32_t time, uint32_t delay) const;

  /**
   * @brief 使对象淡出。
   *
   * @param time 淡出时间（毫秒）。
   * @param delay 延迟时间（毫秒）。
   */
  void fadeOut(uint32_t time, uint32_t delay) const;

  /**
   * @brief 设置对象的所有内边距。
   *
   * @param value 内边距值。
   * @param selector 样式选择器。
   */
  void setStylePadAll(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置对象的水平内边距。
   *
   * @param value 内边距值。
   * @param selector 样式选择器。
   */
  void setStylePadHor(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置对象的垂直内边距。
   *
   * @param value 内边距值。
   * @param selector 样式选择器。
   */
  void setStylePadVer(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置对象的所有外边距。
   *
   * @param value 外边距值。
   * @param selector 样式选择器。
   */
  void setStyleMarginAll(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置对象的水平外边距。
   *
   * @param value 外边距值。
   * @param selector 样式选择器。
   */
  void setStyleMarginHor(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置对象的垂直外边距。
   *
   * @param value 外边距值。
   * @param selector 样式选择器。
   */
  void setStyleMarginVer(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置对象的间距。
   *
   * @param value 间距值。
   * @param selector 样式选择器。
   */
  void setStylePadGap(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置对象的宽度和高度。
   *
   * @param width 宽度值。
   * @param height 高度值。
   * @param selector 样式选择器。
   */
  void setStyleSize(int32_t width, int32_t height,
                    lv_style_selector_t selector) const;

  /**
   * @brief 设置对象的缩放比例。
   *
   * @param value 缩放值。
   * @param selector 样式选择器。
   */
  void setStyleTransformScale(int32_t value,
                              lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的宽度。
   *
   * @param value 要设置的宽度值。
   * @param selector 样式选择器。
   */
  void setStyleWidth(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的最小宽度。
   *
   * @param value 要设置的最小宽度值。
   * @param selector 样式选择器。
   */
  void setStyleMinWidth(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的最大宽度。
   *
   * @param value 要设置的最大宽度值。
   * @param selector 样式选择器。
   */
  void setStyleMaxWidth(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的高度。
   *
   * @param value 要设置的高度值。
   * @param selector 样式选择器。
   */
  void setStyleHeight(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的最小高度。
   *
   * @param value 要设置的最小高度值。
   * @param selector 样式选择器。
   */
  void setStyleMinHeight(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的最大高度。
   *
   * @param value 要设置的最大高度值。
   * @param selector 样式选择器。
   */
  void setStyleMaxHeight(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的长度。
   *
   * @param value 要设置的长度值。
   * @param selector 样式选择器。
   */
  void setStyleLength(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的X坐标。
   *
   * @param value 要设置的X坐标值。
   * @param selector 样式选择器。
   */
  void setStyleX(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的Y坐标。
   *
   * @param value 要设置的Y坐标值。
   * @param selector 样式选择器。
   */
  void setStyleY(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的对齐方式。
   *
   * @param value 要设置的对齐方式。
   * @param selector 样式选择器。
   */
  void setStyleAlign(lv_align_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的转换宽度。
   *
   * @param value 要设置的转换宽度值。
   * @param selector 样式选择器。
   */
  void setStyleTransformWidth(int32_t value,
                              lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的转换高度。
   *
   * @param value 要设置的转换高度值。
   * @param selector 样式选择器。
   */
  void setStyleTransformHeight(int32_t value,
                               lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的X轴平移量。
   *
   * @param value 要设置的X轴平移量。
   * @param selector 样式选择器。
   */
  void setStyleTranslateX(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的Y轴平移量。
   *
   * @param value 要设置的Y轴平移量。
   * @param selector 样式选择器。
   */
  void setStyleTranslateY(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的径向平移量。
   *
   * @param value 要设置的径向平移量。
   * @param selector 样式选择器。
   */
  void setStyleTranslateRadial(int32_t value,
                               lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的X轴缩放比例。
   *
   * @param value 要设置的X轴缩放比例。
   * @param selector 样式选择器。
   */
  void setStyleTransformScaleX(int32_t value,
                               lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的Y轴缩放比例。
   *
   * @param value 要设置的Y轴缩放比例。
   * @param selector 样式选择器。
   */
  void setStyleTransformScaleY(int32_t value,
                               lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的旋转角度。
   *
   * @param value 要设置的旋转角度。
   * @param selector 样式选择器。
   */
  void setStyleTransformRotation(int32_t value,
                                 lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的旋转轴的X坐标。
   *
   * @param value 要设置的旋转轴的X坐标值。
   * @param selector 样式选择器。
   */
  void setStyleTransformPivotX(int32_t value,
                               lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的旋转轴的Y坐标。
   *
   * @param value 要设置的旋转轴的Y坐标值。
   * @param selector 样式选择器。
   */
  void setStyleTransformPivotY(int32_t value,
                               lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的X轴倾斜角度。
   *
   * @param value 要设置的X轴倾斜角度。
   * @param selector 样式选择器。
   */
  void setStyleTransformSkewX(int32_t value,
                              lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的Y轴倾斜角度。
   *
   * @param value 要设置的Y轴倾斜角度。
   * @param selector 样式选择器。
   */
  void setStyleTransformSkewY(int32_t value,
                              lv_style_selector_t selector) const;

  void set_style_pad_top(int32_t value, lv_style_selector_t selector) const;
  void set_style_pad_bottom(int32_t value, lv_style_selector_t selector) const;
  void set_style_pad_left(int32_t value, lv_style_selector_t selector) const;
  void set_style_pad_right(int32_t value, lv_style_selector_t selector) const;
  void set_style_pad_row(int32_t value, lv_style_selector_t selector) const;
  void set_style_pad_column(int32_t value, lv_style_selector_t selector) const;
  void set_style_pad_radial(int32_t value, lv_style_selector_t selector) const;
  void set_style_margin_top(int32_t value, lv_style_selector_t selector) const;
  void set_style_margin_bottom(int32_t value,
                               lv_style_selector_t selector) const;
  void set_style_margin_left(int32_t value, lv_style_selector_t selector) const;
  void set_style_margin_right(int32_t value,
                              lv_style_selector_t selector) const;
  void set_style_bg_color(lv_color_t value, lv_style_selector_t selector) const;
  void set_style_bg_opa(lv_opa_t value, lv_style_selector_t selector) const;
  void set_style_bg_grad_color(lv_color_t value,
                               lv_style_selector_t selector) const;
  void set_style_bg_grad_dir(lv_grad_dir_t value,
                             lv_style_selector_t selector) const;
  void set_style_bg_main_stop(int32_t value,
                              lv_style_selector_t selector) const;
  void set_style_bg_grad_stop(int32_t value,
                              lv_style_selector_t selector) const;
  void set_style_bg_main_opa(lv_opa_t value,
                             lv_style_selector_t selector) const;
  void set_style_bg_grad_opa(lv_opa_t value,
                             lv_style_selector_t selector) const;
  void set_style_bg_grad(const lv_grad_dsc_t *value,
                         lv_style_selector_t selector) const;
  void set_style_bg_image_src(const void *value,
                              lv_style_selector_t selector) const;
  void set_style_bg_image_opa(lv_opa_t value,
                              lv_style_selector_t selector) const;
  void set_style_bg_image_recolor(lv_color_t value,
                                  lv_style_selector_t selector) const;
  void set_style_bg_image_recolor_opa(lv_opa_t value,
                                      lv_style_selector_t selector) const;
  void set_style_bg_image_tiled(bool value, lv_style_selector_t selector) const;
  void set_style_border_color(lv_color_t value,
                              lv_style_selector_t selector) const;
  void set_style_border_opa(lv_opa_t value, lv_style_selector_t selector) const;
  void set_style_border_width(int32_t value,
                              lv_style_selector_t selector) const;
  void set_style_border_side(lv_border_side_t value,
                             lv_style_selector_t selector) const;
  void set_style_border_post(bool value, lv_style_selector_t selector) const;
  void set_style_outline_width(int32_t value,
                               lv_style_selector_t selector) const;
  void set_style_outline_color(lv_color_t value,
                               lv_style_selector_t selector) const;
  void set_style_outline_opa(lv_opa_t value,
                             lv_style_selector_t selector) const;
  void set_style_outline_pad(int32_t value, lv_style_selector_t selector) const;
  void set_style_shadow_width(int32_t value,
                              lv_style_selector_t selector) const;
  void set_style_shadow_offset_x(int32_t value,
                                 lv_style_selector_t selector) const;
  void set_style_shadow_offset_y(int32_t value,
                                 lv_style_selector_t selector) const;
  void set_style_shadow_spread(int32_t value,
                               lv_style_selector_t selector) const;
  void set_style_shadow_color(lv_color_t value,
                              lv_style_selector_t selector) const;
  void set_style_shadow_opa(lv_opa_t value, lv_style_selector_t selector) const;
  void set_style_image_opa(lv_opa_t value, lv_style_selector_t selector) const;
  void set_style_image_recolor(lv_color_t value,
                               lv_style_selector_t selector) const;
  void set_style_image_recolor_opa(lv_opa_t value,
                                   lv_style_selector_t selector) const;
  void set_style_line_width(int32_t value, lv_style_selector_t selector) const;
  void set_style_line_dash_width(int32_t value,
                                 lv_style_selector_t selector) const;
  void set_style_line_dash_gap(int32_t value,
                               lv_style_selector_t selector) const;
  void set_style_line_rounded(bool value, lv_style_selector_t selector) const;
  void set_style_line_color(lv_color_t value,
                            lv_style_selector_t selector) const;
  void set_style_line_opa(lv_opa_t value, lv_style_selector_t selector) const;
  void set_style_arc_width(int32_t value, lv_style_selector_t selector) const;
  void set_style_arc_rounded(bool value, lv_style_selector_t selector) const;
  void set_style_arc_color(lv_color_t value,
                           lv_style_selector_t selector) const;
  void set_style_arc_opa(lv_opa_t value, lv_style_selector_t selector) const;
  void set_style_arc_image_src(const void *value,
                               lv_style_selector_t selector) const;
  void set_style_text_color(lv_color_t value,
                            lv_style_selector_t selector) const;
  void set_style_text_opa(lv_opa_t value, lv_style_selector_t selector) const;
  void set_style_text_font(const lv_font_t *value,
                           lv_style_selector_t selector) const;
  void set_style_text_letter_space(int32_t value,
                                   lv_style_selector_t selector) const;
  void set_style_text_line_space(int32_t value,
                                 lv_style_selector_t selector) const;
  void set_style_text_decor(lv_text_decor_t value,
                            lv_style_selector_t selector) const;
  void set_style_text_align(lv_text_align_t value,
                            lv_style_selector_t selector) const;
  void set_style_radius(int32_t value, lv_style_selector_t selector) const;
  void set_style_radial_offset(int32_t value,
                               lv_style_selector_t selector) const;
  void set_style_clip_corner(bool value, lv_style_selector_t selector) const;
  void set_style_opa(lv_opa_t value, lv_style_selector_t selector) const;
  void set_style_opa_layered(lv_opa_t value,
                             lv_style_selector_t selector) const;
  void set_style_color_filter_dsc(const lv_color_filter_dsc_t *value,
                                  lv_style_selector_t selector) const;
  void set_style_color_filter_opa(lv_opa_t value,
                                  lv_style_selector_t selector) const;
  void set_style_anim(const lv_anim_t *value,
                      lv_style_selector_t selector) const;
  void set_style_anim_duration(uint32_t value,
                               lv_style_selector_t selector) const;
  void set_style_transition(const lv_style_transition_dsc_t *value,
                            lv_style_selector_t selector) const;
  void set_style_blend_mode(lv_blend_mode_t value,
                            lv_style_selector_t selector) const;
  void set_style_layout(uint16_t value, lv_style_selector_t selector) const;
  void set_style_base_dir(lv_base_dir_t value,
                          lv_style_selector_t selector) const;
  void set_style_bitmap_mask_src(const void *value,
                                 lv_style_selector_t selector) const;
  void set_style_rotary_sensitivity(uint32_t value,
                                    lv_style_selector_t selector) const;
  void set_style_flex_flow(lv_flex_flow_t value,
                           lv_style_selector_t selector) const;
  void set_style_flex_main_place(lv_flex_align_t value,
                                 lv_style_selector_t selector) const;
  void set_style_flex_cross_place(lv_flex_align_t value,
                                  lv_style_selector_t selector) const;
  void set_style_flex_track_place(lv_flex_align_t value,
                                  lv_style_selector_t selector) const;
  void set_style_flex_grow(uint8_t value, lv_style_selector_t selector) const;
  void set_style_grid_column_dsc_array(const int32_t *value,
                                       lv_style_selector_t selector) const;
  void set_style_grid_column_align(lv_grid_align_t value,
                                   lv_style_selector_t selector) const;
  void set_style_grid_row_dsc_array(const int32_t *value,
                                    lv_style_selector_t selector) const;
  void set_style_grid_row_align(lv_grid_align_t value,
                                lv_style_selector_t selector) const;
  void set_style_grid_cell_column_pos(int32_t value,
                                      lv_style_selector_t selector) const;
  void set_style_grid_cell_x_align(lv_grid_align_t value,
                                   lv_style_selector_t selector) const;
  void set_style_grid_cell_column_span(int32_t value,
                                       lv_style_selector_t selector) const;
  void set_style_grid_cell_row_pos(int32_t value,
                                   lv_style_selector_t selector) const;
  void set_style_grid_cell_y_align(lv_grid_align_t value,
                                   lv_style_selector_t selector) const;
  void set_style_grid_cell_row_span(int32_t value,
                                    lv_style_selector_t selector) const;

  void delete_delayed(uint32_t delay_ms) const;
  void delete_async() const;
  void set_parent(lv_obj_t *parent) const;
  void swap(lv_obj_t *obj2) const;
  void move_to_index(int32_t index) const;
  void tree_walk(lv_obj_tree_walk_cb_t cb, void *user_data) const;
  void dump_tree() const;

  void style_create_transition(lv_part_t part, lv_state_t prev_state,
                               lv_state_t new_state,
                               const lv_obj_style_transition_dsc_t *tr) const;
  void update_layer_type() const;

  void redraw(lv_layer_t *layer) const;
};

} // namespace LVGLEx

#endif // LVGLEX_WIDGET_BASE_H
