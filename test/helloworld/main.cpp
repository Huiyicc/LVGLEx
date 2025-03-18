//
// Created by 19254 on 24-12-15.
//
#include <LVGLEx/LVGLEx.h>
#include <LVGLEx/logs.h>
#include <LVGLEx/widget/label.h>
#include <LVGLEx/widget_lvgl/group_box.h>
#include <iostream>
#include <thread>

class MyWindow : public LVGLEx::Window {
public:
  ~MyWindow() override = default;

  void onShow() override {
    std::cout << "Window Show" << std::endl;
  };

  void onCreate() override {
    std::cout << "Window Created" << std::endl;
  };

  void onDelete() override {

  };

  void onLoadStart() override {
    std::cout << "Window Load Start" << std::endl;
  };

  void onLoadEnd() override {
    std::cout << "Window Load End" << std::endl;
  };
};

int main() {
  LVGLEx::init();
  MyWindow win;
  win.setTitle("Hello World1");

  auto label = LVGLEx::Label::create(&win);
  label.setPos(20, 20);
  label.setText("Hello World");

  win.show();

  LVGLEx::runExec();
  LVGLEx::deInit();

  return 0;
}