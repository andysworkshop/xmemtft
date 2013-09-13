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

/**
 * @file Rectangle.h
 * @brief The definition of the Rectangle structure
 * @ingroup GraphicsLibrary
 */

#pragma once

#include "Point.h"
#include "Size.h"


namespace lcd {

  /**
   * @brief (X,Y,Width,Height) rectangle structure
   */

  struct Rectangle {

    /**
     * The co-ords and sizes
     */

    int16_t X,Y,Width,Height;


    /**
     * Default constructor. X, Y, width, height = zero.
     */

    Rectangle()
      : X(), Y(), Width(), Height() {

    }


    /**
     * Constructor. Set up the parameters.
     * @param x The upper-left x-coord.
     * @param y The upper-left y-coord.
     * @param width The width in pixels.
     * @param height The height in pixels.
     */

    Rectangle(int16_t x,int16_t y,int16_t width,int16_t height) {
      X=x;
      Y=y;
      Width=width;
      Height=height;
    }


    /**
     * Constructor with top-left co-ord and size
     * @param p The co-ord of the top-left.
     * @param size The width and height
     */

    Rectangle(const Point& p,const Size& size) {
      X=p.X;
      Y=p.Y;
      Width=size.Width;
      Height=size.Height;
    }


    /**
     * Copy constructor
     * @param src The rectangle to copy from
     */

    Rectangle(const Rectangle& src) {
      X=src.X;
      Y=src.Y;
      Width=src.Width;
      Height=src.Height;
    }


    /**
     * Get the size of the rectangle
     * @return a Size structure containing the size.
     */

    Size getSize() const {
      Size s;

      s.Width=Width;
      s.Height=Height;

      return s;
    }


    /**
     * Get the top-left corner
     * @return A Point structure containing the top-left.
     */

    Point getTopLeft() const {
      Point p;

      p.X=X;
      p.Y=Y;

      return p;
    }


    /**
     * Get the right X co-ord
     * @return The right-edge x co-ord.
     */

    int16_t Right() const {
      return X+Width-1;
    }


    /**
     * Get the bottom Y co-ord
     * @return The bottom edge y co-ord.
     */

    int16_t Bottom() const {
      return Y+Height-1;
    }


    /**
     * Check if the given point is contained in this rectangle.
     * @param p The point to check for containment.
     * @return true if is contained
     */

    bool containsPoint(const Point& p) const {
      return p.X>=X && p.X<=X+Width && p.Y>=Y && p.Y<=Y+Height;
    }
  };


  /**
   * @brief Subclass of Rectangle that handles negative sizes.
   *
   * This subclass of Rectangle can be used wherever you may have rectangles with
   * a negative width or height. The constructor adjusts the position and sizes
   * accordingly so that they are all positive. The original negative dimensions
   * are not retained.
   */

  struct NormalizedRectangle : public Rectangle {

    /**
     * Constructor
     * @param x The x-coord. Positive only.
     * @param y The y-coord. Positive only.
     * @param width The width. May be negative.
     * @param height The height. May be negative.
     */

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
