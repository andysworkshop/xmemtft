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
 * @defgroup HX8347A
 * @brief Himax HX8347A
 *
 * The HX8347A is a popular QVGA controller found in many of the shields and LCD breakout boards.
 * The user can specialise based on the desired colour depth, orientation and access mode.
 *
 * @file HX8347A.h
 * @brief Core HX8347A support. Contains the initialisation sequence and other non-specific members.
 * @ingroup HX8347A
 */

#pragma once

#include "commands/Allcommands.h"
#include "HX8347AColour.h"
#include "HX8347AOrientation.h"


namespace lcd {

  /**
   * @brief Generic HX8347A template.
   *
   * @ingroup HX8347A
   * @tparam TOrientation The desired panel orientation, LANDSCAPE or PORTRAIT
   * @tparam TColourDepth The colour depth for your use, just 64K is supported for this panel.
   * @tparam TAccessMode The access mode that you want to talk to this panel with, e.g. Gpio16LatchAccessMode.
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  class HX8347A : public HX8347AColour<TColourDepth,TAccessMode>,
                  public HX8347AOrientation<TOrientation,TAccessMode> {

    public:

      /**
       * Panel dimensions
       */

      enum {
        SHORT_SIDE = 240,       ///< Short side is 240px
        LONG_SIDE = 320         ///< Long side is 320px
      };

    public:
      HX8347A();

      void initialise() const;

      void beginWriting() const;
      void sleep() const;
      void wake() const;
      void setScrollArea(uint16_t y,uint16_t height) const;

