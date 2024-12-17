//
// Created by 19254 on 24-12-15.
//

#ifndef LVGLEX_WINDOW_H
#define LVGLEX_WINDOW_H

#include "misc/lv_types.h"
#include "widget/widget_base.h"
#include <memory>
#include <string>
#include <set>

namespace LVGLEx {


class WindowBase {
protected:
  lv_display_t *m_display = nullptr;
  std::set<std::unique_ptr<WidgetBase>> m_widgets;

public:
  friend class WidgetBase;

  WidgetBase* add_widget(std::unique_ptr<WidgetBase> &&widget);

  lv_obj_t *get_screen_active() const;
  virtual ~WindowBase() = default;
  virtual void on_show() {};
  virtual void on_create() {};
  virtual void on_delete() {};
  virtual void on_load_start() {};
  virtual void on_load_end() {};

  void set_title(const std::string& title) const;

};

class Window : public WindowBase {
  void register_event();

protected:

public:
  Window();
  ~Window() override;


  void show();
};

}// namespace LVGLEx

#endif//LVGLEX_WINDOW_H
