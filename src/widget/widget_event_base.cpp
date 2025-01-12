//
// Created by 19254 on 24-12-22.
//
#include <LVGLEx/widget/widget_base.h>
#include <LVGLEx/widget/widget_event_base.h>
#include <misc/lv_event_private.h>
#include <misc/lv_types.h>

#define WIDGET_OBJ_EVENT_REGISTER(TARGET, TYPE, HANDEL, EVENT)                 \
  lv_obj_add_event_cb(                                                         \
      TARGET,                                                                  \
      [](lv_event_t *e) {                                                      \
        if (e && e->user_data) {                                               \
          static_cast<TYPE *>(e->user_data)->HANDEL(e);                        \
        }                                                                      \
      },                                                                       \
      EVENT, this);

namespace LVGLEx {

void WidgetEventBase::init(lv_obj_t *obj) {
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnPressed, LV_EVENT_PRESSED);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnPressing,
                            LV_EVENT_PRESSING);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnPressLost,
                            LV_EVENT_PRESS_LOST);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnShortClicked,
                            LV_EVENT_SHORT_CLICKED);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnSingleClicked,
                            LV_EVENT_SINGLE_CLICKED);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnDoubleClicked,
                            LV_EVENT_DOUBLE_CLICKED);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnTripleClicked,
                            LV_EVENT_TRIPLE_CLICKED);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnLongPressed,
                            LV_EVENT_LONG_PRESSED);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnLongPressedRepeat,
                            LV_EVENT_LONG_PRESSED_REPEAT);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnClicked, LV_EVENT_CLICKED);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnReleased,
                            LV_EVENT_RELEASED);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnScrollBegin,
                            LV_EVENT_SCROLL_BEGIN);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnScrollThrowBegin,
                            LV_EVENT_SCROLL_THROW_BEGIN);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnScrollEnd,
                            LV_EVENT_SCROLL_END);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnScroll, LV_EVENT_SCROLL);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnGesture, LV_EVENT_GESTURE);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnKey, LV_EVENT_KEY);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnRotary, LV_EVENT_ROTARY);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnFocused, LV_EVENT_FOCUSED);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnDefocused,
                            LV_EVENT_DEFOCUSED);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnLeave, LV_EVENT_LEAVE);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnHitTest, LV_EVENT_HIT_TEST);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnIndevReset,
                            LV_EVENT_INDEV_RESET);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnHoverOver,
                            LV_EVENT_HOVER_OVER);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnHoverLeave,
                            LV_EVENT_HOVER_LEAVE);

  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnCoverCheck,
                            LV_EVENT_COVER_CHECK);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnRefrExtDrawSize,
                            LV_EVENT_REFR_EXT_DRAW_SIZE);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnDrawMainBegin,
                            LV_EVENT_DRAW_MAIN_BEGIN);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnDrawMain,
                            LV_EVENT_DRAW_MAIN);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnDrawMainEnd,
                            LV_EVENT_DRAW_MAIN_END);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnDrawPostBegin,
                            LV_EVENT_DRAW_POST_BEGIN);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnDrawPost,
                            LV_EVENT_DRAW_POST);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnDrawPostEnd,
                            LV_EVENT_DRAW_POST_END);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnDrawTaskAdded,
                            LV_EVENT_DRAW_TASK_ADDED);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnCreate, LV_EVENT_CREATE);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnDelete, LV_EVENT_DELETE);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnChildChanged,
                            LV_EVENT_CHILD_CHANGED);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnChildCreated,
                            LV_EVENT_CHILD_CREATED);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnChildDeleted,
                            LV_EVENT_CHILD_DELETED);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnScreenUnloadStart,
                            LV_EVENT_SCREEN_UNLOAD_START);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnScreenLoadStart,
                            LV_EVENT_SCREEN_LOAD_START);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnScreenLoaded,
                            LV_EVENT_SCREEN_LOADED);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnScreenUnloaded,
                            LV_EVENT_SCREEN_UNLOADED);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnSizeChanged,
                            LV_EVENT_SIZE_CHANGED);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnStyleChanged,
                            LV_EVENT_STYLE_CHANGED);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnLayoutChanged,
                            LV_EVENT_LAYOUT_CHANGED);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnGetSelfSize,
                            LV_EVENT_GET_SELF_SIZE);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnInvalidateArea,
                            LV_EVENT_INVALIDATE_AREA);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnResolutionChanged,
                            LV_EVENT_RESOLUTION_CHANGED);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnColorFormatChanged,
                            LV_EVENT_COLOR_FORMAT_CHANGED);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnRefrRequest,
                            LV_EVENT_REFR_REQUEST);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnRefrStart,
                            LV_EVENT_REFR_START);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnRefrReady,
                            LV_EVENT_REFR_READY);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnRenderStart,
                            LV_EVENT_RENDER_START);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnRenderReady,
                            LV_EVENT_RENDER_READY);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnFlushStart,
                            LV_EVENT_FLUSH_START);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnFlushStart,
                            LV_EVENT_FLUSH_START);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnFlushFinish,
                            LV_EVENT_FLUSH_FINISH);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnFlushWaitStart,
                            LV_EVENT_FLUSH_WAIT_START);
  WIDGET_OBJ_EVENT_REGISTER(obj, WidgetEventBase, OnFlushWaitFinish,
                            LV_EVENT_FLUSH_WAIT_FINISH);
};

} // namespace LVGLEx