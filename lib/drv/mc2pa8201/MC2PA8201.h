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
 * @defgroup MC2PA8201
 * @brief Magnachip MC2PA8201
 *
 * The user can specialise based on the desired colour depth, orientation and access mode. Support is
 * provided for the built-in backlight controller.
 *
 * @file MC2PA8201.h
 * @brief Core MC2PA8201 support. Contains the initialisation sequence and other non-specific members.
 * @ingroup MC2PA8201
 */


#pragma once

#include "commands/Allcommands.h"
#include "MC2PA8201Colour.h"
#include "MC2PA8201Orientation.h"


namespace lcd {

  /**
   * @brief Generic MC2PA8201 template.
   *
   * @ingroup MC2PA8201
   * @tparam TOrientation The desired panel orientation, LANDSCAPE or PORTRAIT
   * @tparam TColourDepth The colour depth for your use, just 64K is supported for this panel.
   * @tparam TAccessMode The access mode that you want to talk to this panel with, e.g. XmemAccessMode.
   * @tparam TPanelTraits Panel-specific traits.
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
  class MC2PA8201 : public MC2PA8201Colour<TColourDepth,TAccessMode,TPanelTraits>,
                    public MC2PA8201Orientation<TOrientation,TAccessMode,TPanelTraits> {

    public:
      enum {
        SHORT_SIDE = 240,
        LONG_SIDE = 320
      };

    public:
      MC2PA8201();

      void initialise() const;

      void beginWriting() const;
      void sleep() const;
      void wake() const;
      void setScrollArea(uint16_t y,uint16_t height) const;

      void rawFlashTransfer(uint32_t data,uint32_t numBytes) const;
      void rawSramTransfer(uint8_t *data,uint32_t numBytes) const;
  };


  /**
   * Constructor
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
  inline MC2PA8201<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::MC2PA8201() {
    initialise();
  }


  /**
   * Initialise the LCD. Do the reset sequence.
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
  inline void MC2PA8201<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::initialise() const {

    // initialise the access mode

    TAccessMode::initialise();

    // reset the device

    TAccessMode::hardReset();

    // post-reset sequence

    TAccessMode::writeCommand(mc2pa8201::SLEEP_OUT);
    delay(10);
    TAccessMode::writeCommand(mc2pa8201::DISPLAY_INVERSION_OFF);
    TAccessMode::writeCommand(mc2pa8201::IDLE_MODE_OFF);
    TAccessMode::writeCommand(mc2pa8201::NORMAL_DISPLAY_MODE_ON);

    // interface pixel format comes from the colour specialisation

    TAccessMode::writeCommand(mc2pa8201::INTERFACE_PIXEL_FORMAT);
    TAccessMode::writeData(this->getInterfacePixelFormat());

    // memory access control comes from the orientation specialisation

    TAccessMode::writeCommand(mc2pa8201::MEMORY_ACCESS_CONTROL);
    TAccessMode::writeData(this->getMemoryAccessControl());

    // reset the scrolling area

    if(TPanelTraits::template hasHardwareScrolling<TOrientation>())
      setScrollArea(0,TPanelTraits::getScrollHeight());

    // wait at least 120ms before we can turn the display on

    delay(125);
    TAccessMode::writeCommand(mc2pa8201::DISPLAY_ON);
  }


  /**
   * Send the panel to sleep
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
  inline void MC2PA8201<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::sleep() const {

    TAccessMode::writeCommand(mc2pa8201::DISPLAY_OFF);
    TAccessMode::writeCommand(mc2pa8201::SLEEP_IN);
    delay(5);
  }


  /**
   * Wake the panel up
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
  inline void MC2PA8201<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::wake() const {

    TAccessMode::writeCommand(mc2pa8201::SLEEP_OUT);
    delay(120);
    TAccessMode::writeCommand(mc2pa8201::DISPLAY_ON);
    delay(5);
  }


  /**
   * Issue the command that allows graphics ram writing to commence
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
  inline void MC2PA8201<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::beginWriting() const {
    TAccessMode::writeCommand(mc2pa8201::MEMORY_WRITE);
  }


  /**
   * Set the scroll area to a full-width rectangle region
   * @param y The y-co-ord of the region
   * @param height The height of the region
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
  inline void MC2PA8201<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::setScrollArea(uint16_t y,uint16_t height) const {

    uint16_t bfa;

    bfa=TPanelTraits::getScrollHeight()-height-y;

    TAccessMode::writeCommand(mc2pa8201::VERTICAL_SCROLLING_DEFINITION);
    TAccessMode::writeData(y >> 8);
    TAccessMode::writeData(y & 0xff);
    TAccessMode::writeData(height >> 8);
    TAccessMode::writeData(height & 0xff);
    TAccessMode::writeData(bfa >> 8);
    TAccessMode::writeData(bfa & 0xff);
  }


  /**
   * Transfer data bytes, en-masse
   * @param data The 32-bit address in flash
   * @param numBytes The number of bytes to transfer
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
  inline void MC2PA8201<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::rawFlashTransfer(uint32_t data,uint32_t numBytes) const {

    // handle data in the lower and upper segments with possible overlap

    while(data<65536 && numBytes>0) {
      TAccessMode::writeData(pgm_read_byte_near(data++));
      numBytes--;
    }

    while(numBytes>0) {
      TAccessMode::writeData(pgm_read_byte_far(data++));
      numBytes--;
    }
  }


  /**
   * Write raw bytes from SRAM
   * @param data data source
   * @param numBytes number of bytes to write.
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
  inline void MC2PA8201<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::rawSramTransfer(uint8_t *data,uint32_t numBytes) const {

    while(numBytes--)
      TAccessMode::writeData(*data++);
  }
}
