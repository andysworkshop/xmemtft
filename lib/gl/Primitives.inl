/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

#pragma once


namespace lcd {

	/*
	 * plot a point in the foreground colour
	 */

	template<class TDevice,class TAccessMode>
	inline void GraphicsLibrary<TDevice,TAccessMode>::plotPoint(const Point& p) const {
		plotPoint(p.X,p.Y);
	}

	template<class TDevice,class TAccessMode>
	inline void GraphicsLibrary<TDevice,TAccessMode>::plotPoint(int16_t x,int16_t y) const {

		this->moveTo(
				Rectangle(
						x,
						y,
						1,
						1
				)
		);

		this->beginWriting();
		this->writePixel(_foreground);
	}


	/**
	 * Draw a line between two points. Uses the bresenham algorithm for lines that are not straight
   */

	template<class TDevice,class TAccessMode>
	inline void GraphicsLibrary<TDevice,TAccessMode>::drawLine(const Point& p1,const Point& p2) const {

		int16_t x0,x1,y0,y1,err,e2;
		int8_t sx,sy;

		x0=p1.X;
		x1=p2.X;
		y0=p1.Y;
		y1=p2.Y;

		// optimisation for straight lines. filling rectangles is much more efficient than plotting points

		if(x0==x1)
			fillRectangle(Rectangle(x0,Min(y0,y1),1,Abs(y1-y0)+1));
		else if(y0==y1)
			fillRectangle(Rectangle(Min(x0,x1),y0,Abs(x1-x0)+1,1));
		else {

			// can't optimise, use the algorithm

			int16_t dx=Abs(x0-x1);
			int16_t dy=Abs(y0-y1);

			if(x0<x1)
				sx=1;
			else
				sx=-1;

			if(y0<y1)
				sy=1;
			else
				sy=-1;

			err=dx-dy;

			for(;;) {

				plotPoint(x0,y0);

				if(x0==x1 && y0==y1)
					return;

				e2=2*err;

				if(e2>-dy) {
					err-=dy;
					x0+=sx;
				}

				if(x0==x1 && y0==y1) {
					plotPoint(x0,y0);
					return;
				}

				if(e2<dx) {
					err+=dx;
					y0+=sy;
				}
			}
		}
	}
}
