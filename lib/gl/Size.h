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
