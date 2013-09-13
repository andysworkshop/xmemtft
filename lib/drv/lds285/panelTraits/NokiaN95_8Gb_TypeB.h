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
 * @file NokiaN95_8Gb_TypeB.h
 * @brief Panel traits unique to the Nokia N95 8Gb Type B.
 *
 * See my website for documentation about the various panel types
 *
 * @ingroup LDS285
 */

#pragma once

#include "drv/lds285/commands/AllCommands.h"


namespace lcd {

  /**
   * Panel traits for a Type B Nokia N95 8Gb. The type B screen does
   * flip column and row addresses in portrait mode
   * @ingroup LDS285
   */

  class NokiaN95_8Gb_TypeB {
    public:
      template<Orientation TOrientation>
      static uint8_t getColumnAddressCommand();

      template<Orientation TOrientation>
      static uint8_t getRowAddressCommand();
  };


  /**
   * Get the command used to set column address in portrait mode
   * @return lds285::ROW_ADDRESS_SET
   */

  template<>
  inline uint8_t NokiaN95_8Gb_TypeB::getColumnAddressCommand<PORTRAIT>() {
    return lds285::ROW_ADDRESS_SET;
  }


  /**
   * Get the command used to set row address in portrait mode
   * @return lds285::ROW_ADDRESS_SET
   */

  template<>
  inline uint8_t NokiaN95_8Gb_TypeB::getRowAddressCommand<PORTRAIT>() {
    return lds285::COLUMN_ADDRESS_SET;
  }
}
