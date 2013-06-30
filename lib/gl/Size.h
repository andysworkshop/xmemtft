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
 * @file Size.h
 * @brief The definition of the Size structure
 * @ingroup GraphicsLibrary
 */

#pragma once


namespace lcd {

	/**
	 * @brief (width,height) size structure
	 */

	struct Size {

		/**
		 * The width and height
		 */

		int16_t Width,Height;


		/**
		 * Default constructor
		 */

		Size()
			: Width(), Height() {
		}


		/**
		 * Constructor with parameters
		 * @param width The width
		 * @param height The height
		 */

		Size(int16_t width,int16_t height) :
			Width(width),
			Height(height) {
		}


		/**
		 * Copy constructor
		 * @param src Where to copy from.
		 */

		Size(const Size& src) {
			Width=src.Width;
			Height=src.Height;
		}


		/**
		 * Get the area covered by this size
		 * @return The width multiplied by the height.
		 */

		uint32_t getArea() const {
			return static_cast<uint32_t>(Width)*static_cast<uint32_t>(Height);
		}
	};
}
