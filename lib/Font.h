/*
  XMEM LCD Library for the Arduino

  Copyright 2012,2013 Andrew Brown

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This notice may not be removed or altered from any source distribution.
*/

/**
 * @defgroup Fonts
 * @brief Font functionality and structures.
 *
 * The graphics library provides the ability to manipulate TrueType fonts using the FontConv
 * and LzgFontConv utilities. The utilities allow you to optimise your memory usage by only
 * exporting the characters from the font that you require.
 */

/**
 * @file Font.h
 * @brief Font structures.
 * @ingroup Fonts
 */

#pragma once

#include <stdint.h>
#include "FontChar.h"


namespace lcd {

  /**
   * @brief Generic implementation of a font that's represented by bits in memory.
   * @ingroup Fonts
   */

  class FontBase {

    public:
      enum FontType {
        FONT_BITMAP,
        FONT_LZG
      } _fontType;

    protected:
      const struct FontChar * _characters;
      uint8_t _characterCount;
      uint8_t _firstCharacter;
      uint8_t _height;
      int8_t _characterSpacing;
      uint8_t _lastCharacter;

    public:
      FontBase(FontType type,uint8_t firstChar,uint8_t characterCount,uint8_t height,int8_t spacing,const struct FontChar *characters);

      void getCharacter(uint8_t character,FontChar& fc) const;
      uint16_t getId() const;
      uint8_t getHeight() const;
      int8_t getCharacterSpacing() const;
      FontType getType() const;
  };


  /**
   * Constructor
   * @param type FONT_BITMAP or FONT_LZG.
   * @param firstChar The first character in this font, usually an ASCII code.
   * @param characterCount The number of consecutive characters in this font.
   * @param height The font height in pixels.
   * @param spacing The spacing between characters in pixels.
   * @param characters A pointer to an array of FontChar structures that define each sequential character
   */

  inline FontBase::FontBase(FontType type,uint8_t firstChar,uint8_t characterCount,uint8_t height,int8_t spacing,const struct FontChar *characters)
    : _fontType(type),
      _characters(characters),
      _characterCount(characterCount),
      _firstCharacter(firstChar),
      _height(height),
      _characterSpacing(spacing) {

    _lastCharacter=_characters[characterCount-1].Code;
  }


  /**
   * Get the font height in pixels.
   * @return The height.
   */

  inline uint8_t FontBase::getHeight() const {
    return _height;
  }


  /**
   * Get the inter-character spacing
   * @return The additional space between characters.
   */

  inline int8_t FontBase::getCharacterSpacing() const {
    return _characterSpacing;
  }


  /**
   * Get the font type
   * @return FONT_BITMAP or FONT_LZG
   */

  inline FontBase::FontType FontBase::getType() const {
    return _fontType;
  }


  /**
   * @brief Bitmap font structure that can handle 8-bit fonts.
   *
   * FontConv creates instances of this class.
   *
   * @ingroup Fonts
   */

  class Font : public FontBase {
    public:

      /**
       * Constructor
       * @param firstChar The first character in this font, usually an ASCII code.
       * @param characterCount The number of consecutive characters in this font.
       * @param height The font height in pixels.
       * @param spacing The spacing between characters in pixels.
       * @param characters A pointer to an array of FontChar structures that define each sequential character
       */

      Font(uint8_t firstChar,uint8_t characterCount,uint8_t height,int8_t spacing,const struct FontChar *characters)
        : FontBase(FONT_BITMAP,firstChar,characterCount,height,spacing,characters) {
      }
  };


  /**
   * @brief LZG font structure that can handle complex TrueType font characters stored as bitmaps.
   *
   * LzgFontConv creates instances of this class.
   *
   * @ingroup Fonts
   */

  class LzgFont : public FontBase {
    public:

      /**
       * Constructor
       * @param firstChar The first character in this font, usually an ASCII code.
       * @param characterCount The number of consecutive characters in this font.
       * @param height The font height in pixels.
       * @param spacing The spacing between characters in pixels.
       * @param characters A pointer to an array of FontChar structures that define each sequential character
       */

      LzgFont(uint8_t firstChar,uint8_t characterCount,uint8_t height,int8_t spacing,const struct FontChar *characters)
        : FontBase(FONT_LZG,firstChar,characterCount,height,spacing,characters) {
      }
  };
}
