//
// Created by 19254 on 24-12-16.
//
#include <LVGLEx/widget/label.h>
#include <LVGLEx/window.h>
#include <widgets/label/lv_label.h>

namespace LVGLEx {

Label::Label() {

};

Label::~Label() {
}

Label *Label::create(WindowBase *parent) {
  auto r = std::make_unique<Label>();
  auto scr = parent->get_screen_active();
  r->m_parent = parent;
  r->m_obj = lv_label_create(scr);

  return dynamic_cast<Label *>(parent->add_widget(std::move(r)));
}

Label *Label::create(WidgetBase *parent) {
  auto r = std::make_unique<Label>();
  auto scr = parent->get_parent()->get_screen_active();
  r->m_parent = parent->get_parent();
  r->m_obj = lv_label_create(scr);
  return dynamic_cast<Label *>(parent->add_widget(std::move(r)));
};

Label *Label::set_text(const std::string &text) {
  lv_label_set_text(m_obj, text.c_str());
  return this;
};

}// namespace LVGLEx