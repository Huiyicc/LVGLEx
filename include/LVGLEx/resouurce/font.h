//
// Created by 19254 on 24-12-16.
//

#ifndef LVGLEX_FONT_H
#define LVGLEX_FONT_H

#include <filesystem>
#include <memory>

namespace LVGLEx {

class Font {
  lv_font_t *m_font = nullptr;

public:
  explicit Font(lv_font_t *font) : m_font(font) {}

  ~Font();

  operator lv_font_t *() const { return m_font; };
  operator const lv_font_t *() const { return m_font; };


  /**
   * Get the descriptor of a glyph
   * @param dsc_out       store the result descriptor here
   * @param letter        a UNICODE letter code
   * @param letter_next   the next letter after `letter`. Used for kerning
   * @return true: descriptor is successfully loaded into `dsc_out`.
   *         false: the letter was not found, no data is loaded to `dsc_out`
   */
  bool GetGlyphDsc(lv_font_glyph_dsc_t * dsc_out, uint32_t letter,
                             uint32_t letter_next) const;

  static std::shared_ptr<Font>
  MakeFromFile(const std::filesystem::path &font_file, uint32_t size = 14,
                   lv_freetype_font_render_mode_t render_mode = LV_FREETYPE_FONT_RENDER_MODE_BITMAP, lv_freetype_font_style_t style = LV_FREETYPE_FONT_STYLE_NORMAL);
};

}// namespace LVGLEx

#endif//LVGLEX_FONT_H
