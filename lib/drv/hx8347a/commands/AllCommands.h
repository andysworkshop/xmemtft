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
 * @file Commands for the HX8347A that we use
 * @brief Contains commands used by the HX8347A
 * @ingroup HX8347A
 */

#pragma once


namespace lcd {
  namespace hx8347a {

    enum {

      DISPLAY_MODE = 0x1,

      COLUMN_ADDRESS_START_HIGH = 0x2,
      COLUMN_ADDRESS_START_LOW = 0x3,
      COLUMN_ADDRESS_END_HIGH = 0x4,
      COLUMN_ADDRESS_END_LOW = 0x5,
      ROW_ADDRESS_START_HIGH = 0x6,
      ROW_ADDRESS_START_LOW = 0x7,
      ROW_ADDRESS_END_HIGH = 0x8,
      ROW_ADDRESS_END_LOW = 0x9,

      SET_SCROLL_START_HIGH = 0x14,
      SET_SCROLL_START_LOW = 0x15,

      SET_SCROLL_AREA_HIGH = 0x10,
      SET_SCROLL_AREA_LOW = 0x11,

      SET_SCROLL_TOP_FIXED_AREA_HIGH = 0xe,
      SET_SCROLL_TOP_FIXED_AREA_LOW = 0xf,

      SET_SCROLL_BOTTOM_FIXED_AREA_HIGH = 0x12,
      SET_SCROLL_BOTTOM_FIXED_AREA_LOW = 0x13,

      MEMORY_ACCESS_CONTROL = 0x16,

      GATE_SCAN_CONTROL = 0x18,

      MEMORY_WRITE = 0x22,

      CYCLE_CONTROL_1 = 0x23,
      CYCLE_CONTROL_2 = 0x24,
      CYCLE_CONTROL_3 = 0x25,
      CYCLE_CONTROL_4 = 0x3a,
      CYCLE_CONTROL_5 = 0x3b,
      CYCLE_CONTROL_6 = 0x3c,
      CYCLE_CONTROL_7 = 0x3d,

      CYCLE_CONTROL_5a = 0x3e,
      CYCLE_CONTROL_6a = 0x40,

      DISPLAY_CONTROL_1 = 0x26,
      DISPLAY_CONTROL_2 = 0x27,
      DISPLAY_CONTROL_3 = 0x28,
      DISPLAY_CONTROL_4 = 0x29,
      DISPLAY_CONTROL_5 = 0x2a,
      DISPLAY_CONTROL_6 = 0x2c,
      DISPLAY_CONTROL_7 = 0x2d,
      DISPLAY_CONTROL_8 = 0x90,
      DISPLAY_CONTROL_9 = 0x35,
      DISPLAY_CONTROL_10 = 0x36,
      DISPLAY_CONTROL_14 = 0x41,

      OSC_CONTROL_1 = 0x19,
      OSC_CONTROL_3 = 0x93,

      POWER_CONTROL_1 = 0x1b,
      POWER_CONTROL_2 = 0x1c,
      POWER_CONTROL_3 = 0x1d,
      POWER_CONTROL_4 = 0x1e,
      POWER_CONTROL_5 = 0x1f,
      POWER_CONTROL_6 = 0x20,

      VCOM_CONTROL_1 = 0x43,
      VCOM_CONTROL_2 = 0x44,
      VCOM_CONTROL_3 = 0x45,

      INTERNAL_USE_2 = 0x56,
      INTERNAL_USE_3 = 0x57,

      /*
       * DISPLAY_MODE bits
       */

      IDMON=1 << 3,
      INVON=1 << 2,
      NORON=1 << 1,
      PTLON=1,

      /*
       * MEMORY_ACCESS_CONROL_BITS
       */

      MY=1 << 7,
      MX=1 << 6,
      MV=1 << 5,
      ML=1 << 4,
      BGR=1 << 3
    };
  }
}
