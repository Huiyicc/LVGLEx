//
// Created by 19254 on 25-1-12.
//
#include "LVGLEx/widget_lvgl/group_box.h"

#include <core/lv_obj.h>
#include <misc/lv_types.h>
#include <widgets/button/lv_button.h>
#include <widgets/label/lv_label.h>

lv_obj_t * create_group_box(lv_obj_t * parent, const char * title) {
  // Create a container for the group box
  lv_obj_t * group_box = lv_obj_create(parent);
  lv_obj_set_size(group_box, 200, 150);  // Set size of the group box
  lv_obj_set_style_pad_all(group_box, 10, 0);  // Add padding
  lv_obj_set_style_border_width(group_box, 2, 0);  // Set border width
  lv_obj_set_style_border_color(group_box, lv_palette_main(LV_PALETTE_BLUE), 0);  // Set border color
  lv_obj_set_style_radius(group_box, 5, 0);  // Set rounded corners

  // Create a label for the title
  lv_obj_t * title_label = lv_label_create(group_box);
  lv_label_set_text(title_label, title);
  lv_obj_align(title_label, LV_ALIGN_TOP_MID, 0, 5);  // Align the title to the top center

  // Create a content container inside the group box
  lv_obj_t * content_container = lv_obj_create(group_box);
  lv_obj_set_size(content_container, lv_obj_get_width(group_box) - 20, lv_obj_get_height(group_box) - 40);
  lv_obj_align(content_container, LV_ALIGN_BOTTOM_MID, 0, -10);  // Align at the bottom
  lv_obj_set_style_pad_all(content_container, 5, 0);
  lv_obj_set_scrollbar_mode(content_container, LV_SCROLLBAR_MODE_OFF);  // Disable scrollbars

  // Add child widgets to the content container
  lv_obj_t * btn1 = lv_button_create(content_container);
  lv_obj_align(btn1, LV_ALIGN_TOP_LEFT, 10, 10);
  lv_obj_t * btn1_label = lv_label_create(btn1);
  lv_label_set_text(btn1_label, "Button 1");

  lv_obj_t * btn2 = lv_button_create(content_container);
  lv_obj_align(btn2, LV_ALIGN_TOP_RIGHT, -10, 10);
  lv_obj_t * btn2_label = lv_label_create(btn2);
  lv_label_set_text(btn2_label, "Button 2");

  return group_box;
}