//
// Created by 19254 on 24-12-16.
//

#ifndef LVGLEX_WIDGET_EVENT_BASE_H
#define LVGLEX_WIDGET_EVENT_BASE_H

#include <lvgl.h>
#include <memory>
#include <set>

namespace LVGLEx {

class WindowBase;

class WidgetEventBase {
protected:
  virtual void init(lv_obj_t *m_obj) final;

public:
  virtual ~WidgetEventBase() = default;

  /** Input device events*/
  /**
   * @brief 按钮被按下时的事件处理函数。
   *
   * 该函数在按钮被按下时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的按下事件处理。
   */
  virtual void OnPressed(lv_event_t *e) {};

  /**
   * @brief 按钮正在被按下时的事件处理函数。
   *
   * 该函数在按钮被持续按下时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   */
  virtual void OnPressing(lv_event_t *e) {};

  /**
   * @brief 按钮失去按压时的事件处理函数。
   *
   * 该函数在按钮仍然被按压但光标/手指滑出按钮时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   */
  virtual void OnPressLost(lv_event_t *e) {};

  /**
   * @brief 短按事件处理函数。
   *
   * 该函数在按钮被短时间按下后释放时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   */
  virtual void OnShortClicked(lv_event_t *e) {};

  /**
   * @brief 单击事件处理函数。
   *
   * 该函数在短时间内的第一次单击时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   */
  virtual void OnSingleClicked(lv_event_t *e) {};
  /**
   * @brief 双击事件处理函数。
   *
   * 该函数在第二次短点击时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的双击事件处理。
   */
  virtual void OnDoubleClicked(lv_event_t *e) {};

  /**
   * @brief 三击事件处理函数。
   *
   * 该函数在第三次短点击时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的三击事件处理。
   */
  virtual void OnTripleClicked(lv_event_t *e) {};

  /**
   * @brief 长按事件处理函数。
   *
   * 该函数在对象被长按时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的长按事件处理。
   */
  virtual void OnLongPressed(lv_event_t *e) {};

  /**
   * @brief 长按重复事件处理函数。
   *
   * 该函数在长按重复时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的长按重复事件处理。
   */
  virtual void OnLongPressedRepeat(lv_event_t *e) {};

  /**
   * @brief 点击事件处理函数。
   *
   * 该函数在释放时被调用（如果没有滚动）。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的点击事件处理。
   */
  virtual void OnClicked(lv_event_t *e) {};

  /**
   * @brief 释放事件处理函数。
   *
   * 该函数在小部件被释放时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的释放事件处理。
   */
  virtual void OnReleased(lv_event_t *e) {};

  /**
   * @brief 滚动开始事件处理函数。
   *
   * 该函数在滚动开始时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的滚动开始事件处理。
   */
  virtual void OnScrollBegin(lv_event_t *e) {};
  /**
   * @brief 滚动抛出开始事件处理函数。
   *
   * 该函数在滚动抛出开始时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note
   * 此函数为虚函数，可以在派生类中重写以实现自定义的滚动抛出开始事件处理。
   */
  virtual void OnScrollThrowBegin(lv_event_t *e) {};
  /**
   * @brief 滚动结束时的事件处理函数。
   *
   * 该函数在滚动结束时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的滚动结束事件处理。
   */
  virtual void OnScrollEnd(lv_event_t *e) {};

  /**
   * @brief 滚动时的事件处理函数。
   *
   * 该函数在滚动过程中被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的滚动事件处理。
   */
  virtual void OnScroll(lv_event_t *e) {};

  /**
   * @brief 手势检测时的事件处理函数。
   *
   * 该函数在检测到手势时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的手势事件处理。
   */
  virtual void OnGesture(lv_event_t *e) {};

  /**
   * @brief 按键事件处理函数。
   *
   * 该函数在接收到按键时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的按键事件处理。
   */
  virtual void OnKey(lv_event_t *e) {};

  /**
   * @brief 旋转事件处理函数。
   *
   * 该函数在编码器或轮子旋转时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的旋转事件处理。
   */
  virtual void OnRotary(lv_event_t *e) {};

  /**
   * @brief 焦点事件处理函数。
   *
   * 该函数在小部件获得焦点时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的焦点事件处理。
   */
  virtual void OnFocused(lv_event_t *e) {};
  /**
   * @brief 失去焦点时的事件处理函数。
   *
   * 该函数在小部件失去焦点时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的失去焦点事件处理。
   */
  virtual void OnDefocused(lv_event_t *e) {};

  /**
   * @brief 离开时的事件处理函数。
   *
   * 该函数在小部件失去焦点但仍被选中时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的离开事件处理。
   */
  virtual void OnLeave(lv_event_t *e) {};

