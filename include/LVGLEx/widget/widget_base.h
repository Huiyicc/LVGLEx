//
// Created by 19254 on 24-12-16.
//

#ifndef LVGLEX_WIDGET_BASE_H
#define LVGLEX_WIDGET_BASE_H

#include "../obj_pointer.h"
#include "./widget_event_base.h"
#include <lvgl.h>
#include <memory>
#include <set>

namespace LVGLEx {

class WindowBase;

/*
void func_name_end(int32_t size) const;
void func_name_end(lv_cover_res_t res) const;
void delete() const;
void clean() const;
lv_refr_now(lv_display_t* disp) -> void
lv_refr_init(void) -> void
lv_refr_deinit(void)->void
lv_inv_area(lv_display_t* disp, const lv_area_t* area_p) -> void
lv_refr_set_disp_refreshing(lv_display_t* disp) -> void
lv_display_refr_timer(lv_timer_t* timer) -> void
void lv_obj_delete_anim_completed_cb(lv_anim_t *a) const;
* */

#define WIDGET_OBJ_CREATE_H(TYPE)                                              \
  static TYPE *create(WidgetBase *parent);                                     \
  static TYPE *create(WindowBase *parent);
#define WIDGET_OBJ_CREATE_CPP(TYPE, OBJCREATE_FUNC)                            \
  TYPE *TYPE::create(WindowBase *parent) {                                     \
    auto r = std::make_unique<TYPE>();                                         \
    auto scr = parent->get_screen_active();                                    \
    r->m_parent = parent;                                                      \
    r->m_obj = WidgetPointer<lv_obj_t>::MakePrivatePtr(OBJCREATE_FUNC(scr));   \
    r->init();                                                                 \
    return dynamic_cast<TYPE *>(parent->add_widget(std::move(r)));             \
  }                                                                            \
  TYPE *TYPE::create(WidgetBase *parent) {                                     \
    auto r = std::make_unique<TYPE>();                                         \
    auto scr = parent->get_parent()->get_screen_active();                      \
    r->m_parent = parent->get_parent();                                        \
    r->m_obj = WidgetPointer<lv_obj_t>::MakePrivatePtr(OBJCREATE_FUNC(scr));   \
    r->init();                                                                 \
    return dynamic_cast<TYPE *>(parent->add_widget(std::move(r)));             \
  };

class WidgetBase : public WidgetEventBase {
protected:
  WidgetPointer<lv_obj_t> m_obj;
  // lv_obj_t *m_obj = nullptr;
  WindowBase *m_parent = nullptr;
  std::set<std::unique_ptr<WidgetBase>> m_children;

  virtual void init() final;

public:
  WidgetBase();
  virtual ~WidgetBase();

  lv_obj_t *get_obj() const;

  [[nodiscard]] WindowBase *get_parent() const;

  WidgetBase *add_widget(std::unique_ptr<WidgetBase> &&widget);

  void set_pos(int32_t x, int32_t y) const;
  void set_x(int32_t x) const;
  void set_y(int32_t y) const;
  void set_size(int32_t w, int32_t h) const;
  void set_width(int32_t w) const;
  void set_height(int32_t h) const;
  void set_content_width(int32_t w) const;
  void set_content_height(int32_t h) const;
  void set_layout(uint32_t layout) const;
  void mark_layout_as_dirty() const;
  void update_layout() const;
  void set_align(lv_align_t align) const;
  void align(lv_align_t align, int32_t x_ofs, int32_t y_ofs) const;
  void align_to(const lv_obj_t *base, lv_align_t align, int32_t x_ofs,
                int32_t y_ofs) const;
  void center() const;
  void set_transform(const lv_matrix_t *matrix) const;
  void reset_transform() const;
  void get_coords(lv_area_t *coords) const;
  void get_content_coords(lv_area_t *area) const;
  void refr_pos() const;
  void move_to(int32_t x, int32_t y) const;
  void move_children_by(int32_t x_diff, int32_t y_diff,
                        bool ignore_floating) const;
  void transform_point(lv_point_t *p,
                       lv_obj_point_transform_flag_t flags) const;
  void transform_point_array(lv_point_t points[], size_t count,
                             lv_obj_point_transform_flag_t flags) const;
  void get_transformed_area(lv_area_t *area,
                            lv_obj_point_transform_flag_t flags) const;
  void invalidate_area(const lv_area_t *area) const;
  void invalidate() const;
  void set_ext_click_area(int32_t size) const;
  void get_click_area(lv_area_t *area) const;

