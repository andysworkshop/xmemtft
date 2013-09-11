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
 * @file NokiaN93_TypeA.h
 * @brief Panel-specific traits for the Nokia N93 Type A.
 * @ingroup MC2PA8201
 */

#pragma once

#include "drv/mc2pa8201/commands/AllCommands.h"


namespace lcd {

  /**
   * Panel traits for a Type A Nokia N93 panel
   *
   * 1. Hardware scrolling is not supported
   * 2. (page,column) addressing is not swapped for landscape mode
   * 3. Memory access control is handled
   * @ingroup MC2PA8201
   */

  class NokiaN93_TypeA {
    public:
      static int16_t normaliseScrollPosition(int16_t scrollPosition);

      template<Orientation TOrientation>
      static uint8_t getColumnAddressCommand();

      template<Orientation TOrientation>
      static uint8_t getPageAddressCommand();

      template<Orientation TOrientation>
      static uint8_t getMemoryAccessControl();

      template<Orientation TOrientation>
      static bool hasHardwareScrolling();

      static uint16_t getScrollHeight();
  };


  /**
   * Get the maximum scroll height of the display
   * @return 320
   */

  inline uint16_t NokiaN93_TypeA::getScrollHeight() {
    return 320;
  }


  /*
   * Hardware scrolling is not supported
   */

  template<Orientation TOrientation>
  inline bool NokiaN93_TypeA::hasHardwareScrolling() {
    return false;
  }


  /*
   * Normalise the scroll position for the setScrollPosition() call.
   * Scrolling is not supported (yet...) on the N93
   */

  inline int16_t NokiaN93_TypeA::normaliseScrollPosition(int16_t scrollPosition) {
    return scrollPosition;
  }


  /**
   * Get the command used to set column address in landscape mode
   * @return mc2pa8201::COLUMN_ADDRESS_SET
   */

  template<>
  inline uint8_t NokiaN93_TypeA::getColumnAddressCommand<LANDSCAPE>() {
    return mc2pa8201::COLUMN_ADDRESS_SET;
  }


  /**
   * Get the command used to set column address in landscape mode
   * @return mc2pa8201::PAGE_ADDRESS_SET
   */

  template<>
  inline uint8_t NokiaN93_TypeA::getPageAddressCommand<LANDSCAPE>() {
    return mc2pa8201::PAGE_ADDRESS_SET;
  }


  /**
   * Get the parameter to the MEMORY_ACCESS_CONTROL command
   * @return 0x50
   */

  template<>
  inline uint8_t NokiaN93_TypeA::getMemoryAccessControl<PORTRAIT>() {
    return 0x50;
  }


  /**
   * Get the parameter to the MEMORY_ACCESS_CONTROL command
   * @return 0x60
   */

  template<>
  inline uint8_t NokiaN93_TypeA::getMemoryAccessControl<LANDSCAPE>() {
    return 0x60;
  }
}
