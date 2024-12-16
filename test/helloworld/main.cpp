//
// Created by 19254 on 24-12-15.
//
#include <LVGLEx/LVGLEx.h>
#include <LVGLEx/widget/label.h>
#include <iostream>

class MyWindow : public LVGLEx::Window {
public:
  ~MyWindow() override = default;

  void OnCreate() override {
    std::cout << "Window Created" << std::endl;
  };

  void OnDelete() override {

  };

  void OnLoadStart() override {
    std::cout << "Window Load Start" << std::endl;
  };

  void OnLoadEnd() override {
    std::cout << "Window Load End" << std::endl;
  };
};

int main() {
  LVGLEx::Init();
  MyWindow win;

  auto label = LVGLEx::Label::Create(&win);
  label->SetPos<LVGLEx::Label>(20, 20)
    ->SetText("Hello World");

  win.Show();
  LVGLEx::Run();

  LVGLEx::DeInit();

  return 0;
}