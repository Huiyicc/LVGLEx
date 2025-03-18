//
// Created by 19254 on 24-12-15.
//

#ifndef LVGLEX_WINDOW_H
#define LVGLEX_WINDOW_H

#include "misc/lv_types.h"
#include "widget/widget_base.h"
#include <memory>
#include <set>
#include <string>

namespace LVGLEx {

class WindowBase {
protected:
  struct Status {
    // 鼠标是否为按下
    bool MousePress = false;
    // 鼠标最后按下的位置
    lv_point_t MousePressPos = {0, 0};
    // 鼠标最后按下时全局(相对于屏幕)坐标
    lv_point_t MousePressGlobalPos = {0, 0};
    // 鼠标最后按下时窗口的坐标
    lv_point_t MousePressPosWindow = {0, 0};
  };

  lv_display_t *m_display = nullptr;
  std::set<std::unique_ptr<WidgetBase>> m_widgets;
  // 首次渲染完毕
  bool m_firstRender = false;
  // 是否显示
  bool m_show = false;
  // 窗口状态
  Status m_status;
  // 标题栏高度
  int m_titleBarHeight = 16;

  void handelEvent(void *eventPtr);
  void handelMouseEvent(void *eventPtr);
  void handelWindowMoveEvent(void *eventPtr);
  void handelFirstRender(void *eventPtr);

public:
  friend class WidgetBase;
  friend void handel_sdl_window_event(void *eventPtr);

  [[nodiscard]] DisplayPointer getDisplay() const;

  [[nodiscard]] WidgetPointer getScreenActive() const;
  virtual ~WindowBase() = default;

  void setData(const char *name, void *data) const;

  virtual void onShow() {};
  virtual void onCreate() {};
  virtual void onDelete() {};
  virtual void onLoadStart() {};
  virtual void onLoadEnd() {};

  void setTitle(const std::string &title) const;
  // void set_point(lv_point_t point);
};

class Window : public WindowBase {
  void register_event();

protected:
public:
  Window();
  ~Window() override;

  /**
   * @brief 从显示器获取窗口指针
   * @param display 显示器指针
   * @return 窗口指针
   * */
  static Window *getByDisplay(lv_display_t *display);

  void show();
};

} // namespace LVGLEx

#endif // LVGLEX_WINDOW_H
