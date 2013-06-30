/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012,2013 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
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
			uint8_t _characterCount;
			uint8_t _height;
			uint8_t _characterSpacing;
			uint8_t _firstCharacter;
			const struct FontChar * _characters;

		public:
			FontBase(FontType type,uint8_t firstChar,uint8_t characterCount,uint8_t height,uint8_t spacing,const struct FontChar *characters);

			void getCharacter(uint8_t character,FontChar& fc) const;
			uint16_t getId() const;
			uint8_t getHeight() const;
			uint8_t getCharacterSpacing() const;
			FontType getType() const;
	};


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

			Font(uint8_t firstChar,uint8_t characterCount,uint8_t height,uint8_t spacing,const struct FontChar *characters)
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

			LzgFont(uint8_t firstChar,uint8_t characterCount,uint8_t height,uint8_t spacing,const struct FontChar *characters)
				: FontBase(FONT_LZG,firstChar,characterCount,height,spacing,characters) {
			}
	};
}