  /**
   * @brief 高级命中测试的事件处理函数。
   *
   * 该函数在执行高级命中测试时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的命中测试事件处理。
   */
  virtual void OnHitTest(lv_event_t *e) {};

  /**
   * @brief 输入设备重置时的事件处理函数。
   *
   * 该函数在输入设备被重置时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的重置事件处理。
   */
  virtual void OnIndevReset(lv_event_t *e) {};

  /**
   * @brief 悬停进入时的事件处理函数。
   *
   * 该函数在输入设备悬停在小部件上时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的悬停进入事件处理。
   */
  virtual void OnHoverOver(lv_event_t *e) {};

  /**
   * @brief 悬停离开时的事件处理函数。
   *
   * 该函数在输入设备离开小部件时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的悬停离开事件处理。
   */
  virtual void OnHoverLeave(lv_event_t *e) {};

  /** Drawing events */
  /**
   * @brief 检查 Widget 是否完全覆盖一个区域。
   *
   * 该函数在检查 Widget 覆盖区域时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的覆盖检查事件处理。
   */
  virtual void OnCoverCheck(lv_event_t *e) {};

  /**
   * @brief 获取 Widget 周围所需的额外绘制区域（例如阴影）。
   *
   * 该函数在获取额外绘制区域时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note
   * 此函数为虚函数，可以在派生类中重写以实现自定义的额外绘制区域事件处理。
   */
  virtual void OnRefrExtDrawSize(lv_event_t *e) {};

  /**
   * @brief 开始主绘制阶段。
   *
   * 该函数在主绘制阶段开始时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的主绘制开始事件处理。
   */
  virtual void OnDrawMainBegin(lv_event_t *e) {};

  /**
   * @brief 执行主绘制。
   *
   * 该函数在执行主绘制时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的主绘制事件处理。
   */
  virtual void OnDrawMain(lv_event_t *e) {};

  /**
   * @brief 完成主绘制阶段。
   *
   * 该函数在主绘制阶段完成时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的主绘制结束事件处理。
   */
  virtual void OnDrawMainEnd(lv_event_t *e) {};

  /**
   * @brief 开始后绘制阶段（当所有子元素都已绘制）。
   *
   * 该函数在后绘制阶段开始时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的后绘制开始事件处理。
   */
  virtual void OnDrawPostBegin(lv_event_t *e) {};
  /**
   * @brief 执行后绘制阶段（当所有子元素都已绘制）。
   *
   * 该函数在执行后绘制时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的后绘制事件处理。
   */
  virtual void OnDrawPost(lv_event_t *e) {};

  /**
   * @brief 完成后绘制阶段（当所有子元素都已绘制）。
   *
   * 该函数在后绘制阶段完成时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的后绘制结束事件处理。
   */
  virtual void OnDrawPostEnd(lv_event_t *e) {};

  /**
   * @brief 添加绘制任务。
   *
   * 该函数在添加绘制任务时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note
   * 此函数为虚函数，可以在派生类中重写以实现自定义的绘制任务添加事件处理。
   */
  virtual void OnDrawTaskAdded(lv_event_t *e) {};

  /** Other events */
  /**
   * @brief 对象创建时的事件处理函数。
   *
   * 该函数在对象被创建时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的创建事件处理。
   */
  virtual void OnCreate(lv_event_t *e) {};

  /**
   * @brief 对象删除时的事件处理函数。
   *
   * 该函数在对象被删除时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的删除事件处理。
   */
  virtual void OnDelete(lv_event_t *e) {};

  /**
   * @brief 子对象变化时的事件处理函数。
   *
   * 该函数在子对象被移除、添加或其大小、位置发生变化时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的子对象变化事件处理。
   */
  virtual void OnChildChanged(lv_event_t *e) {};

  /**
   * @brief 子对象创建时的事件处理函数。
   *
   * 该函数在子对象被创建时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的子对象创建事件处理。
   */
  virtual void OnChildCreated(lv_event_t *e) {};

  /**
   * @brief 子对象删除时的事件处理函数。
   *
   * 该函数在子对象被删除时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的子对象删除事件处理。
   */
  virtual void OnChildDeleted(lv_event_t *e) {};
  /**
   * @brief 屏幕卸载开始时的事件处理函数。
   *
   * 该函数在屏幕卸载开始时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的卸载开始事件处理。
   */
  virtual void OnScreenUnloadStart(lv_event_t *e) {};

  /**
   * @brief 屏幕加载开始时的事件处理函数。
   *
   * 该函数在屏幕加载开始时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的加载开始事件处理。
   */
  virtual void OnScreenLoadStart(lv_event_t *e) {};

