//
// Created by 19254 on 24-12-16.
//
#include <LVGLEx/widget/widget_base.h>
#include <core/lv_obj_pos.h>
#include <core/lv_obj_style_private.h>
#include <core/lv_obj_tree.h>

namespace LVGLEx {


WidgetBase::~WidgetBase() {
  if (m_obj) {
    lv_obj_delete(m_obj);
    m_obj = nullptr;
  }
}

WidgetBase *WidgetBase::add_widget(std::unique_ptr<WidgetBase> &&widget) {
  auto [iter, _] = m_children.insert(std::move(widget));
  return iter->get();
}

WindowBase *WidgetBase::get_parent() const {
  return m_parent;
}

void WidgetBase::set_pos(const int32_t x, const int32_t y) const {
  lv_obj_set_pos(m_obj, x, y);
}

void WidgetBase::set_x(const int32_t x) const {
  lv_obj_set_x(m_obj, x);
}

void WidgetBase::set_y(const int32_t y) const {
  lv_obj_set_y(m_obj, y);
}

void WidgetBase::set_size(const int32_t w, const int32_t h) const {
  lv_obj_set_size(m_obj, w, h);
}

void WidgetBase::set_width(const int32_t w) const {
  lv_obj_set_width(m_obj, w);
}

void WidgetBase::set_height(const int32_t h) const {
  lv_obj_set_height(m_obj, h);
}


void WidgetBase::move_foreground() const {
  lv_obj_move_foreground(m_obj);
};

void WidgetBase::add_flag(const lv_obj_flag_t f) const {
  lv_obj_add_flag(m_obj, f);
};

void WidgetBase::remove_flag(const lv_obj_flag_t f) const {
  lv_obj_remove_flag(m_obj, f);
};

void WidgetBase::update_flag(const lv_obj_flag_t f, const bool v) const {
  lv_obj_update_flag(m_obj, f, v);
}

void WidgetBase::add_state(lv_state_t state) const {
  lv_obj_add_state(m_obj, state);
}

void WidgetBase::remove_state(lv_state_t state) const {
  lv_obj_remove_state(m_obj, state);
}

void WidgetBase::set_state(lv_state_t state, bool v) const {
  lv_obj_set_state(m_obj, state, v);
}

void WidgetBase::set_user_data(void *user_data) const {
  lv_obj_set_user_data(m_obj, user_data);
}

void WidgetBase::allocate_spec_attr() const {
  lv_obj_allocate_spec_attr(m_obj);
}

void WidgetBase::class_init_obj() const {
  lv_obj_class_init_obj(m_obj);
}

void WidgetBase::init_draw_rect_dsc(lv_part_t part, lv_draw_rect_dsc_t *draw_dsc) const {
  lv_obj_init_draw_rect_dsc(m_obj, part, draw_dsc);
}

void WidgetBase::init_draw_label_dsc(lv_part_t part, lv_draw_label_dsc_t *draw_dsc) const {
  lv_obj_init_draw_label_dsc(m_obj, part, draw_dsc);
}

void WidgetBase::init_draw_image_dsc(lv_part_t part, lv_draw_image_dsc_t *draw_dsc) const {
  lv_obj_init_draw_image_dsc(m_obj, part, draw_dsc);
}

void WidgetBase::init_draw_line_dsc(lv_part_t part, lv_draw_line_dsc_t *draw_dsc) const {
  lv_obj_init_draw_line_dsc(m_obj, part, draw_dsc);
}

void WidgetBase::init_draw_arc_dsc(lv_part_t part, lv_draw_arc_dsc_t *draw_dsc) const {
  lv_obj_init_draw_arc_dsc(m_obj, part, draw_dsc);
}

void WidgetBase::refresh_ext_draw_size() const {
  lv_obj_refresh_ext_draw_size(m_obj);
}


// void WidgetBase::func_name_end( int32_t size) const {
//   func_prefixfunc_name_end(m_obj , size);
// }
//
// void WidgetBase::func_name_end( lv_cover_res_t res) const {
//   func_prefixfunc_name_end(m_obj , res);
// }

void WidgetBase::set_content_width(int32_t w) const {
  lv_obj_set_content_width(m_obj, w);
}

void WidgetBase::set_content_height(int32_t h) const {
  lv_obj_set_content_height(m_obj, h);
}

void WidgetBase::set_layout(uint32_t layout) const {
  lv_obj_set_layout(m_obj, layout);
}

void WidgetBase::mark_layout_as_dirty() const {
  lv_obj_mark_layout_as_dirty(m_obj);
}

void WidgetBase::update_layout() const {
  lv_obj_update_layout(m_obj);
}

void WidgetBase::set_align(lv_align_t align) const {
  lv_obj_set_align(m_obj, align);
}

void WidgetBase::align(lv_align_t align, int32_t x_ofs, int32_t y_ofs) const {
  lv_obj_align(m_obj, align, x_ofs, y_ofs);
}

void WidgetBase::align_to(const lv_obj_t *base, lv_align_t align, int32_t x_ofs, int32_t y_ofs) const {
  lv_obj_align_to(m_obj, base, align, x_ofs, y_ofs);
}

void WidgetBase::center() const {
  lv_obj_center(m_obj);
}

void WidgetBase::set_transform(const lv_matrix_t *matrix) const {
  lv_obj_set_transform(m_obj, matrix);
}

void WidgetBase::reset_transform() const {
  lv_obj_reset_transform(m_obj);
}

void WidgetBase::get_coords(lv_area_t *coords) const {
  lv_obj_get_coords(m_obj, coords);
}

void WidgetBase::get_content_coords(lv_area_t *area) const {
  lv_obj_get_content_coords(m_obj, area);
}

void WidgetBase::refr_pos() const {
  lv_obj_refr_pos(m_obj);
}

void WidgetBase::move_to(int32_t x, int32_t y) const {
  lv_obj_move_to(m_obj, x, y);
}

void WidgetBase::move_children_by(int32_t x_diff, int32_t y_diff, bool ignore_floating) const {
  lv_obj_move_children_by(m_obj, x_diff, y_diff, ignore_floating);
}

void WidgetBase::transform_point(lv_point_t *p, lv_obj_point_transform_flag_t flags) const {
  lv_obj_transform_point(m_obj, p, flags);
}

void WidgetBase::transform_point_array(lv_point_t points[], size_t count, lv_obj_point_transform_flag_t flags) const {
  lv_obj_transform_point_array(m_obj, points, count, flags);
}

void WidgetBase::get_transformed_area(lv_area_t *area, lv_obj_point_transform_flag_t flags) const {
  lv_obj_get_transformed_area(m_obj, area, flags);
}

void WidgetBase::invalidate_area(const lv_area_t *area) const {
  lv_obj_invalidate_area(m_obj, area);
}

void WidgetBase::invalidate() const {
  lv_obj_invalidate(m_obj);
}

void WidgetBase::set_ext_click_area(int32_t size) const {
  lv_obj_set_ext_click_area(m_obj, size);
}

void WidgetBase::get_click_area(lv_area_t *area) const {
  lv_obj_get_click_area(m_obj, area);
}

void WidgetBase::set_scrollbar_mode(lv_scrollbar_mode_t mode) const {
  lv_obj_set_scrollbar_mode(m_obj, mode);
}

void WidgetBase::set_scroll_dir(lv_dir_t dir) const {
  lv_obj_set_scroll_dir(m_obj, dir);
}

void WidgetBase::set_scroll_snap_x(lv_scroll_snap_t align) const {
  lv_obj_set_scroll_snap_x(m_obj, align);
}

void WidgetBase::set_scroll_snap_y(lv_scroll_snap_t align) const {
  lv_obj_set_scroll_snap_y(m_obj, align);
}

void WidgetBase::get_scroll_end(lv_point_t *end) const {
  lv_obj_get_scroll_end(m_obj, end);
}

void WidgetBase::scroll_by(int32_t dx, int32_t dy, lv_anim_enable_t anim_en) const {
  lv_obj_scroll_by(m_obj, dx, dy, anim_en);
}

void WidgetBase::scroll_by_bounded(int32_t dx, int32_t dy, lv_anim_enable_t anim_en) const {
  lv_obj_scroll_by_bounded(m_obj, dx, dy, anim_en);
}

void WidgetBase::scroll_to(int32_t x, int32_t y, lv_anim_enable_t anim_en) const {
  lv_obj_scroll_to(m_obj, x, y, anim_en);
}

void WidgetBase::scroll_to_x(int32_t x, lv_anim_enable_t anim_en) const {
  lv_obj_scroll_to_x(m_obj, x, anim_en);
}

void WidgetBase::scroll_to_y(int32_t y, lv_anim_enable_t anim_en) const {
  lv_obj_scroll_to_y(m_obj, y, anim_en);
}

void WidgetBase::scroll_to_view(lv_anim_enable_t anim_en) const {
  lv_obj_scroll_to_view(m_obj, anim_en);
}

void WidgetBase::scroll_to_view_recursive(lv_anim_enable_t anim_en) const {
  lv_obj_scroll_to_view_recursive(m_obj, anim_en);
}

void WidgetBase::update_snap(lv_anim_enable_t anim_en) const {
  lv_obj_update_snap(m_obj, anim_en);
}

void WidgetBase::get_scrollbar_area(lv_area_t *hor, lv_area_t *ver) const {
  lv_obj_get_scrollbar_area(m_obj, hor, ver);
}

void WidgetBase::scrollbar_invalidate() const {
  lv_obj_scrollbar_invalidate(m_obj);
}

void WidgetBase::readjust_scroll(lv_anim_enable_t anim_en) const {
  lv_obj_readjust_scroll(m_obj, anim_en);
}

void WidgetBase::add_style(const lv_style_t *style, lv_style_selector_t selector) const {
  lv_obj_add_style(m_obj, style, selector);
}

void WidgetBase::remove_style(const lv_style_t *style, lv_style_selector_t selector) const {
  lv_obj_remove_style(m_obj, style, selector);
}

void WidgetBase::remove_style_all() const {
  lv_obj_remove_style_all(m_obj);
}

void WidgetBase::report_style_change(lv_style_t *style) const {
  lv_obj_report_style_change(style);
}

void WidgetBase::refresh_style(lv_part_t part, lv_style_prop_t prop) const {
  lv_obj_refresh_style(m_obj, part, prop);
}

void WidgetBase::enable_style_refresh() const {
  lv_obj_enable_style_refresh(m_obj);
}

void WidgetBase::set_local_style_prop(lv_style_prop_t prop, lv_style_value_t value, lv_style_selector_t selector) const {
  lv_obj_set_local_style_prop(m_obj, prop, value, selector);
}

void WidgetBase::fade_in(uint32_t time, uint32_t delay) const {
  lv_obj_fade_in(m_obj, time, delay);
}

void WidgetBase::fade_out(uint32_t time, uint32_t delay) const {
  lv_obj_fade_out(m_obj, time, delay);
}

void WidgetBase::set_style_pad_all(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_pad_all(m_obj, value, selector);
}

void WidgetBase::set_style_pad_hor(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_pad_hor(m_obj, value, selector);
}

void WidgetBase::set_style_pad_ver(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_pad_ver(m_obj, value, selector);
}

void WidgetBase::set_style_margin_all(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_margin_all(m_obj, value, selector);
}

void WidgetBase::set_style_margin_hor(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_margin_hor(m_obj, value, selector);
}

void WidgetBase::set_style_margin_ver(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_margin_ver(m_obj, value, selector);
}

void WidgetBase::set_style_pad_gap(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_pad_gap(m_obj, value, selector);
}

void WidgetBase::set_style_size(int32_t width, int32_t height, lv_style_selector_t selector) const {
  lv_obj_set_style_size(m_obj, width, height, selector);
}

void WidgetBase::set_style_transform_scale(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_transform_scale(m_obj, value, selector);
}


void WidgetBase::set_style_width(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_width(m_obj, value, selector);
}

void WidgetBase::set_style_min_width(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_min_width(m_obj, value, selector);
}

void WidgetBase::set_style_max_width(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_max_width(m_obj, value, selector);
}

void WidgetBase::set_style_height(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_height(m_obj, value, selector);
}

void WidgetBase::set_style_min_height(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_min_height(m_obj, value, selector);
}

void WidgetBase::set_style_max_height(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_max_height(m_obj, value, selector);
}

void WidgetBase::set_style_length(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_length(m_obj, value, selector);
}

void WidgetBase::set_style_x(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_x(m_obj, value, selector);
}

void WidgetBase::set_style_y(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_y(m_obj, value, selector);
}

void WidgetBase::set_style_align(lv_align_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_align(m_obj, value, selector);
}

void WidgetBase::set_style_transform_width(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_transform_width(m_obj, value, selector);
}

void WidgetBase::set_style_transform_height(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_transform_height(m_obj, value, selector);
}

void WidgetBase::set_style_translate_x(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_translate_x(m_obj, value, selector);
}

void WidgetBase::set_style_translate_y(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_translate_y(m_obj, value, selector);
}

void WidgetBase::set_style_translate_radial(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_translate_radial(m_obj, value, selector);
}

void WidgetBase::set_style_transform_scale_x(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_transform_scale_x(m_obj, value, selector);
}

void WidgetBase::set_style_transform_scale_y(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_transform_scale_y(m_obj, value, selector);
}

void WidgetBase::set_style_transform_rotation(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_transform_rotation(m_obj, value, selector);
}

void WidgetBase::set_style_transform_pivot_x(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_transform_pivot_x(m_obj, value, selector);
}

void WidgetBase::set_style_transform_pivot_y(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_transform_pivot_y(m_obj, value, selector);
}

void WidgetBase::set_style_transform_skew_x(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_transform_skew_x(m_obj, value, selector);
}

void WidgetBase::set_style_transform_skew_y(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_transform_skew_y(m_obj, value, selector);
}

void WidgetBase::set_style_pad_top(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_pad_top(m_obj, value, selector);
}

void WidgetBase::set_style_pad_bottom(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_pad_bottom(m_obj, value, selector);
}

void WidgetBase::set_style_pad_left(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_pad_left(m_obj, value, selector);
}

void WidgetBase::set_style_pad_right(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_pad_right(m_obj, value, selector);
}

void WidgetBase::set_style_pad_row(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_pad_row(m_obj, value, selector);
}

void WidgetBase::set_style_pad_column(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_pad_column(m_obj, value, selector);
}

void WidgetBase::set_style_pad_radial(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_pad_radial(m_obj, value, selector);
}

void WidgetBase::set_style_margin_top(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_margin_top(m_obj, value, selector);
}

void WidgetBase::set_style_margin_bottom(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_margin_bottom(m_obj, value, selector);
}

void WidgetBase::set_style_margin_left(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_margin_left(m_obj, value, selector);
}

void WidgetBase::set_style_margin_right(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_margin_right(m_obj, value, selector);
}

void WidgetBase::set_style_bg_color(lv_color_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_bg_color(m_obj, value, selector);
}

void WidgetBase::set_style_bg_opa(lv_opa_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_bg_opa(m_obj, value, selector);
}

void WidgetBase::set_style_bg_grad_color(lv_color_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_bg_grad_color(m_obj, value, selector);
}

void WidgetBase::set_style_bg_grad_dir(lv_grad_dir_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_bg_grad_dir(m_obj, value, selector);
}

void WidgetBase::set_style_bg_main_stop(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_bg_main_stop(m_obj, value, selector);
}

void WidgetBase::set_style_bg_grad_stop(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_bg_grad_stop(m_obj, value, selector);
}

void WidgetBase::set_style_bg_main_opa(lv_opa_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_bg_main_opa(m_obj, value, selector);
}

void WidgetBase::set_style_bg_grad_opa(lv_opa_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_bg_grad_opa(m_obj, value, selector);
}

void WidgetBase::set_style_bg_grad(const lv_grad_dsc_t *value, lv_style_selector_t selector) const {
  lv_obj_set_style_bg_grad(m_obj, value, selector);
}

void WidgetBase::set_style_bg_image_src(const void *value, lv_style_selector_t selector) const {
  lv_obj_set_style_bg_image_src(m_obj, value, selector);
}

void WidgetBase::set_style_bg_image_opa(lv_opa_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_bg_image_opa(m_obj, value, selector);
}

void WidgetBase::set_style_bg_image_recolor(lv_color_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_bg_image_recolor(m_obj, value, selector);
}

void WidgetBase::set_style_bg_image_recolor_opa(lv_opa_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_bg_image_recolor_opa(m_obj, value, selector);
}

void WidgetBase::set_style_bg_image_tiled(bool value, lv_style_selector_t selector) const {
  lv_obj_set_style_bg_image_tiled(m_obj, value, selector);
}

void WidgetBase::set_style_border_color(lv_color_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_border_color(m_obj, value, selector);
}

void WidgetBase::set_style_border_opa(lv_opa_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_border_opa(m_obj, value, selector);
}

void WidgetBase::set_style_border_width(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_border_width(m_obj, value, selector);
}

void WidgetBase::set_style_border_side(lv_border_side_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_border_side(m_obj, value, selector);
}

void WidgetBase::set_style_border_post(bool value, lv_style_selector_t selector) const {
  lv_obj_set_style_border_post(m_obj, value, selector);
}

void WidgetBase::set_style_outline_width(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_outline_width(m_obj, value, selector);
}

void WidgetBase::set_style_outline_color(lv_color_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_outline_color(m_obj, value, selector);
}

void WidgetBase::set_style_outline_opa(lv_opa_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_outline_opa(m_obj, value, selector);
}

void WidgetBase::set_style_outline_pad(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_outline_pad(m_obj, value, selector);
}

void WidgetBase::set_style_shadow_width(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_shadow_width(m_obj, value, selector);
}

void WidgetBase::set_style_shadow_offset_x(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_shadow_offset_x(m_obj, value, selector);
}

void WidgetBase::set_style_shadow_offset_y(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_shadow_offset_y(m_obj, value, selector);
}

void WidgetBase::set_style_shadow_spread(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_shadow_spread(m_obj, value, selector);
}

void WidgetBase::set_style_shadow_color(lv_color_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_shadow_color(m_obj, value, selector);
}

void WidgetBase::set_style_shadow_opa(lv_opa_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_shadow_opa(m_obj, value, selector);
}

void WidgetBase::set_style_image_opa(lv_opa_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_image_opa(m_obj, value, selector);
}

void WidgetBase::set_style_image_recolor(lv_color_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_image_recolor(m_obj, value, selector);
}

void WidgetBase::set_style_image_recolor_opa(lv_opa_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_image_recolor_opa(m_obj, value, selector);
}

void WidgetBase::set_style_line_width(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_line_width(m_obj, value, selector);
}

void WidgetBase::set_style_line_dash_width(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_line_dash_width(m_obj, value, selector);
}

void WidgetBase::set_style_line_dash_gap(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_line_dash_gap(m_obj, value, selector);
}

void WidgetBase::set_style_line_rounded(bool value, lv_style_selector_t selector) const {
  lv_obj_set_style_line_rounded(m_obj, value, selector);
}

void WidgetBase::set_style_line_color(lv_color_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_line_color(m_obj, value, selector);
}

void WidgetBase::set_style_line_opa(lv_opa_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_line_opa(m_obj, value, selector);
}

void WidgetBase::set_style_arc_width(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_arc_width(m_obj, value, selector);
}

void WidgetBase::set_style_arc_rounded(bool value, lv_style_selector_t selector) const {
  lv_obj_set_style_arc_rounded(m_obj, value, selector);
}

void WidgetBase::set_style_arc_color(lv_color_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_arc_color(m_obj, value, selector);
}

void WidgetBase::set_style_arc_opa(lv_opa_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_arc_opa(m_obj, value, selector);
}

void WidgetBase::set_style_arc_image_src(const void *value, lv_style_selector_t selector) const {
  lv_obj_set_style_arc_image_src(m_obj, value, selector);
}

void WidgetBase::set_style_text_color(lv_color_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_text_color(m_obj, value, selector);
}

void WidgetBase::set_style_text_opa(lv_opa_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_text_opa(m_obj, value, selector);
}

void WidgetBase::set_style_text_font(const lv_font_t *value, lv_style_selector_t selector) const {
  lv_obj_set_style_text_font(m_obj, value, selector);
}

void WidgetBase::set_style_text_letter_space(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_text_letter_space(m_obj, value, selector);
}

void WidgetBase::set_style_text_line_space(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_text_line_space(m_obj, value, selector);
}

void WidgetBase::set_style_text_decor(lv_text_decor_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_text_decor(m_obj, value, selector);
}

void WidgetBase::set_style_text_align(lv_text_align_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_text_align(m_obj, value, selector);
}

void WidgetBase::set_style_radius(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_radius(m_obj, value, selector);
}

void WidgetBase::set_style_radial_offset(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_radial_offset(m_obj, value, selector);
}

void WidgetBase::set_style_clip_corner(bool value, lv_style_selector_t selector) const {
  lv_obj_set_style_clip_corner(m_obj, value, selector);
}

void WidgetBase::set_style_opa(lv_opa_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_opa(m_obj, value, selector);
}

void WidgetBase::set_style_opa_layered(lv_opa_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_opa_layered(m_obj, value, selector);
}

void WidgetBase::set_style_color_filter_dsc(const lv_color_filter_dsc_t *value, lv_style_selector_t selector) const {
  lv_obj_set_style_color_filter_dsc(m_obj, value, selector);
}

void WidgetBase::set_style_color_filter_opa(lv_opa_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_color_filter_opa(m_obj, value, selector);
}

void WidgetBase::set_style_anim(const lv_anim_t *value, lv_style_selector_t selector) const {
  lv_obj_set_style_anim(m_obj, value, selector);
}

void WidgetBase::set_style_anim_duration(uint32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_anim_duration(m_obj, value, selector);
}

void WidgetBase::set_style_transition(const lv_style_transition_dsc_t *value, lv_style_selector_t selector) const {
  lv_obj_set_style_transition(m_obj, value, selector);
}

void WidgetBase::set_style_blend_mode(lv_blend_mode_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_blend_mode(m_obj, value, selector);
}

void WidgetBase::set_style_layout(uint16_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_layout(m_obj, value, selector);
}

void WidgetBase::set_style_base_dir(lv_base_dir_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_base_dir(m_obj, value, selector);
}

void WidgetBase::set_style_bitmap_mask_src(const void *value, lv_style_selector_t selector) const {
  lv_obj_set_style_bitmap_mask_src(m_obj, value, selector);
}

void WidgetBase::set_style_rotary_sensitivity(uint32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_rotary_sensitivity(m_obj, value, selector);
}

void WidgetBase::set_style_flex_flow(lv_flex_flow_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_flex_flow(m_obj, value, selector);
}

void WidgetBase::set_style_flex_main_place(lv_flex_align_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_flex_main_place(m_obj, value, selector);
}

void WidgetBase::set_style_flex_cross_place(lv_flex_align_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_flex_cross_place(m_obj, value, selector);
}

void WidgetBase::set_style_flex_track_place(lv_flex_align_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_flex_track_place(m_obj, value, selector);
}

void WidgetBase::set_style_flex_grow(uint8_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_flex_grow(m_obj, value, selector);
}

void WidgetBase::set_style_grid_column_dsc_array(const int32_t *value, lv_style_selector_t selector) const {
  lv_obj_set_style_grid_column_dsc_array(m_obj, value, selector);
}

void WidgetBase::set_style_grid_column_align(lv_grid_align_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_grid_column_align(m_obj, value, selector);
}

void WidgetBase::set_style_grid_row_dsc_array(const int32_t *value, lv_style_selector_t selector) const {
  lv_obj_set_style_grid_row_dsc_array(m_obj, value, selector);
}

void WidgetBase::set_style_grid_row_align(lv_grid_align_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_grid_row_align(m_obj, value, selector);
}

void WidgetBase::set_style_grid_cell_column_pos(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_grid_cell_column_pos(m_obj, value, selector);
}

void WidgetBase::set_style_grid_cell_x_align(lv_grid_align_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_grid_cell_x_align(m_obj, value, selector);
}

void WidgetBase::set_style_grid_cell_column_span(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_grid_cell_column_span(m_obj, value, selector);
}

void WidgetBase::set_style_grid_cell_row_pos(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_grid_cell_row_pos(m_obj, value, selector);
}

void WidgetBase::set_style_grid_cell_y_align(lv_grid_align_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_grid_cell_y_align(m_obj, value, selector);
}

void WidgetBase::set_style_grid_cell_row_span(int32_t value, lv_style_selector_t selector) const {
  lv_obj_set_style_grid_cell_row_span(m_obj, value, selector);
}


void WidgetBase::delete_delayed(uint32_t delay_ms) const {
  lv_obj_delete_delayed(m_obj, delay_ms);
}

void WidgetBase::delete_async() const {
  lv_obj_delete_async(m_obj);
}

void WidgetBase::set_parent(lv_obj_t *parent) const {
  lv_obj_set_parent(m_obj, parent);
}

void WidgetBase::swap(lv_obj_t *obj2) const {
  lv_obj_swap(m_obj, obj2);
}

void WidgetBase::move_to_index(int32_t index) const {
  lv_obj_move_to_index(m_obj, index);
}

void WidgetBase::tree_walk(lv_obj_tree_walk_cb_t cb, void *user_data) const {
  lv_obj_tree_walk(m_obj, cb, user_data);
}

void WidgetBase::dump_tree() const {
  lv_obj_dump_tree(m_obj);
}

void WidgetBase::style_create_transition(lv_part_t part, lv_state_t prev_state, lv_state_t new_state, const lv_obj_style_transition_dsc_t *tr) const {
  lv_obj_style_create_transition(m_obj, part, prev_state, new_state, tr);
}

void WidgetBase::update_layer_type() const {
  lv_obj_update_layer_type(m_obj);
}

void WidgetBase::redraw(lv_layer_t* layer) const {
  lv_obj_redraw(layer , m_obj);
}

}// namespace LVGLEx