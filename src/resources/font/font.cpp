//
// Created by 19254 on 24-12-16.
//
#include <LVGLEx/LVGLEx.h>

namespace LVGLEx {

Font::~Font() {
  // 喵了个咪的,lvgl居然会自己释放...
  // 反直觉的用法
  // 不怕内存溢出?🤔

  // if (m_font) {
  //   lv_freetype_font_delete(m_font);
  // }
};

/**
 * Get the descriptor of a glyph
 * @param dsc_out       store the result descriptor here
 * @param letter        a UNICODE letter code
 * @param letter_next   the next letter after `letter`. Used for kerning
 * @return true: descriptor is successfully loaded into `dsc_out`.
 *         false: the letter was not found, no data is loaded to `dsc_out`
 */
bool Font::GetGlyphDsc(lv_font_glyph_dsc_t *dsc_out, uint32_t letter,
                       uint32_t letter_next) const {
  return lv_font_get_glyph_dsc(m_font, dsc_out, letter, letter_next);
};

std::shared_ptr<Font>
Font::MakeFromFile(const std::filesystem::path &font_file, uint32_t size,
                   lv_freetype_font_render_mode_t render_mode, lv_freetype_font_style_t style) {
  auto font = lv_freetype_font_create(font_file.string().c_str(),
                                      render_mode,
                                      size,
                                      style);
  return std::make_shared<Font>(font);
};

}// namespace LVGLEx
