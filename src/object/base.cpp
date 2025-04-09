//
// Created by 19254 on 24-12-16.
//
#include <LVGLEx/container/layer.h>
#include <LVGLEx/container/window.h>
#include <LVGLEx/misc/area.h>
#include <LVGLEx/misc/matrix.h>
#include <LVGLEx/misc/point.h>
#include <LVGLEx/misc/style.h>
#include <LVGLEx/object/widget_base.h>
#include <core/lv_obj_pos.h>
#include <core/lv_obj_style_private.h>
#include <core/lv_obj_tree.h>
#include <iostream>
#include <misc/lv_event_private.h>
#include <optional>

namespace LVGLEx {
WidgetBase::WidgetBase() {

};

WidgetBase::~WidgetBase() {
  if (m_obj.get()) {
    m_obj.clean();
  }
}
void WidgetBase::init() {
  if (m_obj.get()) {
    WidgetEventBase::init(m_obj.get());
  }
}

lv_obj_t *WidgetBase::getObj() const { return m_obj.get(); };

WidgetPointer WidgetBase::release() { return WidgetPointer(m_obj.release()); };

WidgetBase WidgetBase::makeFromPtr(lv_obj_t *ptr) {
  auto w = WidgetBase();
  w.m_obj = WidgetPointer::makeQuote(ptr);
  return w;
}

WidgetBase::WidgetBase(WidgetBase &&other) noexcept {
  *this = std::move(other);
}

WidgetBase &WidgetBase::operator=(WidgetBase &&other) noexcept {
  m_obj = std::move(other.m_obj);
  return *this;
}

std::optional<WidgetBase> WidgetBase::getParent() const {
  return makeFromPtr(lv_obj_get_parent(m_obj.get()));
}

WindowBase *WidgetBase::getWindow() const {
  return Window::getByDisplay(lv_obj_get_display(m_obj.get()));
}

WidgetPointer WidgetBase::getScreenActive() const {
  return WidgetPointer::makeQuote(lv_obj_get_screen(m_obj.get()));
}

void WidgetBase::setPos(const int32_t x, const int32_t y) const {
  lv_obj_set_pos(m_obj.get(), x, y);
}

int WidgetBase::addEvent(lv_event_code_t filter,
                         const EventCallBackFunc &func,
                         void *user_data) {
  auto l = std::make_shared<WidgetEventDsc>();
  l->m_data_ptr = user_data;
  if (func) {
    l->m_func = func;
    l->m_dsc = lv_obj_add_event_cb(
        m_obj.get(),
        [](lv_event_t *e) {
          WidgetEvent event(e);
          static_cast<WidgetEventDsc *>(e->user_data)->m_func(event);
        },
        filter, l.get());
  }
  int id = m_event_dsc.empty() ? 0 : int(m_event_dsc.begin()->first) + 1;
  m_event_dsc[id] = l;
  return id;
}

int WidgetBase::addEvent(const EventCallBackFunc &func,
                         void *user_data) {
  auto l = std::make_shared<WidgetEventDsc>();
  l->m_data_ptr = user_data;
  if (func) {
    l->m_func = func;
    l->m_dsc = lv_obj_add_event_cb(
        m_obj.get(),
        [](lv_event_t *e) {
          WidgetEvent event(e);
          static_cast<WidgetEventDsc *>(e->user_data)->m_func(event);
        },
        LV_EVENT_ALL, l.get());
  }
  int id = m_event_dsc.empty() ? 0 : int(m_event_dsc.begin()->first) + 1;
  m_event_dsc[id] = l;
  return id;
}

void WidgetBase::removeEvent(int evebt_id) {
  auto iter = m_event_dsc.find(evebt_id);
  if (iter != m_event_dsc.end()) {
    auto dsc = iter->second;
    lv_obj_remove_event_dsc(m_obj.get(), dsc->m_dsc);
    dsc->m_dsc = nullptr;
    m_event_dsc.erase(evebt_id);
  }
}

void WidgetBase::setX(const int32_t x) const { lv_obj_set_x(m_obj.get(), x); }

void WidgetBase::setY(const int32_t y) const { lv_obj_set_y(m_obj.get(), y); }

void WidgetBase::setSize(const int32_t w, const int32_t h) const {
  lv_obj_set_size(m_obj.get(), w, h);
}

void WidgetBase::setWidth(const int32_t w) const {
  lv_obj_set_width(m_obj.get(), w);
}

void WidgetBase::setHeight(const int32_t h) const {
  lv_obj_set_height(m_obj.get(), h);
}

void WidgetBase::setContentWidth(int32_t w) const {
  lv_obj_set_content_width(m_obj.get(), w);
}

void WidgetBase::setContentHeight(int32_t h) const {
  lv_obj_set_content_height(m_obj.get(), h);
}

void WidgetBase::setLayout(uint32_t layout) const {
  lv_obj_set_layout(m_obj.get(), layout);
}

void WidgetBase::markLayoutAsDirty() const {
  lv_obj_mark_layout_as_dirty(m_obj.get());
}

void WidgetBase::updateLayout() const { lv_obj_update_layout(m_obj.get()); }

void WidgetBase::setAlign(lv_align_t align) const {
  lv_obj_set_align(m_obj.get(), align);
}

void WidgetBase::align(lv_align_t align, int32_t x_ofs, int32_t y_ofs) const {
  lv_obj_align(m_obj.get(), align, x_ofs, y_ofs);
}

void WidgetBase::alignTo(const WidgetPointer &base, lv_align_t align,
                         int32_t x_ofs, int32_t y_ofs) const {
  lv_obj_align_to(m_obj.get(), base.get(), align, x_ofs, y_ofs);
}

void WidgetBase::center() const { lv_obj_center(m_obj.get()); }

void WidgetBase::setTransform(const Matrix &matrix) const {
  lv_obj_set_transform(m_obj.get(), matrix.get());
}

void WidgetBase::resetTransform() const { lv_obj_reset_transform(m_obj.get()); }

Area WidgetBase::getCoords() const {
  Area res;
  lv_obj_get_coords(m_obj.get(), res.getPtr());
  return res;
}

Area WidgetBase::getContentCoords() const {
  Area res;
  lv_obj_get_content_coords(m_obj.get(), res.getPtr());
  return res;
}

void WidgetBase::refrPos() const { lv_obj_refr_pos(m_obj.get()); }

void WidgetBase::moveTo(int32_t x, int32_t y) const {
  lv_obj_move_to(m_obj.get(), x, y);
}

void WidgetBase::moveChildrenBy(int32_t x_diff, int32_t y_diff,
                                bool ignore_floating) const {
  lv_obj_move_children_by(m_obj.get(), x_diff, y_diff, ignore_floating);
}

Point WidgetBase::transformPoint(lv_obj_point_transform_flag_t flags) const {
  Point p;
  lv_obj_transform_point(m_obj.get(), p.getPtr(), flags);
  return p;
}

void WidgetBase::transformPointArray(
    std::vector<Point> &points, lv_obj_point_transform_flag_t flags) const {
  int32_t count = points.size();
  std::vector<lv_point_t> points_c(count);
  for (int i = 0; i < count; i++) {
    points_c[i] = *points[i].get();
  }
  lv_obj_transform_point_array(m_obj.get(), points_c.data(), count, flags);
  for (int i = 0; i < count; i++) {
    points[i] = points_c[i];
  }
}

Area WidgetBase::getTransformedArea(lv_obj_point_transform_flag_t flags) const {
  Area area;
  lv_obj_get_transformed_area(m_obj.get(), area.getPtr(), flags);
  return area;
}

void WidgetBase::invalidateArea(const Area &area) const {
  lv_obj_invalidate_area(m_obj.get(), area.get());
}

void WidgetBase::invalidate() const { lv_obj_invalidate(m_obj.get()); }

void WidgetBase::setExtClickArea(int32_t size) const {
  lv_obj_set_ext_click_area(m_obj.get(), size);
}

Area WidgetBase::getClickArea() const {
  Area area;
  lv_obj_get_click_area(m_obj.get(), area.getPtr());
  return area;
}

void WidgetBase::moveForeground() const {
  lv_obj_move_foreground(m_obj.get());
};

void WidgetBase::addFlag(const lv_obj_flag_t f) const {
  lv_obj_add_flag(m_obj.get(), f);
};

void WidgetBase::removeFlag(const lv_obj_flag_t f) const {
  lv_obj_remove_flag(m_obj.get(), f);
};

void WidgetBase::updateFlag(const lv_obj_flag_t f, const bool v) const {
  lv_obj_update_flag(m_obj.get(), f, v);
}

void WidgetBase::addState(lv_state_t state) const {
  lv_obj_add_state(m_obj.get(), state);
}

void WidgetBase::removeState(lv_state_t state) const {
  lv_obj_remove_state(m_obj.get(), state);
}

void WidgetBase::setState(lv_state_t state, bool v) const {
  lv_obj_set_state(m_obj.get(), state, v);
}

void WidgetBase::setUserData(void *user_data) const {
  lv_obj_set_user_data(m_obj.get(), user_data);
}

void WidgetBase::allocateSpecAttr() const {
  lv_obj_allocate_spec_attr(m_obj.get());
}

void WidgetBase::classInitObj() const { lv_obj_class_init_obj(m_obj.get()); }

void WidgetBase::initDrawRectDsc(lv_part_t part,
                                 lv_draw_rect_dsc_t *draw_dsc) const {
  lv_obj_init_draw_rect_dsc(m_obj.get(), part, draw_dsc);
}

void WidgetBase::initDrawLabelDsc(lv_part_t part,
                                  lv_draw_label_dsc_t *draw_dsc) const {
  lv_obj_init_draw_label_dsc(m_obj.get(), part, draw_dsc);
}

void WidgetBase::initDrawImageDsc(lv_part_t part,
                                  lv_draw_image_dsc_t *draw_dsc) const {
  lv_obj_init_draw_image_dsc(m_obj.get(), part, draw_dsc);
}

void WidgetBase::initDrawLineDsc(lv_part_t part,
                                 lv_draw_line_dsc_t *draw_dsc) const {
  lv_obj_init_draw_line_dsc(m_obj.get(), part, draw_dsc);
}

void WidgetBase::initDrawArcDsc(lv_part_t part,
                                lv_draw_arc_dsc_t *draw_dsc) const {
  lv_obj_init_draw_arc_dsc(m_obj.get(), part, draw_dsc);
}

void WidgetBase::refreshExtDrawSize() const {
  lv_obj_refresh_ext_draw_size(m_obj.get());
}

// void WidgetBase::func_name_end( int32_t size) const {
//   func_prefixfunc_name_end(m_obj , size);
// }
//
// void WidgetBase::func_name_end( lv_cover_res_t res) const {
//   func_prefixfunc_name_end(m_obj , res);
// }

void WidgetBase::setScrollbarMode(lv_scrollbar_mode_t mode) const {
  lv_obj_set_scrollbar_mode(m_obj.get(), mode);
}

void WidgetBase::setScrollDir(lv_dir_t dir) const {
  lv_obj_set_scroll_dir(m_obj.get(), dir);
}

void WidgetBase::setScrollSnapX(lv_scroll_snap_t align) const {
  lv_obj_set_scroll_snap_x(m_obj.get(), align);
}

void WidgetBase::setScrollSnapY(lv_scroll_snap_t align) const {
  lv_obj_set_scroll_snap_y(m_obj.get(), align);
}

void WidgetBase::getScrollEnd(lv_point_t *end) const {
  lv_obj_get_scroll_end(m_obj.get(), end);
}

void WidgetBase::scrollBy(int32_t dx, int32_t dy,
                          lv_anim_enable_t anim_en) const {
  lv_obj_scroll_by(m_obj.get(), dx, dy, anim_en);
}

void WidgetBase::scrollByBounded(int32_t dx, int32_t dy,
                                 lv_anim_enable_t anim_en) const {
  lv_obj_scroll_by_bounded(m_obj.get(), dx, dy, anim_en);
}

void WidgetBase::scrollTo(int32_t x, int32_t y,
                          lv_anim_enable_t anim_en) const {
  lv_obj_scroll_to(m_obj.get(), x, y, anim_en);
}

void WidgetBase::scrollToX(int32_t x, lv_anim_enable_t anim_en) const {
  lv_obj_scroll_to_x(m_obj.get(), x, anim_en);
}

void WidgetBase::scrollToY(int32_t y, lv_anim_enable_t anim_en) const {
  lv_obj_scroll_to_y(m_obj.get(), y, anim_en);
}

void WidgetBase::scrollToView(lv_anim_enable_t anim_en) const {
  lv_obj_scroll_to_view(m_obj.get(), anim_en);
}

void WidgetBase::scrollToViewRecursive(lv_anim_enable_t anim_en) const {
  lv_obj_scroll_to_view_recursive(m_obj.get(), anim_en);
}

void WidgetBase::updateSnap(lv_anim_enable_t anim_en) const {
  lv_obj_update_snap(m_obj.get(), anim_en);
}

void WidgetBase::getScrollbarArea(Area &hor, Area &ver) const {
  lv_obj_get_scrollbar_area(m_obj.get(), hor.getPtr(), ver.getPtr());
}

void WidgetBase::scrollbarInvalidate() const {
  lv_obj_scrollbar_invalidate(m_obj.get());
}

void WidgetBase::readjustScroll(lv_anim_enable_t anim_en) const {
  lv_obj_readjust_scroll(m_obj.get(), anim_en);
}

void WidgetBase::addStyle(const Style &style,
                          lv_style_selector_t selector) const {
  lv_obj_add_style(m_obj.get(), style.get(), selector);
}

void WidgetBase::removeStyle(const Style &style,
                             lv_style_selector_t selector) const {
  lv_obj_remove_style(m_obj.get(), style.get(), selector);
}

void WidgetBase::removeStyleAll() const {
  lv_obj_remove_style_all(m_obj.get());
}

void WidgetBase::reportStyleChange(Style &style) {
  lv_obj_report_style_change(style.getPtr());
}

void WidgetBase::refreshStyle(lv_part_t part, lv_style_prop_t prop) const {
  lv_obj_refresh_style(m_obj.get(), part, prop);
}

void WidgetBase::enableStyleRefresh() const {
  lv_obj_enable_style_refresh(m_obj.get());
}

void WidgetBase::setLocalStyleProp(lv_style_prop_t prop, lv_style_value_t value,
                                   lv_style_selector_t selector) const {
  lv_obj_set_local_style_prop(m_obj.get(), prop, value, selector);
}

void WidgetBase::fadeIn(uint32_t time, uint32_t delay) const {
  lv_obj_fade_in(m_obj.get(), time, delay);
}

void WidgetBase::fadeOut(uint32_t time, uint32_t delay) const {
  lv_obj_fade_out(m_obj.get(), time, delay);
}

void WidgetBase::setStylePadAll(int32_t value,
                                lv_style_selector_t selector) const {
  lv_obj_set_style_pad_all(m_obj.get(), value, selector);
}

void WidgetBase::setStylePadHor(int32_t value,
                                lv_style_selector_t selector) const {
  lv_obj_set_style_pad_hor(m_obj.get(), value, selector);
}

void WidgetBase::setStylePadVer(int32_t value,
                                lv_style_selector_t selector) const {
  lv_obj_set_style_pad_ver(m_obj.get(), value, selector);
}

void WidgetBase::setStyleMarginAll(int32_t value,
                                   lv_style_selector_t selector) const {
  lv_obj_set_style_margin_all(m_obj.get(), value, selector);
}

void WidgetBase::setStyleMarginHor(int32_t value,
                                   lv_style_selector_t selector) const {
  lv_obj_set_style_margin_hor(m_obj.get(), value, selector);
}

void WidgetBase::setStyleMarginVer(int32_t value,
                                   lv_style_selector_t selector) const {
  lv_obj_set_style_margin_ver(m_obj.get(), value, selector);
}

void WidgetBase::setStylePadGap(int32_t value,
                                lv_style_selector_t selector) const {
  lv_obj_set_style_pad_gap(m_obj.get(), value, selector);
}

void WidgetBase::setStyleSize(int32_t width, int32_t height,
                              lv_style_selector_t selector) const {
  lv_obj_set_style_size(m_obj.get(), width, height, selector);
}

void WidgetBase::setStyleTransformScale(int32_t value,
                                        lv_style_selector_t selector) const {
  lv_obj_set_style_transform_scale(m_obj.get(), value, selector);
}

void WidgetBase::setStyleWidth(int32_t value,
                               lv_style_selector_t selector) const {
  lv_obj_set_style_width(m_obj.get(), value, selector);
}

void WidgetBase::setStyleMinWidth(int32_t value,
                                  lv_style_selector_t selector) const {
  lv_obj_set_style_min_width(m_obj.get(), value, selector);
}

void WidgetBase::setStyleMaxWidth(int32_t value,
                                  lv_style_selector_t selector) const {
  lv_obj_set_style_max_width(m_obj.get(), value, selector);
}

void WidgetBase::setStyleHeight(int32_t value,
                                lv_style_selector_t selector) const {
  lv_obj_set_style_height(m_obj.get(), value, selector);
}

void WidgetBase::setStyleMinHeight(int32_t value,
                                   lv_style_selector_t selector) const {
  lv_obj_set_style_min_height(m_obj.get(), value, selector);
}

void WidgetBase::setStyleMaxHeight(int32_t value,
                                   lv_style_selector_t selector) const {
  lv_obj_set_style_max_height(m_obj.get(), value, selector);
}

void WidgetBase::setStyleLength(int32_t value,
                                lv_style_selector_t selector) const {
  lv_obj_set_style_length(m_obj.get(), value, selector);
}

void WidgetBase::setStyleX(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_x(m_obj.get(), value, selector);
}

void WidgetBase::setStyleY(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_y(m_obj.get(), value, selector);
}

void WidgetBase::setStyleAlign(lv_align_t value,
                               lv_style_selector_t selector) const {
  lv_obj_set_style_align(m_obj.get(), value, selector);
}

void WidgetBase::setStyleTransformWidth(int32_t value,
                                        lv_style_selector_t selector) const {
  lv_obj_set_style_transform_width(m_obj.get(), value, selector);
}

void WidgetBase::setStyleTransformHeight(int32_t value,
                                         lv_style_selector_t selector) const {
  lv_obj_set_style_transform_height(m_obj.get(), value, selector);
}

void WidgetBase::setStyleTranslateX(int32_t value,
                                    lv_style_selector_t selector) const {
  lv_obj_set_style_translate_x(m_obj.get(), value, selector);
}

void WidgetBase::setStyleTranslateY(int32_t value,
                                    lv_style_selector_t selector) const {
  lv_obj_set_style_translate_y(m_obj.get(), value, selector);
}

void WidgetBase::setStyleTranslateRadial(int32_t value,
                                         lv_style_selector_t selector) const {
  lv_obj_set_style_translate_radial(m_obj.get(), value, selector);
}

void WidgetBase::setStyleTransformScaleX(int32_t value,
                                         lv_style_selector_t selector) const {
  lv_obj_set_style_transform_scale_x(m_obj.get(), value, selector);
}

void WidgetBase::setStyleTransformScaleY(int32_t value,
                                         lv_style_selector_t selector) const {
  lv_obj_set_style_transform_scale_y(m_obj.get(), value, selector);
}

void WidgetBase::setStyleTransformRotation(int32_t value,
                                           lv_style_selector_t selector) const {
  lv_obj_set_style_transform_rotation(m_obj.get(), value, selector);
}

void WidgetBase::setStyleTransformPivotX(int32_t value,
                                         lv_style_selector_t selector) const {
  lv_obj_set_style_transform_pivot_x(m_obj.get(), value, selector);
}

void WidgetBase::setStyleTransformPivotY(int32_t value,
                                         lv_style_selector_t selector) const {
  lv_obj_set_style_transform_pivot_y(m_obj.get(), value, selector);
}

void WidgetBase::setStyleTransformSkewX(int32_t value,
                                        lv_style_selector_t selector) const {
  lv_obj_set_style_transform_skew_x(m_obj.get(), value, selector);
}

void WidgetBase::setStyleTransformSkewY(int32_t value,
                                        lv_style_selector_t selector) const {
  lv_obj_set_style_transform_skew_y(m_obj.get(), value, selector);
}

void WidgetBase::setStylePadTop(int32_t value,
                                lv_style_selector_t selector) const {
  lv_obj_set_style_pad_top(m_obj.get(), value, selector);
}

void WidgetBase::setStylePadBottom(int32_t value,
                                   lv_style_selector_t selector) const {
  lv_obj_set_style_pad_bottom(m_obj.get(), value, selector);
}

void WidgetBase::setStylePadLeft(int32_t value,
                                 lv_style_selector_t selector) const {
  lv_obj_set_style_pad_left(m_obj.get(), value, selector);
}

void WidgetBase::setStylePadRight(int32_t value,
                                  lv_style_selector_t selector) const {
  lv_obj_set_style_pad_right(m_obj.get(), value, selector);
}

void WidgetBase::setStylePadRow(int32_t value,
                                lv_style_selector_t selector) const {
  lv_obj_set_style_pad_row(m_obj.get(), value, selector);
}

void WidgetBase::setStylePadColumn(int32_t value,
                                   lv_style_selector_t selector) const {
  lv_obj_set_style_pad_column(m_obj.get(), value, selector);
}

void WidgetBase::setStylePadRadial(int32_t value,
                                   lv_style_selector_t selector) const {
  lv_obj_set_style_pad_radial(m_obj.get(), value, selector);
}

void WidgetBase::setStyleMarginTop(int32_t value,
                                   lv_style_selector_t selector) const {
  lv_obj_set_style_margin_top(m_obj.get(), value, selector);
}

void WidgetBase::setStyleMarginBottom(int32_t value,
                                      lv_style_selector_t selector) const {
  lv_obj_set_style_margin_bottom(m_obj.get(), value, selector);
}

void WidgetBase::setStyleMarginLeft(int32_t value,
                                    lv_style_selector_t selector) const {
  lv_obj_set_style_margin_left(m_obj.get(), value, selector);
}

void WidgetBase::setStyleMarginRight(int32_t value,
                                     lv_style_selector_t selector) const {
  lv_obj_set_style_margin_right(m_obj.get(), value, selector);
}

void WidgetBase::setStyleBgColor(lv_color_t value,
                                 lv_style_selector_t selector) const {
  lv_obj_set_style_bg_color(m_obj.get(), value, selector);
}

void WidgetBase::setStyleBgOpa(lv_opa_t value,
                               lv_style_selector_t selector) const {
  lv_obj_set_style_bg_opa(m_obj.get(), value, selector);
}

void WidgetBase::setStyleBgGradColor(lv_color_t value,
                                     lv_style_selector_t selector) const {
  lv_obj_set_style_bg_grad_color(m_obj.get(), value, selector);
}

void WidgetBase::setStyleBgGradDir(lv_grad_dir_t value,
                                   lv_style_selector_t selector) const {
  lv_obj_set_style_bg_grad_dir(m_obj.get(), value, selector);
}

void WidgetBase::setStyleBgMainStop(int32_t value,
                                    lv_style_selector_t selector) const {
  lv_obj_set_style_bg_main_stop(m_obj.get(), value, selector);
}

void WidgetBase::setStyleBgGradStop(int32_t value,
                                    lv_style_selector_t selector) const {
  lv_obj_set_style_bg_grad_stop(m_obj.get(), value, selector);
}

void WidgetBase::setStyleBgMainOpa(lv_opa_t value,
                                   lv_style_selector_t selector) const {
  lv_obj_set_style_bg_main_opa(m_obj.get(), value, selector);
}

void WidgetBase::setStyleBgGradOpa(lv_opa_t value,
                                   lv_style_selector_t selector) const {
  lv_obj_set_style_bg_grad_opa(m_obj.get(), value, selector);
}

void WidgetBase::setStyleBgGrad(const lv_grad_dsc_t *value,
                                lv_style_selector_t selector) const {
  lv_obj_set_style_bg_grad(m_obj.get(), value, selector);
}

void WidgetBase::setStyleBgImageSrc(const void *value,
                                    lv_style_selector_t selector) const {
  lv_obj_set_style_bg_image_src(m_obj.get(), value, selector);
}

void WidgetBase::setStyleBgImageOpa(lv_opa_t value,
                                    lv_style_selector_t selector) const {
  lv_obj_set_style_bg_image_opa(m_obj.get(), value, selector);
}

void WidgetBase::setStyleBgImageRecolor(lv_color_t value,
                                        lv_style_selector_t selector) const {
  lv_obj_set_style_bg_image_recolor(m_obj.get(), value, selector);
}

void WidgetBase::setStyleBgImageRecolorOpa(lv_opa_t value,
                                           lv_style_selector_t selector) const {
  lv_obj_set_style_bg_image_recolor_opa(m_obj.get(), value, selector);
}

void WidgetBase::setStyleBgImageTiled(bool value,
                                      lv_style_selector_t selector) const {
  lv_obj_set_style_bg_image_tiled(m_obj.get(), value, selector);
}

void WidgetBase::setStyleBorderColor(lv_color_t value,
                                     lv_style_selector_t selector) const {
  lv_obj_set_style_border_color(m_obj.get(), value, selector);
}

void WidgetBase::setStyleBorderOpa(lv_opa_t value,
                                   lv_style_selector_t selector) const {
  lv_obj_set_style_border_opa(m_obj.get(), value, selector);
}

void WidgetBase::setStyleBorderWidth(int32_t value,
                                     lv_style_selector_t selector) const {
  lv_obj_set_style_border_width(m_obj.get(), value, selector);
}

void WidgetBase::setStyleBorderSide(lv_border_side_t value,
                                    lv_style_selector_t selector) const {
  lv_obj_set_style_border_side(m_obj.get(), value, selector);
}

void WidgetBase::setStyleBorderPost(bool value,
                                    lv_style_selector_t selector) const {
  lv_obj_set_style_border_post(m_obj.get(), value, selector);
}

void WidgetBase::setStyleOutlineWidth(int32_t value,
                                      lv_style_selector_t selector) const {
  lv_obj_set_style_outline_width(m_obj.get(), value, selector);
}

void WidgetBase::setStyleOutlineColor(lv_color_t value,
                                      lv_style_selector_t selector) const {
  lv_obj_set_style_outline_color(m_obj.get(), value, selector);
}

void WidgetBase::setStyleOutlineOpa(lv_opa_t value,
                                    lv_style_selector_t selector) const {
  lv_obj_set_style_outline_opa(m_obj.get(), value, selector);
}

void WidgetBase::setStyleOutlinePad(int32_t value,
                                    lv_style_selector_t selector) const {
  lv_obj_set_style_outline_pad(m_obj.get(), value, selector);
}

void WidgetBase::setStyleShadowWidth(int32_t value,
                                     lv_style_selector_t selector) const {
  lv_obj_set_style_shadow_width(m_obj.get(), value, selector);
}

void WidgetBase::setStyleShadowOffsetX(int32_t value,
                                       lv_style_selector_t selector) const {
  lv_obj_set_style_shadow_offset_x(m_obj.get(), value, selector);
}

void WidgetBase::setStyleShadowOffsetY(int32_t value,
                                       lv_style_selector_t selector) const {
  lv_obj_set_style_shadow_offset_y(m_obj.get(), value, selector);
}

void WidgetBase::setStyleShadowSpread(int32_t value,
                                      lv_style_selector_t selector) const {
  lv_obj_set_style_shadow_spread(m_obj.get(), value, selector);
}

void WidgetBase::setStyleShadowColor(lv_color_t value,
                                     lv_style_selector_t selector) const {
  lv_obj_set_style_shadow_color(m_obj.get(), value, selector);
}

void WidgetBase::setStyleShadowOpa(lv_opa_t value,
                                   lv_style_selector_t selector) const {
  lv_obj_set_style_shadow_opa(m_obj.get(), value, selector);
}

void WidgetBase::setStyleImageOpa(lv_opa_t value,
                                  lv_style_selector_t selector) const {
  lv_obj_set_style_image_opa(m_obj.get(), value, selector);
}

void WidgetBase::setStyleImageRecolor(lv_color_t value,
                                      lv_style_selector_t selector) const {
  lv_obj_set_style_image_recolor(m_obj.get(), value, selector);
}

void WidgetBase::setStyleImageRecolorOpa(lv_opa_t value,
                                         lv_style_selector_t selector) const {
  lv_obj_set_style_image_recolor_opa(m_obj.get(), value, selector);
}

void WidgetBase::setStyleLineWidth(int32_t value,
                                   lv_style_selector_t selector) const {
  lv_obj_set_style_line_width(m_obj.get(), value, selector);
}

void WidgetBase::setStyleLineDashWidth(int32_t value,
                                       lv_style_selector_t selector) const {
  lv_obj_set_style_line_dash_width(m_obj.get(), value, selector);
}

void WidgetBase::setStyleLineDashGap(int32_t value,
                                     lv_style_selector_t selector) const {
  lv_obj_set_style_line_dash_gap(m_obj.get(), value, selector);
}

void WidgetBase::setStyleLineRounded(bool value,
                                     lv_style_selector_t selector) const {
  lv_obj_set_style_line_rounded(m_obj.get(), value, selector);
}

void WidgetBase::setStyleLineColor(lv_color_t value,
                                   lv_style_selector_t selector) const {
  lv_obj_set_style_line_color(m_obj.get(), value, selector);
}

void WidgetBase::setStyleLineOpa(lv_opa_t value,
                                 lv_style_selector_t selector) const {
  lv_obj_set_style_line_opa(m_obj.get(), value, selector);
}

void WidgetBase::setStyleArcWidth(int32_t value,
                                  lv_style_selector_t selector) const {
  lv_obj_set_style_arc_width(m_obj.get(), value, selector);
}

void WidgetBase::setStyleArcRounded(bool value,
                                    lv_style_selector_t selector) const {
  lv_obj_set_style_arc_rounded(m_obj.get(), value, selector);
}

void WidgetBase::setStyleArcColor(lv_color_t value,
                                  lv_style_selector_t selector) const {
  lv_obj_set_style_arc_color(m_obj.get(), value, selector);
}

void WidgetBase::setStyleArcOpa(lv_opa_t value,
                                lv_style_selector_t selector) const {
  lv_obj_set_style_arc_opa(m_obj.get(), value, selector);
}

void WidgetBase::setStyleArcImageSrc(const void *value,
                                     lv_style_selector_t selector) const {
  lv_obj_set_style_arc_image_src(m_obj.get(), value, selector);
}

void WidgetBase::setStyleTextColor(lv_color_t value,
                                   lv_style_selector_t selector) const {
  lv_obj_set_style_text_color(m_obj.get(), value, selector);
}

void WidgetBase::setStyleTextOpa(lv_opa_t value,
                                 lv_style_selector_t selector) const {
  lv_obj_set_style_text_opa(m_obj.get(), value, selector);
}

void WidgetBase::setStyleTextFont(const lv_font_t *value,
                                  lv_style_selector_t selector) const {
  lv_obj_set_style_text_font(m_obj.get(), value, selector);
}

void WidgetBase::setStyleTextLetterSpace(int32_t value,
                                         lv_style_selector_t selector) const {
  lv_obj_set_style_text_letter_space(m_obj.get(), value, selector);
}

void WidgetBase::setStyleTextLineSpace(int32_t value,
                                       lv_style_selector_t selector) const {
  lv_obj_set_style_text_line_space(m_obj.get(), value, selector);
}

void WidgetBase::setStyleTextDecor(lv_text_decor_t value,
                                   lv_style_selector_t selector) const {
  lv_obj_set_style_text_decor(m_obj.get(), value, selector);
}

void WidgetBase::setStyleTextAlign(lv_text_align_t value,
                                   lv_style_selector_t selector) const {
  lv_obj_set_style_text_align(m_obj.get(), value, selector);
}

void WidgetBase::setStyleRadius(int32_t value,
                                lv_style_selector_t selector) const {
  lv_obj_set_style_radius(m_obj.get(), value, selector);
}

void WidgetBase::setStyleRadialOffset(int32_t value,
                                      lv_style_selector_t selector) const {
  lv_obj_set_style_radial_offset(m_obj.get(), value, selector);
}

void WidgetBase::setStyleClipCorner(bool value,
                                    lv_style_selector_t selector) const {
  lv_obj_set_style_clip_corner(m_obj.get(), value, selector);
}

void WidgetBase::setStyleOpa(lv_opa_t value,
                             lv_style_selector_t selector) const {
  lv_obj_set_style_opa(m_obj.get(), value, selector);
}

void WidgetBase::setStyleOpaLayered(lv_opa_t value,
                                    lv_style_selector_t selector) const {
  lv_obj_set_style_opa_layered(m_obj.get(), value, selector);
}

void WidgetBase::setStyleColorFilterDsc(const lv_color_filter_dsc_t *value,
                                        lv_style_selector_t selector) const {
  lv_obj_set_style_color_filter_dsc(m_obj.get(), value, selector);
}

void WidgetBase::setStyleColorFilterOpa(lv_opa_t value,
                                        lv_style_selector_t selector) const {
  lv_obj_set_style_color_filter_opa(m_obj.get(), value, selector);
}

void WidgetBase::setStyleAnim(const lv_anim_t *value,
                              lv_style_selector_t selector) const {
  lv_obj_set_style_anim(m_obj.get(), value, selector);
}

void WidgetBase::setStyleAnimDuration(uint32_t value,
                                      lv_style_selector_t selector) const {
  lv_obj_set_style_anim_duration(m_obj.get(), value, selector);
}

void WidgetBase::setStyleTransition(const lv_style_transition_dsc_t *value,
                                    lv_style_selector_t selector) const {
  lv_obj_set_style_transition(m_obj.get(), value, selector);
}

void WidgetBase::setStyleBlendMode(lv_blend_mode_t value,
                                   lv_style_selector_t selector) const {
  lv_obj_set_style_blend_mode(m_obj.get(), value, selector);
}

void WidgetBase::setStyleLayout(uint16_t value,
                                lv_style_selector_t selector) const {
  lv_obj_set_style_layout(m_obj.get(), value, selector);
}

void WidgetBase::setStyleBaseDir(lv_base_dir_t value,
                                 lv_style_selector_t selector) const {
  lv_obj_set_style_base_dir(m_obj.get(), value, selector);
}

void WidgetBase::setStyleBitmapMaskSrc(const void *value,
                                       lv_style_selector_t selector) const {
  lv_obj_set_style_bitmap_mask_src(m_obj.get(), value, selector);
}

void WidgetBase::setStyleRotarySensitivity(uint32_t value,
                                           lv_style_selector_t selector) const {
  lv_obj_set_style_rotary_sensitivity(m_obj.get(), value, selector);
}

void WidgetBase::setStyleFlexFlow(lv_flex_flow_t value,
                                  lv_style_selector_t selector) const {
  lv_obj_set_style_flex_flow(m_obj.get(), value, selector);
}

void WidgetBase::setStyleFlexMainPlace(lv_flex_align_t value,
                                       lv_style_selector_t selector) const {
  lv_obj_set_style_flex_main_place(m_obj.get(), value, selector);
}

void WidgetBase::setStyleFlexCrossPlace(lv_flex_align_t value,
                                        lv_style_selector_t selector) const {
  lv_obj_set_style_flex_cross_place(m_obj.get(), value, selector);
}

void WidgetBase::setStyleFlexTrackPlace(lv_flex_align_t value,
                                        lv_style_selector_t selector) const {
  lv_obj_set_style_flex_track_place(m_obj.get(), value, selector);
}

void WidgetBase::setStyleFlexGrow(uint8_t value,
                                  lv_style_selector_t selector) const {
  lv_obj_set_style_flex_grow(m_obj.get(), value, selector);
}

void WidgetBase::setStyleGridColumnDscArray(
    const int32_t *value, lv_style_selector_t selector) const {
  lv_obj_set_style_grid_column_dsc_array(m_obj.get(), value, selector);
}

void WidgetBase::setStyleGridColumnAlign(lv_grid_align_t value,
                                         lv_style_selector_t selector) const {
  lv_obj_set_style_grid_column_align(m_obj.get(), value, selector);
}

void WidgetBase::setStyleGridRowDscArray(const int32_t *value,
                                         lv_style_selector_t selector) const {
  lv_obj_set_style_grid_row_dsc_array(m_obj.get(), value, selector);
}

void WidgetBase::setStyleGridRowAlign(lv_grid_align_t value,
                                      lv_style_selector_t selector) const {
  lv_obj_set_style_grid_row_align(m_obj.get(), value, selector);
}

void WidgetBase::setStyleGridCellColumnPos(int32_t value,
                                           lv_style_selector_t selector) const {
  lv_obj_set_style_grid_cell_column_pos(m_obj.get(), value, selector);
}

void WidgetBase::setStyleGridCellXAlign(lv_grid_align_t value,
                                        lv_style_selector_t selector) const {
  lv_obj_set_style_grid_cell_x_align(m_obj.get(), value, selector);
}

void WidgetBase::setStyleGridCellColumnSpan(
    int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_grid_cell_column_span(m_obj.get(), value, selector);
}

void WidgetBase::setStyleGridCellRowPos(int32_t value,
                                        lv_style_selector_t selector) const {
  lv_obj_set_style_grid_cell_row_pos(m_obj.get(), value, selector);
}

void WidgetBase::setStyleGridCellYAlign(lv_grid_align_t value,
                                        lv_style_selector_t selector) const {
  lv_obj_set_style_grid_cell_y_align(m_obj.get(), value, selector);
}

void WidgetBase::setStyleGridCellRowSpan(int32_t value,
                                         lv_style_selector_t selector) const {
  lv_obj_set_style_grid_cell_row_span(m_obj.get(), value, selector);
}

void WidgetBase::deleteDelayed(uint32_t delay_ms) const {
  lv_obj_delete_delayed(m_obj.get(), delay_ms);
}

void WidgetBase::deleteAsync() const { lv_obj_delete_async(m_obj.get()); }

void WidgetBase::setParent(const WidgetBase &parent) const {
  lv_obj_set_parent(m_obj.get(), parent.getObj());
}

void WidgetBase::swap(WidgetBase &obj2) const noexcept {
  lv_obj_swap(m_obj.get(), obj2.getObj());
}

void WidgetBase::moveToIndex(int32_t index) const {
  lv_obj_move_to_index(m_obj.get(), index);
}
struct LocalTreeWalk_ {
  WidgetBase *this_ = nullptr;
  void *user_data = nullptr;
  LvObjTreeWalkCbHandel cb_handel;
};

lv_obj_tree_walk_res_t localTreeWalk(lv_obj_t *obj, void *local_data_ptr) {
  if (!local_data_ptr)
    return lv_obj_tree_walk_res_t::LV_OBJ_TREE_WALK_END;
  auto local_data = static_cast<LocalTreeWalk_ *>(local_data_ptr);
  if (!local_data->cb_handel)
    return lv_obj_tree_walk_res_t::LV_OBJ_TREE_WALK_END;
  auto local = WidgetBase::makeFromPtr(obj);
  return local_data->cb_handel(local, local_data->user_data);
}

void WidgetBase::treeWalk(const LvObjTreeWalkCbHandel &cb, void *user_data) {
  LocalTreeWalk_ local_data{this, user_data, cb};
  lv_obj_tree_walk(m_obj.get(), localTreeWalk, &local_data);
}

void WidgetBase::dumpTree() const { lv_obj_dump_tree(m_obj.get()); }

void WidgetBase::styleCreateTransition(
    lv_part_t part, lv_state_t prev_state, lv_state_t new_state,
    const lv_obj_style_transition_dsc_t *tr) const {
  lv_obj_style_create_transition(m_obj.get(), part, prev_state, new_state, tr);
}

void WidgetBase::updateLayerType() const {
  lv_obj_update_layer_type(m_obj.get());
}

void WidgetBase::redraw(Layer &layer) const {
  lv_obj_redraw(layer.getPtr(), m_obj.get());
}

bool WidgetBase::hitTest(const Point &point) const {
  return lv_obj_hit_test(m_obj.get(), point.get());
}

WidgetBase WidgetBase::getScreen() const {
  return makeFromPtr(lv_obj_get_screen(m_obj.get()));
}

DisplayPointer WidgetBase::getDisplay() const {
  return DisplayPointer::makeQuote(lv_obj_get_display(m_obj.get()));
}

WidgetBase WidgetBase::getParent() {
  return makeFromPtr(lv_obj_get_parent(m_obj.get()));
}

WidgetBase WidgetBase::getChild(int32_t idx) const {
  return makeFromPtr(lv_obj_get_child(m_obj.get(), idx));
}

WidgetBase WidgetBase::getChildByType(int32_t idx,
                                      const lv_obj_class_t *class_p) const {
  return makeFromPtr(lv_obj_get_child_by_type(m_obj.get(), idx, class_p));
}

WidgetBase WidgetBase::getSibling(int32_t idx) const {
  return makeFromPtr(lv_obj_get_sibling(m_obj.get(), idx));
}

WidgetBase WidgetBase::getSiblingByType(int32_t idx,
                                        const lv_obj_class_t *class_p) const {
  return makeFromPtr(lv_obj_get_sibling_by_type(m_obj.get(), idx, class_p));
}

uint32_t WidgetBase::getChildCount() const {
  return lv_obj_get_child_count(m_obj.get());
}

uint32_t WidgetBase::getChildCountByType(const lv_obj_class_t *class_p) const {
  return lv_obj_get_child_count_by_type(m_obj.get(), class_p);
}

int32_t WidgetBase::getIndex() const { return lv_obj_get_index(m_obj.get()); }

int32_t WidgetBase::getIndexByType(const lv_obj_class_t *class_p) const {
  return lv_obj_get_index_by_type(m_obj.get(), class_p);
}

void WidgetBase::getCoords(Area &coords) const {
  lv_obj_get_coords(m_obj.get(), coords.getPtr());
}

int32_t WidgetBase::getX() const { return lv_obj_get_x(m_obj.get()); }

int32_t WidgetBase::getX2() const { return lv_obj_get_x2(m_obj.get()); }

int32_t WidgetBase::getY() const { return lv_obj_get_y(m_obj.get()); }

int32_t WidgetBase::getY2() const { return lv_obj_get_y2(m_obj.get()); }

int32_t WidgetBase::getXAligned() const {
  return lv_obj_get_x_aligned(m_obj.get());
}

int32_t WidgetBase::getYAligned() const {
  return lv_obj_get_y_aligned(m_obj.get());
}

int32_t WidgetBase::getWidth() const { return lv_obj_get_width(m_obj.get()); }

int32_t WidgetBase::getHeight() const { return lv_obj_get_height(m_obj.get()); }

int32_t WidgetBase::getContentWidth() const {
  return lv_obj_get_content_width(m_obj.get());
}

int32_t WidgetBase::getContentHeight() const {
  return lv_obj_get_content_height(m_obj.get());
}

void WidgetBase::getContentCoords(Area &area) const {
  lv_obj_get_content_coords(m_obj.get(), area.getPtr());
}

int32_t WidgetBase::getSelfWidth() const {
  return lv_obj_get_self_width(m_obj.get());
}

int32_t WidgetBase::getSelfHeight() const {
  return lv_obj_get_self_height(m_obj.get());
}

const Matrix WidgetBase::getTransform() const {
  return lv_obj_get_transform(m_obj.get());
}

void WidgetBase::getTransformedArea(Area &area,
                                    lv_obj_point_transform_flag_t flags) const {
  lv_obj_get_transformed_area(m_obj.get(), area.getPtr(), flags);
}

void WidgetBase::invalidate() { lv_obj_invalidate(m_obj.get()); }

bool WidgetBase::areaIsVisible(Area &area) const {
  return lv_obj_area_is_visible(m_obj.get(), area.getPtr());
}

bool WidgetBase::isVisible() const { return lv_obj_is_visible(m_obj.get()); }

} // namespace LVGLEx