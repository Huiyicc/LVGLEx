//
// Created by 19254 on 24-12-16.
//

#ifndef LVGLEX_WIDGET_BASE_H
#define LVGLEX_WIDGET_BASE_H

#include "./widget_event_base.h"
#include <LVGLEx/object/obj_global.h>
#include <LVGLEx/object/obj_pointer.h>
#include <lvgl.h>
#include <map>
#include <memory>
#include <optional>
#include <set>

namespace LVGLEx {

class WindowBase;
class Layer;
class Matrix;
class Point;
class Area;
class Style;

#define WIDGET_OBJ_CREATE_H(TYPE)                                              \
  static TYPE create(WidgetBase *parent) noexcept;                             \
  static TYPE create(WindowBase *parent) noexcept;                             \
  TYPE(TYPE &&other) noexcept;                                                 \
  TYPE &operator=(TYPE &&other) noexcept;
#define WIDGET_OBJ_CREATE_CPP(TYPE, OBJCREATE_FUNC)                            \
  TYPE TYPE::create(WindowBase *parent) noexcept {                             \
    TYPE r;                                                                    \
    auto scr = parent->getScreenActive();                                      \
    r.m_obj = WidgetPointer::makeQuote(OBJCREATE_FUNC(scr.get()));             \
    r.init();                                                                  \
    return r;                                                                  \
  }                                                                            \
  TYPE TYPE::create(WidgetBase *parent) noexcept {                             \
    TYPE r;                                                                    \
    r.m_obj = WidgetPointer::makeQuote(OBJCREATE_FUNC(parent->getObj()));      \
    r.init();                                                                  \
    return r;                                                                  \
  };                                                                           \
  TYPE::TYPE(TYPE &&other) noexcept { *this = std::move(other); }              \
  TYPE &TYPE::operator=(TYPE &&other) noexcept {                               \
    m_obj = std::move(other.m_obj);                                            \
    return *this;                                                              \
  }

class WidgetEvent {
  lv_event_t *m_event = nullptr;
  friend class WidgetBase;
  WidgetEvent(lv_event_t *e);

public:
  lv_event_t* operator->() const {
    return m_event;
  }
  void* userData() const;
};

typedef std::function<void(WidgetEvent &)> EventCallBackFunc;

class WidgetEventDsc {
private:
  lv_event_dsc_t *m_dsc = nullptr;
  void *m_data_ptr;
  EventCallBackFunc m_func;
  friend class WidgetBase;

public:
  WidgetEventDsc();
};

class WidgetBase : public WidgetEventBase {
private:
std::map<int,std::shared_ptr<WidgetEventDsc>> m_event_dsc;
protected:
  WidgetPointer m_obj;
  // lv_obj_t *m_obj = nullptr;
  // WindowBase *m_parent = nullptr;
  // std::set<std::unique_ptr<WidgetBase>> m_children;

  virtual void init() final;

public:

  WidgetBase();
  ~WidgetBase() override;

  WidgetBase(WidgetBase &&other) noexcept;
  WidgetBase &operator=(WidgetBase &&other) noexcept;

  [[nodiscard]] lv_obj_t *getObj() const;

  static WidgetBase makeFromPtr(lv_obj_t *ptr);

  [[nodiscard]] std::optional<WidgetBase> getParent() const;
  [[nodiscard]] WindowBase *getWindow() const;
  [[nodiscard]] WidgetPointer getScreenActive() const;
  virtual WidgetPointer release() final;

  int addEvent(lv_event_code_t filter,
           const EventCallBackFunc &func,
           void *user_data);
  int addEvent(const EventCallBackFunc &func,
           void *user_data);

  void removeEvent(int event_id);

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
  [[nodiscard]] Point transformPoint(lv_obj_point_transform_flag_t flags) const;

