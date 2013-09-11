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
 * @file Bitmap.h
 * @brief The definition of the Bitmap structure
 * @ingroup GraphicsLibrary
 */

#pragma once


namespace lcd {

  /**
   * @brief Structure that defines a bitmap
   * @ingroup GraphicsLibrary
   */

  struct Bitmap {

    Size Dimensions;      ///< pixel Width,Height
    uint32_t Pixels;      ///< memory location. the choice of flash/sram is not mandated here
    uint32_t DataSize;    ///< byte-size of the buffer pointed to by the Pixels member

    /**
     * Default constructor
     */

    Bitmap()
      : Dimensions(), Pixels() {
    }
  };
}
