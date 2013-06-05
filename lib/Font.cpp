/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012,2013 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

#include <avr/pgmspace.h>
#include <stdlib.h>
#include <stddef.h>
#include "Font.h"


namespace lcd {

	/*
	 * Constructor
	 */

	FontBase::FontBase(FontType type,uint8_t firstChar,uint8_t characterCount,uint8_t height,uint8_t spacing,const struct FontChar *characters) {

		_fontType=type;
		_characterCount=characterCount;
		_firstCharacter=firstChar;
		_height=height;
		_characterSpacing=spacing;
		_characters=characters;
	}


	/*
	 * Get the font character definition in progmem space
	 */

	void FontBase::getCharacter(uint8_t character,FontChar& fc) const {

		const FontChar *ptr;
		uint8_t c;
		int16_t i;

		// the bulk of the characters are in sequential order, see if we can
		// index directly into the character array to find it

		if(character-_firstCharacter<_characterCount) {

			// don't try this at home kids...

			ptr=&_characters[character-_firstCharacter];
			c=pgm_read_byte(reinterpret_cast<const uint8_t *>(ptr)+offsetof(FontChar,Code));

			// ...ok you can start looking again

			if(c==character) {
				memcpy_P(&fc,ptr,sizeof(FontChar));
				return;
			}
		}

		// did't find it, search for it going backwards because the likelihood is that
		// it's towards the end of the array

		for(i=_characterCount-1;i>=0;i--) {

			// this is the stuff that gives C a bad name...

			ptr=&_characters[i];
			c=pgm_read_byte(reinterpret_cast<const uint8_t *>(ptr)+offsetof(FontChar,Code));

			// ...ok you can start looking again

			if(c==character) {
				memcpy_P(&fc,ptr,sizeof(FontChar));
				return;
			}
		}

		ptr=&_characters[1]; 		// default to first char if not found
		memcpy_P(&fc,ptr,sizeof(fc));
	}

	/**
	 * Get the font height in pixels.
	 */

	uint8_t FontBase::getHeight() const {
		return _height;
	}


	/**
	 * Get the inter-character spacing
	 */

	uint8_t FontBase::getCharacterSpacing() const {
		return _characterSpacing;
	}


	/**
	 * Get the font type
	 */

	FontBase::FontType FontBase::getType() const {
		return _fontType;
	}
}
