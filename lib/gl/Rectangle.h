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

#include "Point.h"
#include "Size.h"


namespace lcd {

	/**
	 * (X,Y,Width,Height) rectangle structure
	 */

	struct Rectangle {

			int16_t X,Y,Width,Height;

			/*
			 * Default constructor
			 */

			Rectangle()
				: X(), Y(), Width(), Height() {

			}

			/**
			 * Constructor. Set up the parameters.
			 */

			Rectangle(int16_t x,int16_t y,int16_t width,int16_t height) {
				X=x;
				Y=y;
				Width=width;
				Height=height;
			}


			/**
			 * Constructor with top-left co-ord and size
			 */

			Rectangle(const Point& p,const Size& size) {
				X=p.X;
				Y=p.Y;
				Width=size.Width;
				Height=size.Height;
			}

			/*
			 * Copy constructor
			 */

			Rectangle(const Rectangle& src) {
				X=src.X;
				Y=src.Y;
				Width=src.Width;
				Height=src.Height;
			}

			/**
			 * Get the size of the rectangle
			 */

			Size getSize() const {
				Size s;

				s.Width=Width;
				s.Height=Height;

				return s;
			}


			/**
			 * Get the top-left corner
			 */

			Point getTopLeft() const {
				Point p;

				p.X=X;
				p.Y=Y;

				return p;
			}


			/**
			 * Get the right X co-ord
			 */

			int16_t Right() const {
				return X+Width-1;
			}


			/**
			 * Get the bottom Y co-ord
			 */

			int16_t Bottom() const {
				return Y+Height-1;
			}


			/**
			 * Check if the given point is contained in this rectangle
			 * @return true if is contained
			 */

			bool containsPoint(const Point& p) const {
				return p.X>=X && p.X<=X+Width && p.Y>=Y && p.Y<=Y+Height;
			}
	};


	struct NormalizedRectangle : public Rectangle {

		public:
			NormalizedRectangle(int16_t x,int16_t y,int16_t width,int16_t height)
				: Rectangle(x,y,width,height) {

				if(Height<0) {
					Y+=(height+1);
					Height=-Height;
				}

				if(Width<0) {
					X+=(Width+1);
					Width=-Width;
				}
			}
	};
}
