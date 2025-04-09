//
// Created by 19254 on 24-12-15.
//
#include <LVGLEx/LVGLEx.h>
#include <iostream>
#include <misc/lv_event_private.h>
#include <thread>

class MyWindow : public LVGLEx::Window {
public:
  ~MyWindow() override = default;

  void onShow() override { std::cout << "Window Show" << std::endl; };

  void onCreate() override { std::cout << "Window Created" << std::endl; };

  void onDelete() override {

  };

  void onLoadStart() override {
    std::cout << "Window Load Start" << std::endl;
  };

  void onLoadEnd() override { std::cout << "Window Load End" << std::endl; };
};

int main() {
  LVGLEx::init();
  MyWindow win;
  win.setTitle("Hello World1");

  // auto button = LVGLEx::Button::create(&win);
  // button.setPos(20, 60);
  // button.addEvent(LV_EVENT_ALL, [](LVGLEx::WidgetEvent &event) {
  //   std::cout << event->code << std::endl;
  // }, nullptr);
  // {
  //   auto lobj = button.getObj();
  //   lv_obj_add_event_cb(lobj,[](lv_event_t *e) {
  //     std::cout << lv_event_get_code(e) << std::endl;
  //   },LV_EVENT_ALL, nullptr);
  //   lv_obj_add_flag(lobj, LV_OBJ_FLAG_CHECKABLE);
  //   lv_obj_set_height(lobj, LV_SIZE_CONTENT);
  // }
  //
  // auto label = LVGLEx::Label::create(&button);
  // label.align(LV_ALIGN_CENTER, 0, 0);
  // label.setText("Hello World");



  lv_obj_t *btn2 = lv_button_create(win.getScreenActive().get());
  lv_obj_add_event_cb(
      btn2,
      [](lv_event_t *e) { std::cout << lv_event_get_code(e) << std::endl; },
      LV_EVENT_ALL, NULL);
  lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 40);
  lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
  lv_obj_set_height(btn2, LV_SIZE_CONTENT);
  auto label = lv_label_create(btn2);
  lv_label_set_text(label, "Toggle");

  lv_obj_t * ta = lv_textarea_create(win.getScreenActive().get());
  lv_textarea_set_one_line(ta, true);
  lv_textarea_set_placeholder_text(ta, "Your name");


  win.show();

  LVGLEx::runExec();
  LVGLEx::deInit();

  return 0;
}