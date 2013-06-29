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

		// optimisation for straight lines. filling rectangles is much more efficient than plotting points

		if(p1.X==p2.X)
			fillRectangle(Rectangle(p1.X,Min(p1.Y,p2.Y),1,Abs(p2.Y-p1.Y)+1));
		else if(p1.Y==p2.Y)
			fillRectangle(Rectangle(Min(p1.X,p2.X),p1.Y,Abs(p2.X-p1.X)+1,1));
		else {

			int16_t x0,x1,y0,y1;

			x0=p1.X;
			y0=p1.Y;
			x1=p2.X;
			y1=p2.Y;

			if(x0>x1) {

				// the optimiser does this swap method faster than
				// the xor-trick

				int16_t t;

				t=x0;
				x0=x1;
				x1=t;

				t=y0;
				y0=y1;
				y1=t;
			}

			// calculate constants up-front

			int16_t dx=x1-x0;
			int16_t dy=Abs(y1-y0);
			int16_t sy=y0<y1 ? 1 : -1;
			int16_t mdy=-dy;
			int16_t err=dx-dy;
			bool xinc;

			// set the drawing rectangle that we need and plot the first point

			this->moveTo(x0,y0,this->getXmax(),this->getYmax());
			this->beginWriting();
			this->writePixel(_foreground);

			while(x0!=x1 || y0!=y1) {

				int16_t e2=2*err;

				if(e2>mdy) {

					err-=dy;
					x0++;

					// make a note that X has incremented

					xinc=true;
				}
				else
					xinc=false;				// nothing happened to X

				if(x0==x1 && y0==y1) {

					if(xinc) {

						// plot the pending X increment before returning

						this->writePixelAgain(_foreground);
						break;
					}
				}

				if(e2<dx) {
					err+=dx;
					y0+=sy;

					// Y has changed. We're going to have to do a complete
					// pixel write after we've moved the bare minimum of
					// window pointers

					if(xinc)
						this->moveX(x0,this->getXmax());

					this->moveY(y0,this->getYmax());

					this->beginWriting();
					this->writePixel(_foreground);
				}
				else {

					// Y has not changed, if X has changed then all we need
					// to do is push out another pixel

					if(xinc)
						this->writePixelAgain(_foreground);
				}
			}
		}
	}
}
