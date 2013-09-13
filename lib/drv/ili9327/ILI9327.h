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
 * @defgroup ILI9327
 * @brief Ilitek ILI9327
 *
 * The user can specialise based on the desired colour depth, orientation and access mode. Panel sizes
 * up to 400x232 are supported.
 *
 * @file ILI9327.h
 * @brief Core ILI9327 support. Contains the initialisation sequence and other non-specific members.
 * @ingroup ILI9327
 */

#pragma once

#include "commands/Allcommands.h"
#include "ILI9327Colour.h"
#include "ILI9327Orientation.h"


namespace lcd {

  /**
   * @brief Generic ILI9327 template.
   * @tparam TOrientation The desired panel orientation, LANDSCAPE or PORTRAIT
   * @tparam TColourDepth The colour depth for your use, just 64K is supported for this panel.
   * @tparam TAccessMode The access mode that you want to talk to this panel with, e.g. Gpio16LatchAccessMode.
   * @tparam TPanelTraits Constants and functions specific to the actual panel.
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
  class ILI9327 : public ILI9327Colour<TColourDepth,TAccessMode>,
                  public ILI9327Orientation<TOrientation,TAccessMode,TPanelTraits> {

    public:
      enum {
        SHORT_SIDE = TPanelTraits::SHORT_SIDE,
        LONG_SIDE = TPanelTraits::LONG_SIDE
      };

    public:
      ILI9327();

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
  inline ILI9327<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::ILI9327() {
    initialise();
  }


  /**
   * Initialise the LCD. Do the reset sequence.
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
  inline void ILI9327<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::initialise() const {

    // initialise the access mode

    TAccessMode::initialise();

    // reset the device

    TAccessMode::hardReset();

    // power setting: we use the internal ref vci=2.5v

    TAccessMode::writeCommand(ili9327::POWER_SETTING);
    TAccessMode::writeData(ili9327::VC_100);              // vci1=vci*1 (vci=2.5V therefore vci1=2.5V)
    TAccessMode::writeData(ili9327::BT_5_4);              // VGH=vci1*5, VGL=vci1*-4
    TAccessMode::writeData(0xc | ili9327::VCIRE);         // int ref + VREG1OUT = vci1*1.9 = 4.75

    // VCom (more power settings)

    TAccessMode::writeCommand(ili9327::VCOM); // register D1 for setting VCom
    TAccessMode::writeData(0);
    TAccessMode::writeData(0x40);                         // VCOMH = VREG1OUT * 0.748
    TAccessMode::writeData(0xf);                          // VCOM amplitude=VREG1OUT*1

    // power setting for normal mode

    TAccessMode::writeCommand(ili9327::POWER_SETTING_NORMAL_MODE);
    TAccessMode::writeData(1);                            // drivers on
    TAccessMode::writeData(4 | (4<<4));

    // exit sleep mode

    TAccessMode::writeCommand(ili9327::EXIT_SLEEP_MODE);
    delay(50);

    // enter normal mode

    TAccessMode::writeCommand(ili9327::ENTER_NORMAL_MODE);

    // panel driving setting

    TAccessMode::writeCommand(ili9327::PANEL_DRIVING);
    TAccessMode::writeData(0);
    TAccessMode::writeData(0x35);
    TAccessMode::writeData(0);
    TAccessMode::writeData(0);          // modify for power reduction in back/front porch
    TAccessMode::writeData(1 | (1 << 4));
    TAccessMode::writeData(0);

    // display timing (c1)

    TAccessMode::writeCommand(ili9327::DISPLAY_TIMING_SETTING_NORMAL_MODE);
    TAccessMode::writeData(1 << 4);       // line inversion, 1:1 internal clock
    TAccessMode::writeData(0x10);         // 1 line = 16 clocks
    TAccessMode::writeData(2);
    TAccessMode::writeData(4);

    // display timing idle (c3)

    TAccessMode::writeCommand(ili9327::DISPLAY_TIMING_SETTING_IDLE_MODE);
    TAccessMode::writeData(1 << 4);
    TAccessMode::writeData(0x10);
    TAccessMode::writeData(0x2);
    TAccessMode::writeData(0x4);

    // frame rate = 96Hz

    TAccessMode::writeCommand(ili9327::FRAME_RATE_AND_INVERSION_CONTROL);
    TAccessMode::writeData(4);

    // interface control

    TAccessMode::writeCommand(ili9327::INTERFACE_CONTROL);
    TAccessMode::writeData(ili9327::DPL | ili9327::EPL | ili9327::HSPL | ili9327::VSPL);

    // frame memory access (set DFM for 2 transfers/1 pixel in 18-bit mode)

    TAccessMode::writeCommand(ili9327::FRAME_MEMORY_ACCESS_AND_INTERFACE_SETTING);
    TAccessMode::writeData(0);
    TAccessMode::writeData(0);
    TAccessMode::writeData(0);
    TAccessMode::writeData(1);

    // display on - cannot happen <120ms after reset

    delay(100);
    TAccessMode::writeCommand(ili9327::SET_DISPLAY_ON);

    // set the colour mode (base class specialisation does this)

    this->setColourMode();

    // set the address mode (orientation from specialisation and BGR order)

    TAccessMode::writeCommand(ili9327::SET_ADDRESS_MODE);
    TAccessMode::writeData(this->getOrientationAddressMode() | ili9327::BGR | ili9327::VERTICAL_FLIP);

    // set scroll area to omit the missing scan lines if panel is shorter than 432

    setScrollArea(0,TPanelTraits::LONG_SIDE);
    this->setScrollPosition(0);
  }


  /**
   * Send the panel to sleep
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
  inline void ILI9327<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::sleep() const {

    // go to sleep and wait at least 5ms

    TAccessMode::writeCommand(ili9327::ENTER_SLEEP_MODE);
    delay(6);
  }


  /**
   * Wake the panel up
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
  inline void ILI9327<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::wake() const {

    // wake up and wait at least 120ms

    TAccessMode::writeCommand(ili9327::EXIT_SLEEP_MODE);
    delay(121);
  }


  /**
   * Issue the command that allows graphics ram writing to commence
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
  inline void ILI9327<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::beginWriting() const {
    TAccessMode::writeCommand(ili9327::WRITE_MEMORY_START);
  }


  /**
   * Set the scroll area to a full-width rectangle region
   * @param y The y-co-ord of the region
   * @param height The height of the region
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
  inline void ILI9327<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::setScrollArea(uint16_t y,uint16_t height) const {

    uint16_t bfa,tfa;

    tfa=(432-TPanelTraits::LONG_SIDE)+y;
    bfa=432-tfa-height;

    TAccessMode::writeCommand(ili9327::SET_SCROLL_AREA);
    TAccessMode::writeData(tfa >> 8);
    TAccessMode::writeData(tfa & 0xff);
    TAccessMode::writeData(height >> 8);
    TAccessMode::writeData(height & 0xff);
    TAccessMode::writeData(bfa >> 8);
    TAccessMode::writeData(bfa & 0xff);
  }


  /**
   * Transfer data bytes from flash (program) memory, en-masse
   * @param data The address of the bytes to transfer
   * @param numBytes The number of bytes to transfer
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
  inline void ILI9327<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::rawFlashTransfer(uint32_t data,uint32_t numBytes) const {

    uint32_t numPixels;

    numPixels=numBytes/2;

    // handle data in the lower and upper segments with possible overlap
    // a single 16-bit pixel should not overlap the segments

    while(data<65536 && numPixels>0) {
      TAccessMode::writeData(pgm_read_byte_near(data),pgm_read_byte_near(data+1));
      data+=2;
      numPixels--;
    }

    while(numPixels>0) {
      TAccessMode::writeData(pgm_read_byte_far(data),pgm_read_byte_far(data+1));
      data+=2;
      numPixels--;
    }
  }


  /**
   * Write raw bytes from SRAM
   * @param data data source
   * @param numBytes number of bytes to write.
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
  inline void ILI9327<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::rawSramTransfer(uint8_t *data,uint32_t numBytes) const {

    uint32_t numPixels;

    numPixels=numBytes/2;

    while(numPixels--) {
      TAccessMode::writeData(data[0],data[1]);
      data+=2;
    }
  }
}
