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