  /**
   * @brief 使用对象的角度和缩放样式属性转换一个点数组。
   *
   * @param points 指向要转换的点数组的指针，转换结果将写回到此处。
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
  [[nodiscard]] Area
  getTransformedArea(lv_obj_point_transform_flag_t flags) const;

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

  /**
   * @brief 设置样式的顶部内边距。
   *
   * @param value 内边距的值。
   * @param selector 样式选择器，用于指定应用样式的目标。
   */
  void setStylePadTop(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的底部内边距。
   *
   * @param value 内边距的值。
   * @param selector 样式选择器，用于指定应用样式的目标。
   */
  void setStylePadBottom(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的左侧内边距。
   *
   * @param value 内边距的值。
   * @param selector 样式选择器，用于指定应用样式的目标。
   */
  void setStylePadLeft(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的右侧内边距。
   *
   * @param value 内边距的值。
   * @param selector 样式选择器，用于指定应用样式的目标。
   */
  void setStylePadRight(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的行间距。
   *
   * @param value 行间距的值。
   * @param selector 样式选择器，用于指定应用样式的目标。
   */
  void setStylePadRow(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的列间距。
   *
   * @param value 列间距的值。
   * @param selector 样式选择器，用于指定应用样式的目标。
   */
  void setStylePadColumn(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的径向内边距。
   *
   * @param value 径向内边距的值。
   * @param selector 样式选择器，用于指定应用样式的目标。
   */
  void setStylePadRadial(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的顶部外边距。
   *
   * @param value 外边距的值。
   * @param selector 样式选择器，用于指定应用样式的目标。
   */
  void setStyleMarginTop(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的底部外边距。
   *
   * @param value 外边距的值。
   * @param selector 样式选择器，用于指定应用样式的目标。
   */
  void setStyleMarginBottom(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的左侧外边距。
   *
   * @param value 外边距的值。
   * @param selector 样式选择器，用于指定应用样式的目标。
   */
  void setStyleMarginLeft(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的右侧外边距。
   *
   * @param value 外边距的值。
   * @param selector 样式选择器，用于指定应用样式的目标。
   */
  void setStyleMarginRight(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的背景颜色。
   *
   * @param value 背景颜色的值。
   * @param selector 样式选择器，用于指定应用样式的目标。
   */
  void setStyleBgColor(lv_color_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的背景不透明度。
   *
   * @param value 背景不透明度的值。
   * @param selector 样式选择器，用于指定应用样式的目标。
   */
  void setStyleBgOpa(lv_opa_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的背景渐变颜色。
   *
   * @param value 背景渐变颜色的值。
   * @param selector 样式选择器，用于指定应用样式的目标。
   */
  void setStyleBgGradColor(lv_color_t value,
                           lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的背景渐变方向。
   *
   * @param value 背景渐变方向的值。
   * @param selector 样式选择器，用于指定应用样式的目标。
   */
  void setStyleBgGradDir(lv_grad_dir_t value,
                         lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的背景渐变起始位置。
   *
   * @param value 背景渐变起始位置的值。
   * @param selector 样式选择器，用于指定应用样式的目标。
   */
  void setStyleBgMainStop(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的背景渐变终止位置。
   *
   * @param value 背景渐变终止位置的值。
   * @param selector 样式选择器，用于指定应用样式的目标。
   */
  void setStyleBgGradStop(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的背景主颜色不透明度。
   *
   * @param value 背景主颜色不透明度的值。
   * @param selector 样式选择器，用于指定应用样式的目标。
   */
  void setStyleBgMainOpa(lv_opa_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的背景渐变颜色不透明度。
   *
   * @param value 背景渐变颜色不透明度的值。
   * @param selector 样式选择器，用于指定应用样式的目标。
   */
  void setStyleBgGradOpa(lv_opa_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的背景渐变描述信息。
   *
   * @param value 指向背景渐变描述信息的指针。
   * @param selector 样式选择器，用于指定应用样式的目标。
   */
  void setStyleBgGrad(const lv_grad_dsc_t *value,
                      lv_style_selector_t selector) const;

  /**
   * @brief 设置背景图像的源。
   *
   * @param value 图像源。
   * @param selector 样式选择器。
   */
  void setStyleBgImageSrc(const void *value,
                          lv_style_selector_t selector) const;

  /**
   * @brief 设置背景图像的不透明度。
   *
   * @param value 不透明度值。
   * @param selector 样式选择器。
   */
  void setStyleBgImageOpa(lv_opa_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置背景图像的重新着色颜色。
   *
   * @param value 重新着色颜色。
   * @param selector 样式选择器。
   */
  void setStyleBgImageRecolor(lv_color_t value,
                              lv_style_selector_t selector) const;

  /**
   * @brief 设置背景图像的重新着色不透明度。
   *
   * @param value 重新着色不透明度值。
   * @param selector 样式选择器。
   */
  void setStyleBgImageRecolorOpa(lv_opa_t value,
                                 lv_style_selector_t selector) const;

  /**
   * @brief 设置背景图像是否平铺。
   *
   * @param value 是否平铺。
   * @param selector 样式选择器。
   */
  void setStyleBgImageTiled(bool value, lv_style_selector_t selector) const;

  /**
   * @brief 设置边框颜色。
   *
   * @param value 边框颜色。
   * @param selector 样式选择器。
   */
  void setStyleBorderColor(lv_color_t value,
                           lv_style_selector_t selector) const;

  /**
   * @brief 设置边框不透明度。
   *
   * @param value 边框不透明度值。
   * @param selector 样式选择器。
   */
  void setStyleBorderOpa(lv_opa_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置边框宽度。
   *
   * @param value 边框宽度。
   * @param selector 样式选择器。
   */
  void setStyleBorderWidth(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置边框的边。
   *
   * @param value 边框边。
   * @param selector 样式选择器。
   */
  void setStyleBorderSide(lv_border_side_t value,
                          lv_style_selector_t selector) const;

  /**
   * @brief 设置边框是否在内容之后绘制。
   *
   * @param value 是否在内容之后绘制。
   * @param selector 样式选择器。
   */
  void setStyleBorderPost(bool value, lv_style_selector_t selector) const;

  /**
   * @brief 设置轮廓宽度。
   *
   * @param value 轮廓宽度。
   * @param selector 样式选择器。
   */
  void setStyleOutlineWidth(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置轮廓颜色。
   *
   * @param value 轮廓颜色。
   * @param selector 样式选择器。
   */
  void setStyleOutlineColor(lv_color_t value,
                            lv_style_selector_t selector) const;

  /**
   * @brief 设置轮廓不透明度。
   *
   * @param value 轮廓不透明度值。
   * @param selector 样式选择器。
   */
  void setStyleOutlineOpa(lv_opa_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置轮廓填充。
   *
   * @param value 轮廓填充。
   * @param selector 样式选择器。
   */
  void setStyleOutlinePad(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置阴影宽度。
   *
   * @param value 阴影宽度。
   * @param selector 样式选择器。
   */
  void setStyleShadowWidth(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置阴影的X轴偏移。
   *
   * @param value X轴偏移。
   * @param selector 样式选择器。
   */
  void setStyleShadowOffsetX(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置阴影的Y轴偏移。
   *
   * @param value Y轴偏移。
   * @param selector 样式选择器。
   */
  void setStyleShadowOffsetY(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置阴影的扩展。
   *
   * @param value 阴影扩展。
   * @param selector 样式选择器。
   */
  void setStyleShadowSpread(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置阴影颜色。
   *
   * @param value 阴影颜色。
   * @param selector 样式选择器。
   */
  void setStyleShadowColor(lv_color_t value,
                           lv_style_selector_t selector) const;

  /**
   * @brief 设置阴影不透明度。
   *
   * @param value 阴影不透明度值。
   * @param selector 样式选择器。
   */
  void setStyleShadowOpa(lv_opa_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置图像不透明度。
   *
   * @param value 图像不透明度值。
   * @param selector 样式选择器。
   */
  void setStyleImageOpa(lv_opa_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置图像的重新着色颜色。
   *
   * @param value 重新着色颜色。
   * @param selector 样式选择器。
   */
  void setStyleImageRecolor(lv_color_t value,
                            lv_style_selector_t selector) const;

  /**
   * @brief 设置图像的重新着色不透明度。
   *
   * @param value 重新着色不透明度值。
   * @param selector 样式选择器。
   */
  void setStyleImageRecolorOpa(lv_opa_t value,
                               lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的线宽。
   *
   * @param value 线宽的值。
   * @param selector 样式选择器。
   */
  void setStyleLineWidth(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的线条虚线宽度。
   *
   * @param value 虚线宽度的值。
   * @param selector 样式选择器。
   */
  void setStyleLineDashWidth(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的线条虚线间隔。
   *
   * @param value 虚线间隔的值。
   * @param selector 样式选择器。
   */
  void setStyleLineDashGap(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的线条是否圆角。
   *
   * @param value 是否圆角。
   * @param selector 样式选择器。
   */
  void setStyleLineRounded(bool value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的线条颜色。
   *
   * @param value 线条颜色。
   * @param selector 样式选择器。
   */
  void setStyleLineColor(lv_color_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的线条不透明度。
   *
   * @param value 线条不透明度。
   * @param selector 样式选择器。
   */
  void setStyleLineOpa(lv_opa_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的弧宽度。
   *
   * @param value 弧宽度的值。
   * @param selector 样式选择器。
   */
  void setStyleArcWidth(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的弧是否圆角。
   *
   * @param value 是否圆角。
   * @param selector 样式选择器。
   */
  void setStyleArcRounded(bool value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的弧颜色。
   *
   * @param value 弧颜色。
   * @param selector 样式选择器。
   */
  void setStyleArcColor(lv_color_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的弧不透明度。
   *
   * @param value 弧不透明度。
   * @param selector 样式选择器。
   */
  void setStyleArcOpa(lv_opa_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的弧图像源。
   *
   * @param value 弧图像源。
   * @param selector 样式选择器。
   */
  void setStyleArcImageSrc(const void *value,
                           lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的文本颜色。
   *
   * @param value 文本颜色。
   * @param selector 样式选择器。
   */
  void setStyleTextColor(lv_color_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的文本不透明度。
   *
   * @param value 文本不透明度。
   * @param selector 样式选择器。
   */
  void setStyleTextOpa(lv_opa_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的文本字体。
   *
   * @param value 文本字体。
   * @param selector 样式选择器。
   */
  void setStyleTextFont(const lv_font_t *value,
                        lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的文本字母间距。
   *
   * @param value 字母间距的值。
   * @param selector 样式选择器。
   */
  void setStyleTextLetterSpace(int32_t value,
                               lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的文本行间距。
   *
   * @param value 行间距的值。
   * @param selector 样式选择器。
   */
  void setStyleTextLineSpace(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的文本装饰。
   *
   * @param value 文本装饰。
   * @param selector 样式选择器。
   */
  void setStyleTextDecor(lv_text_decor_t value,
                         lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的文本对齐方式。
   *
   * @param value 文本对齐方式。
   * @param selector 样式选择器。
   */
  void setStyleTextAlign(lv_text_align_t value,
                         lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的圆角半径。
   *
   * @param value 圆角半径的值。
   * @param selector 样式选择器。
   */
  void setStyleRadius(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的径向偏移。
   *
   * @param value 径向偏移的值。
   * @param selector 样式选择器。
   */
  void setStyleRadialOffset(int32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的剪裁角标志。
   *
   * @param value 剪裁角标志的值。
   * @param selector 样式选择器。
   */
  void setStyleClipCorner(bool value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的不透明度。
   *
   * @param value 不透明度的值。
   * @param selector 样式选择器。
   */
  void setStyleOpa(lv_opa_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的分层不透明度。
   *
   * @param value 分层不透明度的值。
   * @param selector 样式选择器。
   */
  void setStyleOpaLayered(lv_opa_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的颜色过滤描述符。
   *
   * @param value 指向颜色过滤描述符的指针。
   * @param selector 样式选择器。
   */
  void setStyleColorFilterDsc(const lv_color_filter_dsc_t *value,
                              lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的颜色过滤不透明度。
   *
   * @param value 颜色过滤不透明度的值。
   * @param selector 样式选择器。
   */
  void setStyleColorFilterOpa(lv_opa_t value,
                              lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的动画。
   *
   * @param value 指向动画的指针。
   * @param selector 样式选择器。
   */
  void setStyleAnim(const lv_anim_t *value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的动画持续时间。
   *
   * @param value 动画持续时间的值。
   * @param selector 样式选择器。
   */
  void setStyleAnimDuration(uint32_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的过渡描述符。
   *
   * @param value 指向过渡描述符的指针。
   * @param selector 样式选择器。
   */
  void setStyleTransition(const lv_style_transition_dsc_t *value,
                          lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的混合模式。
   *
   * @param value 混合模式的值。
   * @param selector 样式选择器。
   */
  void setStyleBlendMode(lv_blend_mode_t value,
                         lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的布局。
   *
   * @param value 布局的值。
   * @param selector 样式选择器。
   */
  void setStyleLayout(uint16_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的基方向。
   *
   * @param value 基方向的值。
   * @param selector 样式选择器。
   */
  void setStyleBaseDir(lv_base_dir_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的位图遮罩源。
   *
   * @param value 指向位图遮罩源的指针。
   * @param selector 样式选择器。
   */
  void setStyleBitmapMaskSrc(const void *value,
                             lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的旋转灵敏度。
   *
   * @param value 旋转灵敏度的值。
   * @param selector 样式选择器。
   */
  void setStyleRotarySensitivity(uint32_t value,
                                 lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的弹性流动。
   *
   * @param value 弹性流动的值。
   * @param selector 样式选择器。
   */
  void setStyleFlexFlow(lv_flex_flow_t value,
                        lv_style_selector_t selector) const;

  /**
   * @brief 设置样式的弹性主对齐。
   *
   * @param value 弹性主对齐的值。
   * @param selector 样式选择器。
   */
  void setStyleFlexMainPlace(lv_flex_align_t value,
                             lv_style_selector_t selector) const;

  /**
   * @brief 设置弹性布局的交叉轴对齐方式。
   *
   * @param value 弹性布局的交叉轴对齐方式。
   * @param selector 样式选择器。
   */
  void setStyleFlexCrossPlace(lv_flex_align_t value,
                              lv_style_selector_t selector) const;

  /**
   * @brief 设置弹性布局的主轴对齐方式。
   *
   * @param value 弹性布局的主轴对齐方式。
   * @param selector 样式选择器。
   */
  void setStyleFlexTrackPlace(lv_flex_align_t value,
                              lv_style_selector_t selector) const;

  /**
   * @brief 设置弹性布局的增长因子。
   *
   * @param value 弹性布局的增长因子。
   * @param selector 样式选择器。
   */
  void setStyleFlexGrow(uint8_t value, lv_style_selector_t selector) const;

  /**
   * @brief 设置网格布局的列描述数组。
   *
   * @param value 指向列描述数组的指针。
   * @param selector 样式选择器。
   */
  void setStyleGridColumnDscArray(const int32_t *value,
                                  lv_style_selector_t selector) const;

  /**
   * @brief 设置网格布局的列对齐方式。
   *
   * @param value 网格布局的列对齐方式。
   * @param selector 样式选择器。
   */
  void setStyleGridColumnAlign(lv_grid_align_t value,
                               lv_style_selector_t selector) const;

  /**
   * @brief 设置网格布局的行描述数组。
   *
   * @param value 指向行描述数组的指针。
   * @param selector 样式选择器。
   */
  void setStyleGridRowDscArray(const int32_t *value,
                               lv_style_selector_t selector) const;

  /**
   * @brief 设置网格布局的行对齐方式。
   *
   * @param value 网格布局的行对齐方式。
   * @param selector 样式选择器。
   */
  void setStyleGridRowAlign(lv_grid_align_t value,
                            lv_style_selector_t selector) const;

  /**
   * @brief 设置网格单元格的列位置。
   *
   * @param value 网格单元格的列位置。
   * @param selector 样式选择器。
   */
  void setStyleGridCellColumnPos(int32_t value,
                                 lv_style_selector_t selector) const;

  /**
   * @brief 设置网格单元格的水平对齐方式。
   *
   * @param value 网格单元格的水平对齐方式。
   * @param selector 样式选择器。
   */
  void setStyleGridCellXAlign(lv_grid_align_t value,
                              lv_style_selector_t selector) const;

  /**
   * @brief 设置网格单元格的列跨度。
   *
   * @param value 网格单元格的列跨度。
   * @param selector 样式选择器。
   */
  void setStyleGridCellColumnSpan(int32_t value,
                                  lv_style_selector_t selector) const;

  /**
   * @brief 设置网格单元格的行位置。
   *
   * @param value 网格单元格的行位置。
   * @param selector 样式选择器。
   */
  void setStyleGridCellRowPos(int32_t value,
                              lv_style_selector_t selector) const;

  /**
   * @brief 设置网格单元格的垂直对齐方式。
   *
   * @param value 网格单元格的垂直对齐方式。
   * @param selector 样式选择器。
   */
  void setStyleGridCellYAlign(lv_grid_align_t value,
                              lv_style_selector_t selector) const;

  /**
   * @brief 设置网格单元格的行跨度。
   *
   * @param value 网格单元格的行跨度。
   * @param selector 样式选择器。
   */
  void setStyleGridCellRowSpan(int32_t value,
                               lv_style_selector_t selector) const;

  /**
   * @brief 延迟删除对象。
   *
   * @param delayMs 延迟的毫秒数。
   */
  void deleteDelayed(uint32_t delayMs) const;

  /**
   * @brief 异步删除对象。
   */
  void deleteAsync() const;

  /**
   * @brief 设置对象的父对象。
   *
   * @param parent 指向父对象。
   */
  void setParent(const WidgetBase &parent) const;

  /**
   * @brief 交换两个对象的位置。
   *
   * @param obj2 指向要交换的对象。
   */
  void swap(WidgetBase &obj2) const noexcept;

  /**
   * @brief 将对象移动到指定的索引位置。
   *
   * @param index 目标索引位置。
   */
  void moveToIndex(int32_t index) const;

  /**
   * @brief 遍历对象树。
   *
   * @param cb 回调函数，用于处理树中的每个对象。
   * @param userData 用户数据，将传递给回调函数。
   */
  void treeWalk(const LvObjTreeWalkCbHandel &cb, void *userData);

  /**
   * @brief 打印对象树的结构。
   */
  void dumpTree() const;

  /**
   * @brief 为对象创建样式过渡。
   *
   * @param part 对象的部分。
   * @param prevState 之前的状态。
   * @param newState 新的状态。
   * @param tr 指向样式过渡描述的指针。
   */
  void styleCreateTransition(lv_part_t part, lv_state_t prevState,
                             lv_state_t newState,
                             const lv_obj_style_transition_dsc_t *tr) const;

  /**
   * @brief 更新对象的图层类型。
   */
  void updateLayerType() const;

  /**
   * @brief 重绘指定的图层。
   *
   * @param layer 指向要重绘的图层的指针。
   */
  void redraw(Layer &layer) const;

  /**
   * @brief 根据给定的屏幕空间中的点对对象进行命中测试。
   *
   * @param point 屏幕空间中的点（绝对坐标）。
   * @return 如果对象被认为在该点下方，则返回 true；否则返回 false。
   *
   * @example
   * @code
   * Point myPoint(x, y);
   * bool isHit = obj.hitTest(myPoint);
   * if (isHit) {
   *     // 对象在点下方，可以进行相应处理
   * }
   * @endcode
   */
  [[nodiscard]] bool hitTest(const Point &point) const;

  /**
   * @brief 获取当前对象所在的屏幕。
   *
   * @return 包含屏幕对象的WidgetBase。
   */
  [[nodiscard]] WidgetBase getScreen() const;

  /**
   * @brief 获取当前对象所在的显示器。
   *
   * @return 包含显示器指针的DisplayPointer。
   */
  [[nodiscard]] DisplayPointer getDisplay() const;

  /**
   * @brief 获取当前对象的父对象。
   *
   * @return 包含父对象的WidgetBase。
   */
  [[nodiscard]] WidgetBase getParent();

  /**
   * @brief 获取当前对象的指定索引的子对象。
   *
   * @param idx 子对象的索引。
   * @return 包含子对象的WidgetBase。
   */
  [[nodiscard]] WidgetBase getChild(int32_t idx) const;

  /**
   * @brief 根据类型获取当前对象的指定索引的子对象。
   *
   * @param idx 子对象的索引。
   * @param class_p 指向对象类型的指针。
   * @return 包含子对象的WidgetBase。
   */
  [[nodiscard]] WidgetBase getChildByType(int32_t idx,
                                          const lv_obj_class_t *class_p) const;

  /**
   * @brief 获取当前对象的指定索引的兄弟对象。
   *
   * @param idx 兄弟对象的索引。
   * @return 包含兄弟对象的WidgetBase。
   */
  [[nodiscard]] WidgetBase getSibling(int32_t idx) const;

  /**
   * @brief 根据类型获取当前对象的指定索引的兄弟对象。
   *
   * @param idx 兄弟对象的索引。
   * @param class_p 指向对象类型的指针。
   * @return 包含兄弟对象的WidgetBase。
   */
  [[nodiscard]] WidgetBase
  getSiblingByType(int32_t idx, const lv_obj_class_t *class_p) const;

  /**
   * @brief 获取当前对象的子对象数量。
   *
   * @return 子对象的数量。
   */
  [[nodiscard]] uint32_t getChildCount() const;

  /**
   * @brief 根据类型获取当前对象的子对象数量。
   *
   * @param class_p 指向对象类型的指针。
   * @return 子对象的数量。
   */
  uint32_t getChildCountByType(const lv_obj_class_t *class_p) const;

  /**
   * @brief 获取对象的索引。
   *
   * @return 返回对象的索引。
   */
  int32_t getIndex() const;

  /**
   * @brief 根据类型获取对象的索引。
   *
   * @param class_p 指向对象类的指针。
   * @return 返回对象的索引。
   */
  int32_t getIndexByType(const lv_obj_class_t *class_p) const;

  /**
   * @brief 获取对象的坐标。
   *
   * @param coords 将对象的坐标写入此区域。
   */
  void getCoords(Area &coords) const;

  /**
   * @brief 获取对象的X坐标。
   *
   * @return 返回对象的X坐标。
   */
  int32_t getX() const;

  /**
   * @brief 获取对象的X2坐标。
   *
   * @return 返回对象的X2坐标。
   */
  int32_t getX2() const;

  /**
   * @brief 获取对象的Y坐标。
   *
   * @return 返回对象的Y坐标。
   */
  int32_t getY() const;

  /**
   * @brief 获取对象的Y2坐标。
   *
   * @return 返回对象的Y2坐标。
   */
  int32_t getY2() const;

  /**
   * @brief 获取对象对齐后的X坐标。
   *
   * @return 返回对齐后的X坐标。
   */
  int32_t getXAligned() const;

  /**
   * @brief 获取对象对齐后的Y坐标。
   *
   * @return 返回对齐后的Y坐标。
   */
  int32_t getYAligned() const;

  /**
   * @brief 获取对象的宽度。
   *
   * @return 返回对象的宽度。
   */
  int32_t getWidth() const;

  /**
   * @brief 获取对象的高度。
   *
   * @return 返回对象的高度。
   */
  int32_t getHeight() const;

  /**
   * @brief 获取对象的内容宽度。
   *
   * @return 内容宽度，以像素为单位。
   */
  int32_t getContentWidth() const;

  /**
   * @brief 获取对象的内容高度。
   *
   * @return 内容高度，以像素为单位。
   */
  int32_t getContentHeight() const;

  /**
   * @brief 获取对象的内容区域的坐标。
   *
   * @param area 指向存储内容区域坐标的 `Area` 对象。
   */
  void getContentCoords(Area &area) const;

  /**
   * @brief 获取对象自身的宽度。
   *
   * @return 对象自身宽度，以像素为单位。
   */
  int32_t getSelfWidth() const;

  /**
   * @brief 获取对象自身的高度。
   *
   * @return 对象自身高度，以像素为单位。
   */
  int32_t getSelfHeight() const;

  /**
   * @brief 获取对象的变换矩阵。
   *
   * @return 对象的变换矩阵 `Matrix`。
   */
  const Matrix getTransform() const;

  /**
   * @brief 获取对象变换后的区域。
   *
   * @param area 指向存储变换后区域的 `Area` 对象。
   * @param flags 变换标志，参见 `lv_obj_point_transform_flag_t`。
   */
  void getTransformedArea(Area &area,
                          lv_obj_point_transform_flag_t flags) const;

  /**
   * @brief 使对象的区域失效，从而触发重绘。
   */
  void invalidate();

  /**
   * @brief 检查指定区域是否可见。
   *
   * @param area 指向要检查的区域的 `Area` 对象。
   * @return 如果区域可见则返回 `true`，否则返回 `false`。
   */
  bool areaIsVisible(Area &area) const;

  /**
   * @brief 检查对象是否可见。
   *
   * @return 如果对象可见则返回 `true`，否则返回 `false`。
   */
  bool isVisible() const;
};



} // namespace LVGLEx

#endif // LVGLEX_WIDGET_BASE_H
