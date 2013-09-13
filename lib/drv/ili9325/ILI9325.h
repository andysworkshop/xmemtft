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

/*
 * Implementation for Adafruit TFT LCD copyright (c) 2013 Colin Irwin, see
 * http://aethersdr.org/ for details. Provided under original terms and
 * conditions.
 */

/**
 * @defgroup ILI9325
 * @brief Ilitek ILI9325
 *
 * The user can specialise based on the desired colour depth, orientation and access mode.
 *
 * @file ILI9325.h
 * @brief Core ILI9325 support. Contains the initialisation sequence and other non-specific members.
 * @ingroup ILI9325
 */

#pragma once

#include "Arduino.h"
#include "commands/Allcommands.h"
#include "ILI9325Colour.h"
#include "ILI9325Orientation.h"

namespace lcd {

  /**
   * @brief Generic ILI9325 template.
   *
   * @ingroup ILI9325
   * @tparam TOrientation The desired panel orientation, LANDSCAPE or PORTRAIT
   * @tparam TColourDepth The colour depth for your use, just 64K is supported for this panel.
   * @tparam TAccessMode The access mode that you want to talk to this panel with, e.g. Gpio16LatchAccessMode.
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  class ILI9325 : public ILI9325Colour<TColourDepth,TAccessMode>,
                  public ILI9325Orientation<TOrientation,TAccessMode> {

    public:
      enum {
        SHORT_SIDE=240, LONG_SIDE=320
      };

    public:
      ILI9325();
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

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline ILI9325<TOrientation,TColourDepth,TAccessMode>::ILI9325() {
    initialise();
  }


  /**
   * Initialise the LCD. Do the reset sequence.
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void ILI9325<TOrientation,TColourDepth,TAccessMode>::initialise() const {

    // initialise the access mode

    TAccessMode::initialise();

    // reset the device

    TAccessMode::hardReset();

    // post reset commands to set up the LCD

    TAccessMode::writeCommandData(ili9325::ILI932X_START_OSC,0x01,0x00);

    delay(50);

    TAccessMode::writeCommandData(ili9325::ILI932X_DRIV_OUT_CTRL,0x00,0x01);
    TAccessMode::writeCommandData(ili9325::ILI932X_DRIV_WAV_CTRL,0x00,0x07);
    TAccessMode::writeCommandData(ili9325::ILI932X_RESIZE_CTRL,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_DISP_CTRL2,0x02,0x02);
    TAccessMode::writeCommandData(ili9325::ILI932X_DISP_CTRL3,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_DISP_CTRL4,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_RGB_DISP_IF_CTRL1,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_FRM_MARKER_POS,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_RGB_DISP_IF_CTRL2,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_POW_CTRL1,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_POW_CTRL2,0x07,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_POW_CTRL3,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_POW_CTRL4,0x00,0x00);

    delay(200);

    TAccessMode::writeCommandData(ili9325::ILI932X_POW_CTRL1,0x90,0x16);
    TAccessMode::writeCommandData(ili9325::ILI932X_POW_CTRL2,0x27,0x02);

    delay(50);

    TAccessMode::writeCommandData(ili9325::ILI932X_POW_CTRL3,0x1A,0x00);

    delay(50);

    TAccessMode::writeCommandData(ili9325::ILI932X_POW_CTRL4,0x00,0x18);
    TAccessMode::writeCommandData(ili9325::ILI932X_POW_CTRL7,0x2A,0x00);

    delay(50);

    TAccessMode::writeCommandData(ili9325::ILI932X_GAMMA_CTRL1,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_GAMMA_CTRL2,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_GAMMA_CTRL3,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_GAMMA_CTRL4,0x06,0x02);
    TAccessMode::writeCommandData(ili9325::ILI932X_GAMMA_CTRL5,0x08,0x08);
    TAccessMode::writeCommandData(ili9325::ILI932X_GAMMA_CTRL6,0x07,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_GAMMA_CTRL7,0x01,0x02);
    TAccessMode::writeCommandData(ili9325::ILI932X_GAMMA_CTRL8,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_GAMMA_CTRL9,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_GAMMA_CTRL10,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_GRAM_HOR_AD,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_GRAM_VER_AD,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_HOR_START_AD,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_HOR_END_AD,0xEF,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_VER_START_AD,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_VER_END_AD,0x3F,0x01);
    TAccessMode::writeCommandData(ili9325::ILI932X_GATE_SCAN_CTRL1,0x00,0xA7);
    TAccessMode::writeCommandData(ili9325::ILI932X_GATE_SCAN_CTRL2,0x03,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_GATE_SCAN_CTRL3,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_PANEL_IF_CTRL1,0x10,0X00);
    TAccessMode::writeCommandData(ili9325::ILI932X_PANEL_IF_CTRL2,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_PANEL_IF_CTRL3,0x03,0X00);
    TAccessMode::writeCommandData(ili9325::ILI932X_PANEL_IF_CTRL4,0x00,0X11);
    TAccessMode::writeCommandData(ili9325::ILI932X_PANEL_IF_CTRL5,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_PANEL_IF_CTRL6,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_DISP_CTRL1,0x33,0x01);

    // The following needs to be reviewed/changed potentially to deal
    // with a different orientation.
    // (Other values depending on the exact orientation are:
    //      default: 0x1030
    //      case 1 : 0x1028
    //      case 2 : 0x1000
    //      case 3 : 0x1018)

    uint16_t entryMode=this->getInterfacePixelFormat() | 0x1000 | this->getMemoryAccessControl();
    TAccessMode::writeCommandData(ili9325::ILI932X_ENTRY_MOD,entryMode & 0xff,entryMode >> 8);
  }


  /**
   * Send the panel to sleep
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void ILI9325<TOrientation,TColourDepth,TAccessMode>::sleep() const {
    TAccessMode::writeCommandData(ili9325::ILI932X_DISP_CTRL1,0x00,0x00);
    TAccessMode::writeCommandData(ili9325::ILI932X_POW_CTRL1,0x01,0x00);
  }


  /**
   * Wake the panel up
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void ILI9325<TOrientation,TColourDepth,TAccessMode>::wake() const {
    TAccessMode::writeCommandData(ili9325::ILI932X_POW_CTRL1,0x90,0x16);
    TAccessMode::writeCommandData(ili9325::ILI932X_DISP_CTRL1,0x33,0x01);
  }


  /**
   * Issue the command that allows graphics ram writing to commence
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void ILI9325<TOrientation,TColourDepth,TAccessMode>::beginWriting() const {
    TAccessMode::writeCommand(ili9325::ILI932X_RW_GRAM);
  }


  /**
   * Set the scroll area to a full-width rectangle region
   * @param y The y-co-ord of the region
   * @param height The height of the region
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void ILI9325<TOrientation,TColourDepth,TAccessMode>::setScrollArea(uint16_t y,uint16_t height) const {
    // not supported
  }


  /**
   * Transfer data bytes from flash (program) memory, en-masse
   * @param data The address of the bytes to transfer
   * @param numBytes The number of bytes to transfer
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void ILI9325<TOrientation,TColourDepth,TAccessMode>::rawFlashTransfer(uint32_t data,uint32_t numBytes) const {

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
  inline void ILI9325<TOrientation,TColourDepth,TAccessMode>::rawSramTransfer(uint8_t *data,uint32_t numBytes) const {

    uint32_t numPixels;

    numPixels=numBytes/2;

    while(numPixels--) {
      TAccessMode::writeData(data[0],data[1]);
      data+=2;
    }
  }
}