  /**
   * @brief 屏幕加载完成时的事件处理函数。
   *
   * 该函数在屏幕加载完成时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的加载完成事件处理。
   */
  virtual void OnScreenLoaded(lv_event_t *e) {};

  /**
   * @brief 屏幕卸载完成时的事件处理函数。
   *
   * 该函数在屏幕卸载完成时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的卸载完成事件处理。
   */
  virtual void OnScreenUnloaded(lv_event_t *e) {};
  /**
   * @brief 对象坐标/大小发生变化时的事件处理函数。
   *
   * 该函数在对象的坐标或大小发生变化时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的大小变化事件处理。
   */
  virtual void OnSizeChanged(lv_event_t *e) {};

  /**
   * @brief 对象样式发生变化时的事件处理函数。
   *
   * 该函数在对象的样式发生变化时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的样式变化事件处理。
   */
  virtual void OnStyleChanged(lv_event_t *e) {};

  /**
   * @brief 子对象位置因布局重新计算而发生变化时的事件处理函数。
   *
   * 该函数在子对象的位置发生变化时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的布局变化事件处理。
   */
  virtual void OnLayoutChanged(lv_event_t *e) {};

  /**
   * @brief 获取小部件的内部大小时的事件处理函数。
   *
   * 该函数在请求获取小部件的内部大小时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的获取大小事件处理。
   */
  virtual void OnGetSelfSize(lv_event_t *e) {};

  /** Events of optional LVGL components */
  /**
   * @brief 无效区域发生变化时的事件处理函数。
   *
   * 该函数在无效区域发生变化时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的无效区域变化事件处理。
   */
  virtual void OnInvalidateArea(lv_event_t *e) {};

  /**
   * @brief 分辨率发生变化时的事件处理函数。
   *
   * 该函数在分辨率发生变化时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的分辨率变化事件处理。
   */
  virtual void OnResolutionChanged(lv_event_t *e) {};

  /**
   * @brief 颜色格式发生变化时的事件处理函数。
   *
   * 该函数在颜色格式发生变化时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的颜色格式变化事件处理。
   */
  virtual void OnColorFormatChanged(lv_event_t *e) {};

  /**
   * @brief 刷新请求时的事件处理函数。
   *
   * 该函数在收到刷新请求时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的刷新请求事件处理。
   */
  virtual void OnRefrRequest(lv_event_t *e) {};
  /**
 * @brief 刷新过程开始时的事件处理函数。
 *
 * 该函数在刷新过程开始时被调用，处理相关的事件逻辑。
 *
 * @param e 指向事件结构体的指针，包含事件的相关信息。
 *
 * @note 此函数为虚函数，可以在派生类中重写以实现自定义的刷新开始事件处理。
 */
  virtual void OnRefrStart(lv_event_t *e) {};

  /**
   * @brief 刷新过程准备就绪时的事件处理函数。
   *
   * 该函数在刷新过程准备就绪时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的刷新准备就绪事件处理。
   */
  virtual void OnRefrReady(lv_event_t *e) {};

  /**
   * @brief 渲染过程开始时的事件处理函数。
   *
   * 该函数在渲染过程开始时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的渲染开始事件处理。
   */
  virtual void OnRenderStart(lv_event_t *e) {};

  /**
   * @brief 渲染过程准备就绪时的事件处理函数。
   *
   * 该函数在渲染过程准备就绪时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的渲染准备就绪事件处理。
   */
  virtual void OnRenderReady(lv_event_t *e) {};

  /**
   * @brief 刷新过程开始时的事件处理函数。
   *
   * 该函数在刷新过程开始时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的刷新开始事件处理。
   */
  virtual void OnFlushStart(lv_event_t *e) {};

  /**
   * @brief 刷新操作完成时的事件处理函数。
   *
   * 该函数在刷新操作完成时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的刷新完成事件处理。
   */
  virtual void OnFlushFinish(lv_event_t *e) {};

  /**
   * @brief 等待刷新操作开始时的事件处理函数。
   *
   * 该函数在等待刷新操作开始时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的等待刷新开始事件处理。
   */
  virtual void OnFlushWaitStart(lv_event_t *e) {};

  /**
   * @brief 等待刷新操作完成时的事件处理函数。
   *
   * 该函数在等待刷新操作完成时被调用，处理相关的事件逻辑。
   *
   * @param e 指向事件结构体的指针，包含事件的相关信息。
   *
   * @note 此函数为虚函数，可以在派生类中重写以实现自定义的等待刷新完成事件处理。
   */
  virtual void OnFlushWaitFinish(lv_event_t *e) {};

};

} // namespace LVGLEx

#endif // LVGLEX_WIDGET_EVENT_BASE_H
