//
// Created by 19254 on 25-4-6.
//
#include "LVGLEx/object/widget_base.h"

#include <misc/lv_event_private.h>

namespace LVGLEx {

WidgetEventDsc::WidgetEventDsc() {}
// WidgetEventDsc::WidgetEventDsc(lv_event_dsc_t *dsc, void* data_ptr) :
// m_dsc(dsc), m_data_ptr(data_ptr) {}

WidgetEvent::WidgetEvent(lv_event_t *e) : m_event(e) {};
void *WidgetEvent::userData() const { return m_event->user_data; };

} // namespace LVGLEx