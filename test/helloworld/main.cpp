//
// Created by 19254 on 24-12-15.
//
#include <LVGLEx/LVGLEx.h>
#include <LVGLEx/widget/label.h>
#include <iostream>

class MyWindow : public LVGLEx::Window {
public:
  ~MyWindow() override = default;

  void on_create() override {
    std::cout << "Window Created" << std::endl;
  };

  void on_delete() override {

  };

  void on_load_start() override {
    std::cout << "Window Load Start" << std::endl;
  };

  void on_load_end() override {
    std::cout << "Window Load End" << std::endl;
  };
};

int main() {
  LVGLEx::Init();
  MyWindow win;

  auto label = LVGLEx::Label::create(&win);
  label->set_pos(20, 20);
  label->set_text("Hello World");

  win.show();
  LVGLEx::Run();

  LVGLEx::DeInit();

  return 0;
}