      void rawFlashTransfer(uint32_t data,uint32_t numBytes) const;
      void rawSramTransfer(uint8_t *data,uint32_t numBytes) const;
  };


  /**
   * Constructor. Calls the initialise() member.
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline HX8347A<TOrientation,TColourDepth,TAccessMode>::HX8347A() {
    initialise();
  }


  /**
   * Initialise the LCD. Do the reset sequence. Long and painful for this panel.
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void HX8347A<TOrientation,TColourDepth,TAccessMode>::initialise() const {

    // initialise the access mode

    TAccessMode::initialise();

    // reset the device

    TAccessMode::hardReset();

  // SAP=0111 1111

    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_8,0x7F);

    // IDMON=0, INVON=1, NORON=1, PTLON=0

    TAccessMode::writeCommandData(hx8347a::DISPLAY_MODE,hx8347a::INVON | hx8347a::NORON);

    // cycle control

    TAccessMode::writeCommandData(hx8347a::CYCLE_CONTROL_1,0x95);     // N_DC=1001 0101
    TAccessMode::writeCommandData(hx8347a::CYCLE_CONTROL_2,0x95);     // P_DC=1001 0101
    TAccessMode::writeCommandData(hx8347a::CYCLE_CONTROL_3,0xFF);     // I_DC=1111 1111

    // display control (front and back porch settings)

    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_2,0x06);   // N_BP=0000 0110
    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_3,0x06);   // N_FP=0000 0110
    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_4,0x06);   // P_BP=0000 0110
    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_5,0x06);   // P_FP=0000 0110
    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_6,0x06);   // I_BP=0000 0110
    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_7,0x06);   // I_FP=0000 0110

    // cycle control

    TAccessMode::writeCommandData(hx8347a::CYCLE_CONTROL_4,0x01);     // N_RTN=0000, N_NW=001
    TAccessMode::writeCommandData(hx8347a::CYCLE_CONTROL_5,0x01);     // P_RTN=0000, P_NW=001
    TAccessMode::writeCommandData(hx8347a::CYCLE_CONTROL_6,0xF0);     // I_RTN=1111, I_NW=000
    TAccessMode::writeCommandData(hx8347a::CYCLE_CONTROL_7,0x00);     // DIV=00

    delay(20);

    // Power Supply Setting

    TAccessMode::writeCommandData(hx8347a::OSC_CONTROL_1,0x49);       // OSCADJ=10 0000, OSD_EN=1 //60Hz
    TAccessMode::writeCommandData(hx8347a::OSC_CONTROL_3,0x0C);       // RADJ=1100,

    delay(10);

    TAccessMode::writeCommandData(hx8347a::POWER_CONTROL_6,0x40);     // BT=0100
    TAccessMode::writeCommandData(hx8347a::POWER_CONTROL_3,0x07);     // VC1=111
    TAccessMode::writeCommandData(hx8347a::POWER_CONTROL_4,0x00);     // VC3=000
    TAccessMode::writeCommandData(hx8347a::POWER_CONTROL_5,0x04);     // VRH=0100       4.12V

    TAccessMode::writeCommandData(hx8347a::VCOM_CONTROL_2,0x4D);      // VCM=101 0000   3.21V
    TAccessMode::writeCommandData(hx8347a::VCOM_CONTROL_3,0x11);      // VDV=1 0001     -1.19V

    delay(10);

    TAccessMode::writeCommandData(hx8347a::POWER_CONTROL_2,0x04);     // AP=100

    delay(20);

    TAccessMode::writeCommandData(hx8347a::VCOM_CONTROL_1,0x80);      // set VCOMG=1

    delay(5);

    TAccessMode::writeCommandData(hx8347a::POWER_CONTROL_1,0x18);     // GASENB=0, PON=1, DK=1, XDK=0, DDVDH_TRI=0, STB=0

    delay(40);

    TAccessMode::writeCommandData(hx8347a::POWER_CONTROL_1,0x10);     // GASENB=0, PON=1, DK=0, XDK=0, DDVDH_TRI=0, STB=0

    delay(40);

    // Display ON Setting

    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_1,0x04);   // GON=0, DTE=0, D=01

    delay(40);

    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_1,0x24);   // GON=1, DTE=0, D=01
    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_1,0x2C);   // GON=1, DTE=0, D=11

    delay(40);

    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_1,0x3C);   // GON=1, DTE=1, D=11

    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_9,0x38);   // EQS=38h
    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_10,0x78);  // EQP=78h

    TAccessMode::writeCommandData(hx8347a::CYCLE_CONTROL_5a,0x38);    // SON=38h

    TAccessMode::writeCommandData(hx8347a::CYCLE_CONTROL_6a,0x0F);    // GDON=0Fh
    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_14,0xF0);  // GDOFF

    // Set spulse & rpulse
    TAccessMode::writeCommandData(hx8347a::INTERNAL_USE_3,0x02);      // Test mode='1'
    TAccessMode::writeCommandData(hx8347a::INTERNAL_USE_2,0x84);      // set Rpulse='1000',spulse='0100'
    TAccessMode::writeCommandData(hx8347a::INTERNAL_USE_3,0x00);      // Test mode= '0'

    delay(20);

    // apply entry mode by combining the values from the orientation and colour depth
    // with the common BGR setting

    TAccessMode::writeCommandData(hx8347a::MEMORY_ACCESS_CONTROL,
                              this->getOrientationMemoryAccessCtrl() | hx8347a::MY | hx8347a::BGR);

    // set up the scroll parameters - height references are always 0..320

    setScrollArea(0,320);
    this->setScrollPosition(0);

    // enable scrolling

    TAccessMode::writeCommandData(hx8347a::GATE_SCAN_CONTROL,2);
  }


  /**
   * Send the panel to sleep. The backlight should be switched off as well to achieve
   * full power saving.
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void HX8347A<TOrientation,TColourDepth,TAccessMode>::sleep() const {

      // GON=1, DTE=1, D=10
    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_1,0x38);
    delay(40);

    // GON=1, DTE=0, D=10
    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_1,0x28);
    delay(40);

    // GON=0, DTE=0, D=00
    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_1,0);
    delay(40);

    // SAP=0
    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_8,0);

    TAccessMode::writeCommandData(hx8347a::POWER_CONTROL_2,0); // AP=000
    delay(20);

    // STB=1, DK=1
    TAccessMode::writeCommandData(hx8347a::POWER_CONTROL_1,9);
    // OSC_EN=0
    TAccessMode::writeCommandData(hx8347a::OSC_CONTROL_1,0);
  }


  /**
   * Wake the panel up. Don't forget to switch the backlight back on.
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void HX8347A<TOrientation,TColourDepth,TAccessMode>::wake() const {

    // OSCADJ=10 0000, OSD_EN=1 //60Hz
    TAccessMode::writeCommandData(hx8347a::OSC_CONTROL_1,0x49);
    delay(20);

    // GASENB=0, PON=1, DK=0, XDK=0, DDVDH_TRI=0, STB=0
    TAccessMode::writeCommandData(hx8347a::POWER_CONTROL_1,0x10);

    TAccessMode::writeCommandData(hx8347a::POWER_CONTROL_2,0x04); // AP=100
    delay(20);

    // SAP=0111 1111
    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_8,0x7F);

    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_1,0x04); // GON=0, DTE=0, D=01
    delay(40);

    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_1,0x24); // GON=1, DTE=0, D=01
    delay(40);

    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_1,0x2C); // GON=1, DTE=0, D=11
    delay(40);

    TAccessMode::writeCommandData(hx8347a::DISPLAY_CONTROL_1,0x3C); // GON=1, DTE=1, D=11
    delay(40);
  }


  /**
   * Issue the command that allows graphics ram writing to commence
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void HX8347A<TOrientation,TColourDepth,TAccessMode>::beginWriting() const {
    TAccessMode::writeCommand(hx8347a::MEMORY_WRITE);
  }


  /**
   * Set the scroll area to a full-width rectangle region
   * @param y The y-co-ord of the region
   * @param height The height of the region
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void HX8347A<TOrientation,TColourDepth,TAccessMode>::setScrollArea(uint16_t y,uint16_t height) const {

    uint16_t bfa,tfa;

    tfa=y;
    bfa=320-height-y;

    TAccessMode::writeCommandData(hx8347a::SET_SCROLL_TOP_FIXED_AREA_HIGH,tfa >> 8);
    TAccessMode::writeCommandData(hx8347a::SET_SCROLL_TOP_FIXED_AREA_LOW,tfa & 0xff);
    TAccessMode::writeCommandData(hx8347a::SET_SCROLL_BOTTOM_FIXED_AREA_HIGH,bfa >> 8);
    TAccessMode::writeCommandData(hx8347a::SET_SCROLL_BOTTOM_FIXED_AREA_LOW,bfa & 0xff);
    TAccessMode::writeCommandData(hx8347a::SET_SCROLL_AREA_HIGH,height >> 8);
    TAccessMode::writeCommandData(hx8347a::SET_SCROLL_AREA_LOW,height & 0xff);
  }


  /**
   * Transfer data bytes from flash (program) memory, en-masse
   * @param data The address of the bytes to transfer
   * @param numBytes The number of bytes to transfer
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void HX8347A<TOrientation,TColourDepth,TAccessMode>::rawFlashTransfer(uint32_t data,uint32_t numBytes) const {

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
  inline void HX8347A<TOrientation,TColourDepth,TAccessMode>::rawSramTransfer(uint8_t *data,uint32_t numBytes) const {

    uint32_t numPixels;

    numPixels=numBytes/2;

    while(numPixels--) {
      TAccessMode::writeData(data[0],data[1]);
      data+=2;
    }
  }
}
