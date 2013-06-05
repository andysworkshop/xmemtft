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


namespace lcd {

	/**
	 *  A Single font character definition
	 */

	struct FontChar {
		// The character code
		uint8_t Code;

		// Pixel width of this char (limit 255 pixels)
		uint8_t PixelWidth;

		// Bit-stream of data packed left to right, top to bottom
		const uint8_t* Data;
	};
}