  void move_foreground() const;

  void add_flag(lv_obj_flag_t f) const;
  void remove_flag(lv_obj_flag_t f) const;
  void update_flag(lv_obj_flag_t f, bool v) const;
  void add_state(lv_state_t state) const;
  void remove_state(lv_state_t state) const;
  void set_state(lv_state_t state, bool v) const;
  void set_user_data(void *user_data) const;
  void allocate_spec_attr() const;

  void class_init_obj() const;

  void init_draw_rect_dsc(lv_part_t part, lv_draw_rect_dsc_t *draw_dsc) const;
  void init_draw_label_dsc(lv_part_t part, lv_draw_label_dsc_t *draw_dsc) const;
  void init_draw_image_dsc(lv_part_t part, lv_draw_image_dsc_t *draw_dsc) const;
  void init_draw_line_dsc(lv_part_t part, lv_draw_line_dsc_t *draw_dsc) const;
  void init_draw_arc_dsc(lv_part_t part, lv_draw_arc_dsc_t *draw_dsc) const;
  void refresh_ext_draw_size() const;

  void set_scrollbar_mode(lv_scrollbar_mode_t mode) const;
  void set_scroll_dir(lv_dir_t dir) const;
  void set_scroll_snap_x(lv_scroll_snap_t align) const;
  void set_scroll_snap_y(lv_scroll_snap_t align) const;
  void get_scroll_end(lv_point_t *end) const;
  void scroll_by(int32_t dx, int32_t dy, lv_anim_enable_t anim_en) const;
  void scroll_by_bounded(int32_t dx, int32_t dy,
                         lv_anim_enable_t anim_en) const;
  void scroll_to(int32_t x, int32_t y, lv_anim_enable_t anim_en) const;
  void scroll_to_x(int32_t x, lv_anim_enable_t anim_en) const;
  void scroll_to_y(int32_t y, lv_anim_enable_t anim_en) const;
  void scroll_to_view(lv_anim_enable_t anim_en) const;
  void scroll_to_view_recursive(lv_anim_enable_t anim_en) const;
  void update_snap(lv_anim_enable_t anim_en) const;
  void get_scrollbar_area(lv_area_t *hor, lv_area_t *ver) const;
  void scrollbar_invalidate() const;
  void readjust_scroll(lv_anim_enable_t anim_en) const;

  void add_style(const lv_style_t *style, lv_style_selector_t selector) const;
  void remove_style(const lv_style_t *style,
                    lv_style_selector_t selector) const;
  void remove_style_all() const;
  void report_style_change(lv_style_t *style) const;
  void refresh_style(lv_part_t part, lv_style_prop_t prop) const;
  void enable_style_refresh() const;
  void set_local_style_prop(lv_style_prop_t prop, lv_style_value_t value,
                            lv_style_selector_t selector) const;
  void fade_in(uint32_t time, uint32_t delay) const;
  void fade_out(uint32_t time, uint32_t delay) const;
  void set_style_pad_all(int32_t value, lv_style_selector_t selector) const;
  void set_style_pad_hor(int32_t value, lv_style_selector_t selector) const;
  void set_style_pad_ver(int32_t value, lv_style_selector_t selector) const;
  void set_style_margin_all(int32_t value, lv_style_selector_t selector) const;
  void set_style_margin_hor(int32_t value, lv_style_selector_t selector) const;
  void set_style_margin_ver(int32_t value, lv_style_selector_t selector) const;
  void set_style_pad_gap(int32_t value, lv_style_selector_t selector) const;
  void set_style_size(int32_t width, int32_t height,
                      lv_style_selector_t selector) const;
  void set_style_transform_scale(int32_t value,
                                 lv_style_selector_t selector) const;

