//
// Created by 19254 on 24-12-16.
//
#include <LVGLEx/widget/label.h>
#include <LVGLEx/window.h>
#include <iostream>
#include <misc/lv_event_private.h>
#include <widgets/label/lv_label.h>

namespace LVGLEx {

Label::Label() {

};

Label::~Label() {
}

WIDGET_OBJ_CREATE_CPP(Label, lv_label_create);

Label *Label::setText(const std::string &text) {
  lv_label_set_text(m_obj.get(), text.c_str());

  return this;
};

}// namespace LVGLEx