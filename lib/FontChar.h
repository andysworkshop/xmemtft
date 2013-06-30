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
 * @file FontChar.h
 * @brief FontChar definition.
 * @ingroup Fonts
 */

#pragma once

#include <stdint.h>


namespace lcd {

	/**
	 * @brief A Single font character definition
	 * @ingroup Fonts
	 */

	struct FontChar {
		uint8_t Code;						///< The character code
		uint8_t PixelWidth;			///< Pixel width of this char (limit 255 pixels)
		const uint8_t* Data;		///< Bit-stream of data packed left to right, top to bottom
	};
}
