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

Label *Label::Create(WindowBase *parent) {
  auto r = std::make_unique<Label>();
  auto scr = parent->GetScreenActive();
  r->m_parent = parent;
  r->m_obj = lv_label_create(scr);

  return dynamic_cast<Label *>(parent->AddWidget(std::move(r)));
}

Label *Label::Create(WidgetBase *parent) {
  auto r = std::make_unique<Label>();
  auto scr = parent->GetParent()->GetScreenActive();
  r->m_parent = parent->GetParent();
  r->m_obj = lv_label_create(scr);
  return dynamic_cast<Label *>(parent->AddWidget(std::move(r)));
};

Label *Label::SetText(const std::string &text) {
  lv_label_set_text(m_obj, text.c_str());
  return this;
};

}// namespace LVGLEx