  void set_style_width(int32_t value, lv_style_selector_t selector) const;
  void set_style_min_width(int32_t value, lv_style_selector_t selector) const;
  void set_style_max_width(int32_t value, lv_style_selector_t selector) const;
  void set_style_height(int32_t value, lv_style_selector_t selector) const;
  void set_style_min_height(int32_t value, lv_style_selector_t selector) const;
  void set_style_max_height(int32_t value, lv_style_selector_t selector) const;
  void set_style_length(int32_t value, lv_style_selector_t selector) const;
  void set_style_x(int32_t value, lv_style_selector_t selector) const;
  void set_style_y(int32_t value, lv_style_selector_t selector) const;
  void set_style_align(lv_align_t value, lv_style_selector_t selector) const;
  void set_style_transform_width(int32_t value,
                                 lv_style_selector_t selector) const;
  void set_style_transform_height(int32_t value,
                                  lv_style_selector_t selector) const;
  void set_style_translate_x(int32_t value, lv_style_selector_t selector) const;
  void set_style_translate_y(int32_t value, lv_style_selector_t selector) const;
  void set_style_translate_radial(int32_t value,
                                  lv_style_selector_t selector) const;
  void set_style_transform_scale_x(int32_t value,
                                   lv_style_selector_t selector) const;
  void set_style_transform_scale_y(int32_t value,
                                   lv_style_selector_t selector) const;
  void set_style_transform_rotation(int32_t value,
                                    lv_style_selector_t selector) const;
  void set_style_transform_pivot_x(int32_t value,
                                   lv_style_selector_t selector) const;
  void set_style_transform_pivot_y(int32_t value,
                                   lv_style_selector_t selector) const;
  void set_style_transform_skew_x(int32_t value,
                                  lv_style_selector_t selector) const;
  void set_style_transform_skew_y(int32_t value,
                                  lv_style_selector_t selector) const;
  void set_style_pad_top(int32_t value, lv_style_selector_t selector) const;
  void set_style_pad_bottom(int32_t value, lv_style_selector_t selector) const;
  void set_style_pad_left(int32_t value, lv_style_selector_t selector) const;
  void set_style_pad_right(int32_t value, lv_style_selector_t selector) const;
  void set_style_pad_row(int32_t value, lv_style_selector_t selector) const;
  void set_style_pad_column(int32_t value, lv_style_selector_t selector) const;
  void set_style_pad_radial(int32_t value, lv_style_selector_t selector) const;
  void set_style_margin_top(int32_t value, lv_style_selector_t selector) const;
  void set_style_margin_bottom(int32_t value,
                               lv_style_selector_t selector) const;
  void set_style_margin_left(int32_t value, lv_style_selector_t selector) const;
  void set_style_margin_right(int32_t value,
                              lv_style_selector_t selector) const;
  void set_style_bg_color(lv_color_t value, lv_style_selector_t selector) const;
  void set_style_bg_opa(lv_opa_t value, lv_style_selector_t selector) const;
  void set_style_bg_grad_color(lv_color_t value,
                               lv_style_selector_t selector) const;
  void set_style_bg_grad_dir(lv_grad_dir_t value,
                             lv_style_selector_t selector) const;
  void set_style_bg_main_stop(int32_t value,
                              lv_style_selector_t selector) const;
  void set_style_bg_grad_stop(int32_t value,
                              lv_style_selector_t selector) const;
  void set_style_bg_main_opa(lv_opa_t value,
                             lv_style_selector_t selector) const;
  void set_style_bg_grad_opa(lv_opa_t value,
                             lv_style_selector_t selector) const;
  void set_style_bg_grad(const lv_grad_dsc_t *value,
                         lv_style_selector_t selector) const;
  void set_style_bg_image_src(const void *value,
                              lv_style_selector_t selector) const;
  void set_style_bg_image_opa(lv_opa_t value,
                              lv_style_selector_t selector) const;
  void set_style_bg_image_recolor(lv_color_t value,
                                  lv_style_selector_t selector) const;
  void set_style_bg_image_recolor_opa(lv_opa_t value,
                                      lv_style_selector_t selector) const;
  void set_style_bg_image_tiled(bool value, lv_style_selector_t selector) const;
  void set_style_border_color(lv_color_t value,
                              lv_style_selector_t selector) const;
  void set_style_border_opa(lv_opa_t value, lv_style_selector_t selector) const;
  void set_style_border_width(int32_t value,
                              lv_style_selector_t selector) const;
  void set_style_border_side(lv_border_side_t value,
                             lv_style_selector_t selector) const;
  void set_style_border_post(bool value, lv_style_selector_t selector) const;
  void set_style_outline_width(int32_t value,
                               lv_style_selector_t selector) const;
  void set_style_outline_color(lv_color_t value,
                               lv_style_selector_t selector) const;
  void set_style_outline_opa(lv_opa_t value,
                             lv_style_selector_t selector) const;
  void set_style_outline_pad(int32_t value, lv_style_selector_t selector) const;
  void set_style_shadow_width(int32_t value,
                              lv_style_selector_t selector) const;
  void set_style_shadow_offset_x(int32_t value,
                                 lv_style_selector_t selector) const;
  void set_style_shadow_offset_y(int32_t value,
                                 lv_style_selector_t selector) const;
  void set_style_shadow_spread(int32_t value,
                               lv_style_selector_t selector) const;
  void set_style_shadow_color(lv_color_t value,
                              lv_style_selector_t selector) const;
  void set_style_shadow_opa(lv_opa_t value, lv_style_selector_t selector) const;
  void set_style_image_opa(lv_opa_t value, lv_style_selector_t selector) const;
  void set_style_image_recolor(lv_color_t value,
                               lv_style_selector_t selector) const;
  void set_style_image_recolor_opa(lv_opa_t value,
                                   lv_style_selector_t selector) const;
  void set_style_line_width(int32_t value, lv_style_selector_t selector) const;
  void set_style_line_dash_width(int32_t value,
                                 lv_style_selector_t selector) const;
  void set_style_line_dash_gap(int32_t value,
                               lv_style_selector_t selector) const;
  void set_style_line_rounded(bool value, lv_style_selector_t selector) const;
  void set_style_line_color(lv_color_t value,
                            lv_style_selector_t selector) const;
  void set_style_line_opa(lv_opa_t value, lv_style_selector_t selector) const;
  void set_style_arc_width(int32_t value, lv_style_selector_t selector) const;
  void set_style_arc_rounded(bool value, lv_style_selector_t selector) const;
  void set_style_arc_color(lv_color_t value,
                           lv_style_selector_t selector) const;
  void set_style_arc_opa(lv_opa_t value, lv_style_selector_t selector) const;
  void set_style_arc_image_src(const void *value,
                               lv_style_selector_t selector) const;
  void set_style_text_color(lv_color_t value,
                            lv_style_selector_t selector) const;
  void set_style_text_opa(lv_opa_t value, lv_style_selector_t selector) const;
  void set_style_text_font(const lv_font_t *value,
                           lv_style_selector_t selector) const;
  void set_style_text_letter_space(int32_t value,
                                   lv_style_selector_t selector) const;
  void set_style_text_line_space(int32_t value,
                                 lv_style_selector_t selector) const;
  void set_style_text_decor(lv_text_decor_t value,
                            lv_style_selector_t selector) const;
  void set_style_text_align(lv_text_align_t value,
                            lv_style_selector_t selector) const;
  void set_style_radius(int32_t value, lv_style_selector_t selector) const;
  void set_style_radial_offset(int32_t value,
                               lv_style_selector_t selector) const;
  void set_style_clip_corner(bool value, lv_style_selector_t selector) const;
  void set_style_opa(lv_opa_t value, lv_style_selector_t selector) const;
  void set_style_opa_layered(lv_opa_t value,
                             lv_style_selector_t selector) const;
  void set_style_color_filter_dsc(const lv_color_filter_dsc_t *value,
                                  lv_style_selector_t selector) const;
  void set_style_color_filter_opa(lv_opa_t value,
                                  lv_style_selector_t selector) const;
  void set_style_anim(const lv_anim_t *value,
                      lv_style_selector_t selector) const;
  void set_style_anim_duration(uint32_t value,
                               lv_style_selector_t selector) const;
  void set_style_transition(const lv_style_transition_dsc_t *value,
                            lv_style_selector_t selector) const;
  void set_style_blend_mode(lv_blend_mode_t value,
                            lv_style_selector_t selector) const;
  void set_style_layout(uint16_t value, lv_style_selector_t selector) const;
  void set_style_base_dir(lv_base_dir_t value,
                          lv_style_selector_t selector) const;
  void set_style_bitmap_mask_src(const void *value,
                                 lv_style_selector_t selector) const;
  void set_style_rotary_sensitivity(uint32_t value,
                                    lv_style_selector_t selector) const;
  void set_style_flex_flow(lv_flex_flow_t value,
                           lv_style_selector_t selector) const;
  void set_style_flex_main_place(lv_flex_align_t value,
                                 lv_style_selector_t selector) const;
  void set_style_flex_cross_place(lv_flex_align_t value,
                                  lv_style_selector_t selector) const;
  void set_style_flex_track_place(lv_flex_align_t value,
                                  lv_style_selector_t selector) const;
  void set_style_flex_grow(uint8_t value, lv_style_selector_t selector) const;
  void set_style_grid_column_dsc_array(const int32_t *value,
                                       lv_style_selector_t selector) const;
  void set_style_grid_column_align(lv_grid_align_t value,
                                   lv_style_selector_t selector) const;
  void set_style_grid_row_dsc_array(const int32_t *value,
                                    lv_style_selector_t selector) const;
  void set_style_grid_row_align(lv_grid_align_t value,
                                lv_style_selector_t selector) const;
  void set_style_grid_cell_column_pos(int32_t value,
                                      lv_style_selector_t selector) const;
  void set_style_grid_cell_x_align(lv_grid_align_t value,
                                   lv_style_selector_t selector) const;
  void set_style_grid_cell_column_span(int32_t value,
                                       lv_style_selector_t selector) const;
  void set_style_grid_cell_row_pos(int32_t value,
                                   lv_style_selector_t selector) const;
  void set_style_grid_cell_y_align(lv_grid_align_t value,
                                   lv_style_selector_t selector) const;
  void set_style_grid_cell_row_span(int32_t value,
                                    lv_style_selector_t selector) const;

  void delete_delayed(uint32_t delay_ms) const;
  void delete_async() const;
  void set_parent(lv_obj_t *parent) const;
  void swap(lv_obj_t *obj2) const;
  void move_to_index(int32_t index) const;
  void tree_walk(lv_obj_tree_walk_cb_t cb, void *user_data) const;
  void dump_tree() const;

  void style_create_transition(lv_part_t part, lv_state_t prev_state,
                               lv_state_t new_state,
                               const lv_obj_style_transition_dsc_t *tr) const;
  void update_layer_type() const;

  void redraw(lv_layer_t *layer) const;
};

} // namespace LVGLEx

#endif // LVGLEX_WIDGET_BASE_H
