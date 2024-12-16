//
// Created by 19254 on 24-12-15.
//

#ifndef LVGLEX_WINDOW_H
#define LVGLEX_WINDOW_H

#include "misc/lv_types.h"
#include "widget/widget_base.h"
#include <memory>
#include <set>

namespace LVGLEx {


class WindowBase {
protected:
  lv_display_t *m_display = nullptr;
  std::set<std::unique_ptr<WidgetBase>> m_widgets;

public:
  friend class WidgetBase;

  WidgetBase* AddWidget(std::unique_ptr<WidgetBase> &&widget);

  lv_obj_t *GetScreenActive() const;
  virtual ~WindowBase() = default;
  virtual void OnShow() {};
  virtual void OnCreate() {};
  virtual void OnDelete() {};
  virtual void OnLoadStart() {};
  virtual void OnLoadEnd() {};
};

class Window : public WindowBase {
  void registerEvent();

protected:

public:
  Window();
  ~Window() override;


  void Show();
};

}// namespace LVGLEx

#endif//LVGLEX_WINDOW_H
