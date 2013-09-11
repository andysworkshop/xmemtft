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
 * @file DoublePrecision.h
 * @brief Management class for floating point output
 * @ingroup GraphicsLibrary
 */

#pragma once


/**
 * @brief Carrier class for a double and it's desired output precision.
 *
 * This class is used for text output so that you can specify how precise
 * you need the output to be.
 *
 * @ingroup GraphicsLibrary
 */

struct DoublePrecision {

  // public members

  double Value;           ///< The floating point value
  uint8_t Precision;      ///< The desired number of fractional digits

  /**
   * Constructor. Must be fully constructed.
   * @param d The double-precision value
   * @param precision The desired number of fractional digits
   */

  DoublePrecision(double d,uint8_t precision) {
    Value=d;
    Precision=precision;
  }
};
