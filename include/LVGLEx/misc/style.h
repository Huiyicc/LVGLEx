//
// Created by 19254 on 25-3-18.
//

#ifndef LVGLEX_MISC_STYLE_H
#define LVGLEX_MISC_STYLE_H

#include "misc/lv_style.h"

namespace LVGLEx {

class Style {
private:
    lv_style_t m_style;
public:
    Style();
    Style(const lv_style_t *style);
    Style(const lv_style_t &style);
    Style(const Style &style);
    ~Style();

    const lv_style_t *get() const;
    lv_style_t *getPtr();

};

}

#endif //LVGLEX_MISC_STYLE_H
