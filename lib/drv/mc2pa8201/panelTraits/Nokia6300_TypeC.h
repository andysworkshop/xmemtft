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
 * @file Nokia6300_TypeC.h
 * @brief Panel-specific traits for the Nokia 6300 Type C.
 * @ingroup MC2PA8201
 */

#pragma once


namespace lcd {

  /**
   * Panel traits for a Type C Nokia 6300 panel
   *
   * 1. Positive scroll offsets scroll downwards
   * 2. (page,column) addressing is not swapped for landscape mode
   * 3. RGB is the only transfer order supported
   * @ingroup MC2PA8201
   */

  class Nokia6300_TypeC {
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

  inline uint16_t Nokia6300_TypeC::getScrollHeight() {
    return 320;
  }


  /*
   * Hardware scrolling is supported
   */

  template<Orientation TOrientation>
  inline bool Nokia6300_TypeC::hasHardwareScrolling() {
    return true;
  }


  /*
   * Normalise the scroll position for the setScrollPosition() call
   */

  inline int16_t Nokia6300_TypeC::normaliseScrollPosition(int16_t scrollPosition) {
    return scrollPosition ? 320-scrollPosition : 0;
  }


  /**
   * Get the command used to set column address in landscape mode
   * @return mc2pa8201::PAGE_ADDRESS_SET
   */

  template<>
  inline uint8_t Nokia6300_TypeC::getColumnAddressCommand<LANDSCAPE>() {
    return mc2pa8201::PAGE_ADDRESS_SET;
  }


  /**
   * Get the command used to set column address in landscape mode
   * @return mc2pa8201::COLUMN_ADDRESS_SET
   */

  template<>
  inline uint8_t Nokia6300_TypeC::getPageAddressCommand<LANDSCAPE>() {
    return mc2pa8201::COLUMN_ADDRESS_SET;
  }


  /**
   * Get the parameter to the MEMORY_ACCESS_CONTROL command
   * @return 0xc0
   */

  template<>
  inline uint8_t Nokia6300_TypeC::getMemoryAccessControl<PORTRAIT>() {
    return 0xc0;
  }


  /**
   * Get the parameter to the MEMORY_ACCESS_CONTROL command
   * @return 0xa0
   */

  template<>
  inline uint8_t Nokia6300_TypeC::getMemoryAccessControl<LANDSCAPE>() {
    return 0xa0;
  }
}
