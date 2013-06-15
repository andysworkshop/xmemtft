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


namespace lcd {

	/**
	 * (x,y) co-ordinate structure
	 */

	struct Point {

			int16_t X,Y;

			/**
			 * Return a (0,0) point.
			 */

			static const Point Origin;

			/*
			 * Default constructor
			 */

			Point()
			 : X(), Y() {
			}

			/*
			 * Constructor with parameters
			 */

			Point(int16_t x,int16_t y) {
				X=x;
				Y=y;
			}

			/*
			 * Copy constructor
			 */

			Point(const Point& p) {
				X=p.X;
				Y=p.Y;
			}
		};
}
