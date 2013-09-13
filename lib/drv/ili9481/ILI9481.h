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
 * @defgroup ILI9481
 * @brief Ilitek ILI9481
 *
 * The user can specialise based on the desired colour depth, orientation and access mode.
 *
 * @file ILI9481.h
 * @brief Core ILI9481 support. Contains the initialisation sequence and other non-specific members.
 * @ingroup ILI9481
 */


#pragma once

#include "commands/Allcommands.h"
#include "ILI9481Colour.h"
#include "ILI9481Orientation.h"
#include "ILI9481Gamma.h"


namespace lcd {

  /**
   * @brief Generic ILI9481 template.
   *
   * @ingroup ILI9481
   * @tparam TOrientation The desired panel orientation, LANDSCAPE or PORTRAIT
   * @tparam TColourDepth The colour depth for your use, just 64K is supported for this panel.
   * @tparam TAccessMode The access mode that you want to talk to this panel with, e.g. Gpio16LatchAccessMode.
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  class ILI9481 : public ILI9481Colour<TColourDepth,TAccessMode>,
                  public ILI9481Orientation<TOrientation,TAccessMode> {

    public:
      enum {
        SHORT_SIDE = 320,
        LONG_SIDE = 480
      };

    public:
      ILI9481();

      void initialise() const;

      void beginWriting() const;
      void sleep() const;
      void wake() const;
      void setScrollArea(uint16_t y,uint16_t height) const;

      void rawFlashTransfer(uint32_t data,uint32_t numBytes) const;
      void rawSramTransfer(uint8_t *data,uint32_t numBytes) const;
      void applyGamma(const ILI9481Gamma& gamma) const;
  };


  /**
   * Constructor
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline ILI9481<TOrientation,TColourDepth,TAccessMode>::ILI9481() {
    initialise();
  }


  /**
   * Initialise the LCD. Do the reset sequence.
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void ILI9481<TOrientation,TColourDepth,TAccessMode>::initialise() const {

    // initialise the access mode

    TAccessMode::initialise();

    // reset the device

    TAccessMode::hardReset();

    // exit sleep mode

    TAccessMode::writeCommand(ili9481::EXIT_SLEEP_MODE);
    delay(50);

    // enter normal mode

    TAccessMode::writeCommand(ili9481::ENTER_NORMAL_MODE);

    // power setting

    TAccessMode::writeCommand(ili9481::POWER_SETTING);
    TAccessMode::writeData(7);
    TAccessMode::writeData((1 << 6) | 3);
    TAccessMode::writeData(5 | (1 << 4));

    // VCom (more power settings)

    TAccessMode::writeCommand(ili9481::VCOM);
    TAccessMode::writeData(0); // register D1 for setting VCom
    TAccessMode::writeData(0);
    TAccessMode::writeData(0);

    // power setting for normal mode

    TAccessMode::writeCommand(ili9481::POWER_SETTING_NORMAL_MODE);
    TAccessMode::writeData(1);    // drivers on
    TAccessMode::writeData(2);    // fosc ratios

    // panel driving setting

    TAccessMode::writeCommand(ili9481::PANEL_DRIVING);
    TAccessMode::writeData(0);
    TAccessMode::writeData(0x3b);
    TAccessMode::writeData(0);
    TAccessMode::writeData(2);
    TAccessMode::writeData(1 | (1 << 4));

    // display timing (c1)

    TAccessMode::writeCommand(ili9481::DISPLAY_TIMING_SETTING_NORMAL_MODE);
    TAccessMode::writeData(1 << 4);         // line inversion, 1:1 internal clock
    TAccessMode::writeData(16);             // 1 line = 16 clocks
    TAccessMode::writeData((8 << 4) | 8);

    // display timing idle (c3)

    TAccessMode::writeCommand(ili9481::DISPLAY_TIMING_SETTING_IDLE_MODE);
    TAccessMode::writeData(1 << 4);
    TAccessMode::writeData(0x20);
    TAccessMode::writeData(8);

    // frame rate = 72Hz

    TAccessMode::writeCommand(ili9481::FRAME_RATE_AND_INVERSION_CONTROL);
    TAccessMode::writeData(3);

    // interface control

    TAccessMode::writeCommand(ili9481::INTERFACE_CONTROL);
    TAccessMode::writeData(1 | (1 << 1)| (1 << 3) | (1 << 4));

    // frame memory access (set DFM for 2 transfers/1 pixel in 18-bit mode)

    TAccessMode::writeCommand(ili9481::FRAME_MEMORY_ACCESS_AND_INTERFACE_SETTING);
    TAccessMode::writeData(0);
    TAccessMode::writeData(0);
    TAccessMode::writeData(0);
    TAccessMode::writeData(1);      // DFM

    // set the colour depth and orientation

    TAccessMode::writeCommand(ili9481::SET_PIXEL_FORMAT);
    TAccessMode::writeData(this->getPixelFormat());

    TAccessMode::writeCommand(ili9481::SET_ADDRESS_MODE);
    TAccessMode::writeData(this->getAddressMode() | (1 << 3));    // BGR

    // display on

    delay(100);
    TAccessMode::writeCommand(ili9481::SET_DISPLAY_ON);
  }


  /**
   * Send the panel to sleep
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void ILI9481<TOrientation,TColourDepth,TAccessMode>::sleep() const {

    // go to sleep and wait at least 5ms

    TAccessMode::writeCommand(ili9481::ENTER_SLEEP_MODE);
    delay(6);
  }


  /**
   * Wake the panel up
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void ILI9481<TOrientation,TColourDepth,TAccessMode>::wake() const {

    // wake up and wait at least 120ms

    TAccessMode::writeCommand(ili9481::EXIT_SLEEP_MODE);
    delay(121);
  }


  /**
   * Issue the command that allows graphics ram writing to commence
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void ILI9481<TOrientation,TColourDepth,TAccessMode>::beginWriting() const {
    TAccessMode::writeCommand(ili9481::WRITE_MEMORY_START);
  }


  /**
   * Set the scroll area to a full-width rectangle region
   * @param y The y-co-ord of the region
   * @param height The height of the region
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void ILI9481<TOrientation,TColourDepth,TAccessMode>::setScrollArea(uint16_t y,uint16_t height) const {

    uint16_t bfa,tfa;

    tfa=y;
    bfa=tfa-height;

    TAccessMode::writeCommand(ili9481::SET_SCROLL_AREA);
    TAccessMode::writeData(tfa >> 8);
    TAccessMode::writeData(tfa & 0xff);
    TAccessMode::writeData(height >> 8);
    TAccessMode::writeData(height & 0xff);
    TAccessMode::writeData(bfa >> 8);
    TAccessMode::writeData(bfa & 0xff);
  }


  /**
   * Write raw bytes from SRAM
   * @param data data source
   * @param numBytes number of bytes to write.
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void ILI9481<TOrientation,TColourDepth,TAccessMode>::rawFlashTransfer(uint32_t data,uint32_t numBytes) const {

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

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void ILI9481<TOrientation,TColourDepth,TAccessMode>::rawSramTransfer(uint8_t *data,uint32_t numBytes) const {

    uint32_t numPixels;

    numPixels=numBytes/2;

    while(numPixels--) {
      TAccessMode::writeData(data[0],data[1]);
      data+=2;
    }
  }


  /**
   * Apply the 11 panel gamma settings
   * @param gamma The collection of gamma values
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void ILI9481<TOrientation,TColourDepth,TAccessMode>::applyGamma(const ILI9481Gamma& gamma) const {

    TAccessMode::writeCommand(ili9481::GAMMA_SETTING);

    TAccessMode::writeData(gamma[0]);
    TAccessMode::writeData(gamma[1]);
    TAccessMode::writeData(gamma[2]);
    TAccessMode::writeData(gamma[3]);
    TAccessMode::writeData(gamma[4]);
    TAccessMode::writeData(gamma[5]);
    TAccessMode::writeData(gamma[6]);
    TAccessMode::writeData(gamma[7]);
    TAccessMode::writeData(gamma[8]);
    TAccessMode::writeData(gamma[9]);
    TAccessMode::writeData(gamma[10]);
    TAccessMode::writeData(gamma[11]);
  }
}
