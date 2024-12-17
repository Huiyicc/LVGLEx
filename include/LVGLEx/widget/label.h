//
// Created by 19254 on 24-12-16.
//

#ifndef LVGLEX_WIDGET_LABEL_H
#define LVGLEX_WIDGET_LABEL_H

#include "widget_base.h"
#include <memory>
#include <string>

namespace LVGLEx {

class Label : public WidgetBase {

public:
  Label();
  ~Label() override;

  static Label* create(WidgetBase* parent);
  static Label* create(WindowBase* parent);

  Label* set_text(const std::string& text);

};

}// namespace LVGLEx


#endif//LVGLEX_WIDGET_LABEL_H
