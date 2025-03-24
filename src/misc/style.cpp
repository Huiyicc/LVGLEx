//
// Created by 19254 on 25-3-18.
//
#include "LVGLEx/misc/style.h"

namespace LVGLEx {

void Style::StylePointerDeleter::operator()(lv_style_t *ptr) const {
  if (ptr) {
    delete ptr;
  }
}

Style::Style() : m_style(new lv_style_t) {};
Style::Style(const lv_style_t &matrix) {
  m_style = StylePointer::makeQuote(&matrix);
};
Style::Style(const lv_style_t *matrix) {
  m_style = StylePointer::makeQuote(matrix);
};
Style::Style(const Style &matrix) {
  m_style = StylePointer::makePrivatePtr(new lv_style_t{0});
  *m_style = *matrix.m_style;
};

Style::~Style() = default;
Style &Style::operator=(const Style &data) {
  m_style = StylePointer::makePrivatePtr(new lv_style_t{0});
  *m_style = *data.m_style;
  return *this;
};

const lv_style_t *Style::get() const { return m_style.get(); }

lv_style_t *Style::getPtr() { return m_style.get(); }

void Style::reset() { lv_style_reset(m_style.get()); }

bool Style::isConst() const { return lv_style_is_const(m_style.get()); }

lv_style_prop_t Style::registerProp(uint8_t flag) {
  return lv_style_register_prop(flag);
}

lv_style_prop_t Style::getNumCustomProps() {
  return lv_style_get_num_custom_props();
}

bool Style::removeProp(lv_style_prop_t prop) const {
  return lv_style_remove_prop(m_style.get(), prop);
}

void Style::setProp(lv_style_prop_t prop, lv_style_value_t value) const {
  lv_style_set_prop(m_style.get(), prop, value);
}

lv_style_res_t Style::getProp(lv_style_prop_t prop,
                              lv_style_value_t *value) const {
  return lv_style_get_prop(m_style.get(), prop, value);
}

void Style::transitionDscInit(lv_style_transition_dsc_t *tr,
                              const lv_style_prop_t props[],
                              lv_anim_path_cb_t path_cb, uint32_t time,
                              uint32_t delay, void *user_data) {
  lv_style_transition_dsc_init(tr, props, path_cb, time, delay, user_data);
}

lv_style_value_t Style::propGetDefault(lv_style_prop_t prop) {
  return lv_style_prop_get_default(prop);
}

lv_style_res_t Style::getPropInlined(lv_style_prop_t prop,
                                     lv_style_value_t *value) const {
  return lv_style_get_prop_inlined(m_style.get(), prop, value);
}

bool Style::isEmpty() const { return lv_style_is_empty(m_style.get()); }

uint32_t Style::getPropGroup(lv_style_prop_t prop) {
  return lv_style_get_prop_group(prop);
}

uint8_t Style::propLookupFlags(lv_style_prop_t prop) {
  return lv_style_prop_lookup_flags(prop);
}

void Style::setSize(int32_t width, int32_t height) const {
  lv_style_set_size(m_style.get(), width, height);
}

void Style::setPadAll(int32_t value) const {
  lv_style_set_pad_all(m_style.get(), value);
}

void Style::setPadHor(int32_t value) const {
  lv_style_set_pad_hor(m_style.get(), value);
}

void Style::setPadVer(int32_t value) const {
  lv_style_set_pad_ver(m_style.get(), value);
}

void Style::setPadGap(int32_t value) const {
  lv_style_set_pad_gap(m_style.get(), value);
}

void Style::setMarginHor(int32_t value) const {
  lv_style_set_margin_hor(m_style.get(), value);
}

void Style::setMarginVer(int32_t value) const {
  lv_style_set_margin_ver(m_style.get(), value);
}

void Style::setMarginAll(int32_t value) const {
  lv_style_set_margin_all(m_style.get(), value);
}

void Style::setTransformScale(int32_t value) const {
  lv_style_set_transform_scale(m_style.get(), value);
}

bool Style::propHasFlag(lv_style_prop_t prop, uint8_t flag) {
  return lv_style_prop_has_flag(prop, flag);
}

} // namespace LVGLEx