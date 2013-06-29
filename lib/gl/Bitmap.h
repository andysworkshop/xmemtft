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
 * @file Bitmap.h
 * @brief The definition of the Bitmap structure
 * @ingroup GraphicsLibrary
 */

#pragma once


namespace lcd {

	/**
	 * @brief Structure that defines a bitmap
	 * @ingroup GraphicsLibrary
	 */

	struct Bitmap {

		Size Dimensions;			///< pixel Width,Height
		uint32_t Pixels;			///< memory location. the choice of flash/sram is not mandated here
		uint32_t DataSize;		///< byte-size of the buffer pointed to by the Pixels member

		/**
		 * Default constructor
		 */

		Bitmap()
			: Dimensions(), Pixels() {
		}
	};
}
