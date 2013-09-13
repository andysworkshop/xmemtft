/*
  XMEM LCD Library for the Arduino

  Copyright 2012,2013 Andrew Brown

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This notice may not be removed or altered from any source distribution.
*/

#pragma once


/**
 * @file Ellipse.inl
 * @brief Ellipse drawing functionality
 * @ingroup GraphicsLibrary
 */


namespace lcd {

  /**
   * @brief Fill an ellipse with the foreground colour.
   *
   * This is the algorithm documented in the paper "Drawing Ellipses Using Filled Rectangles" by L. Patrick.
   *
   * @param center The panel co-ords of the center of the ellipse.
   * @param size The size of the ellipse, expressed as its bounding rectangle with the center of that rectangle given by the 'center' parameter.
   */

  template<class TDevice,class TAccessMode>
  inline void GraphicsLibrary<TDevice,TAccessMode>::fillEllipse(const Point& center,const Size& size) const {

    int16_t x=0,y=size.Height;
    int16_t rx=x,ry=y;
    uint32_t width=1,height=1;
    int32_t a2=(int32_t)size.Width*(int32_t)size.Width,b2=(int32_t)size.Height*(int32_t)size.Height;
    int32_t crit1=-(a2 / 4 + size.Width % 2 + b2);
    int32_t crit2=-(b2 / 4 + size.Height % 2 + a2);
    int32_t crit3=-(b2 / 4 + size.Height % 2);
    int32_t t=-a2 * y; // e(x+1/2,y-1/2) - (width_^2+height_^2)/4
    int32_t dxt=2 * b2 * x,dyt=-2 * a2 * y;
    int32_t d2xt=2 * b2,d2yt=2 * a2;

    if(size.Height==0) {
      fillRectangle(NormalizedRectangle(center.X-size.Width,center.Y,2*size.Width+ 1,1));
      return;
    }

    while(y >= 0 && x <= size.Width) {
      if(t + b2 * x <= crit1 || /* e(x+1,y-1/2) <= 0 */
      t + a2 * y <= crit3) { /* e(x+1/2,y) <= 0 */
        if(height == 1) {}      // draw nothing
        else if(ry * 2 + 1 > ((int32_t)height - 1) * 2) {
          fillRectangle(NormalizedRectangle(center.X - rx,center.Y - ry,width,height - 1));
          fillRectangle(NormalizedRectangle(center.X - rx,center.Y + ry + 1,width,1 - height));
          ry-=height - 1;
          height=1;
        } else {
          fillRectangle(NormalizedRectangle(center.X - rx,center.Y - ry,width,ry * 2 + 1));
          ry-=ry;
          height=1;
        }
        x++,dxt+=d2xt,t+=dxt;
        rx++;
        width+=2;
      } else if(t - a2 * y > crit2) { /* e(x+1/2,y-1) > 0 */
        y--,dyt+=d2yt,t+=dyt;
        height++;
      } else {
        if(ry * 2 + 1 > (int32_t)height * 2) {
          fillRectangle(NormalizedRectangle(center.X - rx,center.Y - ry,width,height));
          fillRectangle(NormalizedRectangle(center.X - rx,center.Y + ry + 1,width,-height));
        } else {
          fillRectangle(NormalizedRectangle(center.X - rx,center.Y - ry,width,ry * 2 + 1));
        }
        x++,dxt+=d2xt,t+=dxt;
        y--,dyt+=d2yt,t+=dyt;
        rx++;
        width+=2;
        ry-=height;
        height=1;
      }
    }

    if(ry > (int32_t)height) {
      fillRectangle(NormalizedRectangle(center.X - rx,center.Y - ry,width,height));
      fillRectangle(NormalizedRectangle(center.X - rx,center.Y + ry + 1,width,-height));
    } else {
      fillRectangle(NormalizedRectangle(center.X - rx,center.Y - ry,width,ry * 2 + 2));
    }
  }


  /**
   * Draw an ellipse with the foreground colour using the fast bresenham algorithm. This method is an implementation of
   * the pseudo-code in the paper "A Fast Bresenham Type Algorithm For Drawing Ellipses" by John Kennedy.
   *
   * @param center The center point.
   * @param size The radius width and height.
   */

  template<class TDevice,class TAccessMode>
  inline void GraphicsLibrary<TDevice,TAccessMode>::drawEllipse(const Point& center,const Size& size) const {
    int32_t x,y,xchange,ychange,ellipseError,twoASquare,twoBSquare,stoppingX,stoppingY,width,height;

    width=size.Width;
    height=size.Height;

    twoASquare=2 * width * width;
    twoBSquare=2 * height * height;

    x=width;
    y=0;

    xchange=height * height * (1 - 2 * width);
    ychange=width * width;

    ellipseError=0;
    stoppingX=twoBSquare * width;
    stoppingY=0;

    while(stoppingX >= stoppingY) {

      plot4EllipsePoints(center.X,center.Y,x,y);
      y++;
      stoppingY+=twoASquare;
      ellipseError+=ychange;

      ychange+=twoASquare;

      if(2 * ellipseError + xchange > 0) {
        x--;
        stoppingX-=twoBSquare;
        ellipseError+=xchange;
        xchange+=twoBSquare;
      }
    }

    x=0;
    y=height;

    xchange=height * height;
    ychange=width * width * (1 - 2 * height);

    ellipseError=0;
    stoppingX=0;
    stoppingY=twoASquare * height;

    while(stoppingX <= stoppingY) {
      plot4EllipsePoints(center.X,center.Y,x,y);
      x++;
      stoppingX+=twoBSquare;
      ellipseError+=xchange;
      xchange+=twoBSquare;

      if((2 * ellipseError + ychange) > 0) {
        y--;
        stoppingY-=twoASquare;
        ellipseError+=ychange;
        ychange+=twoASquare;
      }
    }
  }


  /*
   * Utility function for the bresenham algorithm.
   */

  template<class TDevice,class TAccessMode>
  inline void GraphicsLibrary<TDevice,TAccessMode>::plot4EllipsePoints(int16_t cx,int16_t cy,int16_t x,int16_t y) const {

    plotPoint(Point(cx + x,cy + y)); // point in quadrant 1
    plotPoint(Point(cx - x,cy + y)); // point in quadrant 2
    plotPoint(Point(cx - x,cy - y)); // point in quadrant 3
    plotPoint(Point(cx + x,cy - y)); // point in quadrant 4
  }
}
