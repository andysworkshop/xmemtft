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
 * @file Point.h
 * @brief The definition of the Point structure
 * @ingroup GraphicsLibrary
 */


#pragma once


namespace lcd {

	/**
	 * @brief (x,y) co-ordinate structure
	 * @ingroup GraphicsLibrary
	 */

	struct Point {

		/**
		 * @brief X and Y co-ordinates as signed values
		 *
		 * The actual permitted display values are unsigned. We keep them as signed to allow
		 * intermediate calculations using points to go negative.
		 */

		int16_t X,Y;


		/**
		 * Return a (0,0) point.
		 */

		static const Point Origin;


		/**
		 * Default constructor
		 */

		Point()
		 : X(), Y() {
		}


		/**
		 * Constructor with parameters
		 * @param x X-coord
		 * @param y Y-coord
		 */

		Point(int16_t x,int16_t y) {
			X=x;
			Y=y;
		}


		/**
		 * Copy constructor
		 * @param p The point to copy from
		 */

		Point(const Point& p) {
			X=p.X;
			Y=p.Y;
		}
	};
}
