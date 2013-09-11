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
 * @file AllCommands.h
 * @brief Commands for the MC2PA8201 that we use
 * @ingroup MC2PA8201
 */

#pragma once


namespace lcd {
  namespace mc2pa8201 {

    /**
     * The command set as documented in v0.99 of the datasheet
     */

    enum E {
      NOP                               = 0,
      SOFTWARE_RESET                    = 1,
      READ_DISPLAY_ID                   = 4,
      READ_DISPLAY_STATUS               = 9,
      READ_DISPLAY_POWER_MODE           = 0xA,
      READ_DISPLAY_MADCTL               = 0xb,
      READ_DISPLAY_PIXEL_FORMAT         = 0xc,
      READ_DISPLAY_IMAGE_MODE           = 0xd,
      READ_DISPLAY_SIGNAL_MODE          = 0xe,
      READ_DISPLAY_SELF_DIAGNOSTICS     = 0xf,
      SLEEP_IN                          = 0x10,
      SLEEP_OUT                         = 0x11,
      PARTIAL_MODE_ON                   = 0x12,
      NORMAL_DISPLAY_MODE_ON            = 0x13,
      DISPLAY_INVERSION_OFF             = 0x20,
      DISPLAY_INVERSION_ON              = 0x21,
      GAMMA_SET                         = 0x26,
      DISPLAY_OFF                       = 0x28,
      DISPLAY_ON                        = 0x29,
      COLUMN_ADDRESS_SET                = 0x2a,
      PAGE_ADDRESS_SET                  = 0x2b,
      MEMORY_WRITE                      = 0x2c,
      COLOUR_SET                        = 0x2d,
      MEMORY_READ                       = 0x2e,
      PARTIAL_AREA                      = 0x30,
      VERTICAL_SCROLLING_DEFINITION     = 0x33,
      TEARING_EFFECT_LINE_OFF           = 0x34,
      TEARING_EFFECT_LINE_ON            = 0x35,
      MEMORY_ACCESS_CONTROL             = 0x36,
      VERTICAL_SCROLLING_START_ADDRESS  = 0x37,
      IDLE_MODE_OFF                     = 0x38,
      IDLE_MODE_ON                      = 0x39,
      INTERFACE_PIXEL_FORMAT            = 0x3a,
      READ_ID1                          = 0xda,
      READ_ID2                          = 0xdb,
      READ_ID3                          = 0xdc
    };
  }
}
