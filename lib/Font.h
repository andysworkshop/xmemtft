/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012,2013 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

#pragma once

#include <stdint.h>
#include "FontChar.h"


namespace lcd {

	/**
	 * Generic implementation of a font that's represented by bits in memory. The caller gets to decide how to
	 * deal with those bits
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

	// stub types to allow method overloading in the GraphicsLibrary class. this first one is for
	// bitmap fonts - the original font format

	class Font : public FontBase {
		public:
			Font(uint8_t firstChar,uint8_t characterCount,uint8_t height,uint8_t spacing,const struct FontChar *characters)
				: FontBase(FONT_BITMAP,firstChar,characterCount,height,spacing,characters) {
			}
	};

	// and this one is for the Lzg TrueType fonts

	class LzgFont : public FontBase {
		public:
			LzgFont(uint8_t firstChar,uint8_t characterCount,uint8_t height,uint8_t spacing,const struct FontChar *characters)
				: FontBase(FONT_LZG,firstChar,characterCount,height,spacing,characters) {
			}
	};
}
