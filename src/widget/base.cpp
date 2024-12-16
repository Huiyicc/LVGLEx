//
// Created by 19254 on 24-12-16.
//
#include <LVGLEx/widget/widget_base.h>
#include <core/lv_obj_pos.h>
#include <core/lv_obj_tree.h>

namespace LVGLEx {


WidgetBase::~WidgetBase() {
  if (m_obj) {
    lv_obj_delete(m_obj);
    m_obj = nullptr;
  }
}

WidgetBase *WidgetBase::AddWidget(std::unique_ptr<WidgetBase> &&widget) {
  auto [iter, _] = m_children.insert(std::move(widget));
  return iter->get();
}

WindowBase *WidgetBase::GetParent() const {
  return m_parent;
}



}// namespace LVGLEx