//
// Created by 19254 on 25-4-6.
//

#ifndef LVGLEX_WIDGET_BUTTON_H
#define LVGLEX_WIDGET_BUTTON_H

#include <LVGLEx/object/widget_base.h>

namespace LVGLEx {

class Button : public WidgetBase {

public:
  Button();
  ~Button() override;

  WIDGET_OBJ_CREATE_H(Button)

};

}

#endif // LVGLEX_WIDGET_BUTTON_H
