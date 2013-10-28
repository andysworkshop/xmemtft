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
 * @defgroup R61523
 * @brief Renesas R61523
 *
 * The user can specialise based on the desired colour depth, orientation and access mode. Support is
 * provided for the built-in backlight controller.
 *
 * @file R61523.h
 * @brief Core R61523 support. Contains the initialisation sequence and other non-specific members.
 * @ingroup R61523
 */

#pragma once

#include "commands/Allcommands.h"
#include "R61523Colour.h"
#include "R61523Orientation.h"
#include "R61523Gamma.h"


namespace lcd {

  /**
   * @brief Generic R61523 template.
   *
   * @ingroup R61523
   * @tparam TOrientation The desired panel orientation, LANDSCAPE or PORTRAIT
   * @tparam TColourDepth The colour depth for your use, just 64K is supported for this panel.
   * @tparam TAccessMode The access mode that you want to talk to this panel with, e.g. XmemAccessMode.
   * @tparam TPanelTraits Panel-specific traits.
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  class R61523 : public R61523Colour<TColourDepth,TAccessMode>,
                 public R61523Orientation<TOrientation,TAccessMode> {

    public:
      enum {
        SHORT_SIDE = 360,
        LONG_SIDE = 640,

        DEVICE_CODE = 0x01221523
      };


      /**
       * Possible modes for the tearing effect
       */

      enum TearingEffectMode {
        TE_VBLANK,            //!< vertical blank only
        TE_VBLANK_HBLANK,     //!< vertical and horizontal blank
      };

    protected:
      bool _enablePwmPin;

    public:
      R61523(bool enablePwmPin=true);

      void initialise() const;

      void applyGamma(const R61523Gamma& gamma) const;
      void applyGamma(uint16_t command,const R61523Gamma& gamma) const;
      void sleep() const;
      void wake() const;
      void beginWriting() const;

      void rawFlashTransfer(uint32_t data,uint32_t numBytes) const;
      void rawSramTransfer(uint8_t *data,uint32_t numBytes) const;

      uint32_t readDeviceCode() const;
      void enableTearingEffect(TearingEffectMode teMode) const;
      void disableTearingEffect() const;
  };


  /**
   * Constructor
   * @param enablePwmPin true if the PWM backlight out pin is to be enabled
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline R61523<TOrientation,TColourDepth,TAccessMode>::R61523(bool enablePwmPin)
    : _enablePwmPin(enablePwmPin) {

    initialise();
  }


  /**
   * Initialise the LCD. Do the reset sequence.
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void R61523<TOrientation,TColourDepth,TAccessMode>::initialise() const {

    typename R61523Colour<TColourDepth,TAccessMode>::UnpackedColour uc;

    // initialise the access mode

    TAccessMode::initialise();

    // reset the device

    TAccessMode::hardReset();

    // enable access to all the manufacturer commands

    TAccessMode::writeCommand(r61523::MCAP);
    TAccessMode::writeData(4);

    if(_enablePwmPin) {

      // enable the backlight PWM output pin with some default settings and a 0% duty cycle

      TAccessMode::writeCommand(r61523::BACKLIGHT_CONTROL_2);
      TAccessMode::writeData(0x1);         // PWMON=1
      TAccessMode::writeData(0);           // BDCV=0 (off)
      TAccessMode::writeData(0x3);         // 13.7kHz
      TAccessMode::writeData(0x18);        // PWMWM=1, LEDPWME=1
    }

    // exit sleep mode

    TAccessMode::writeCommand(r61523::SLEEP_OUT);
    delay(120);

    // set the orientation and colour depth

    this->setOrientation();
    this->setColourDepth();

    // clear to black

    this->unpackColour(0,uc);
    this->moveTo(0,0,this->getWidth()-1,this->getHeight()-1);
    this->fillPixels(static_cast<uint32_t>(this->getWidth())*static_cast<uint32_t>(this->getHeight()),uc);

    // display on

    TAccessMode::writeCommand(r61523::DISPLAY_ON);
  }

  /**
   * Apply the panel gamma settings
   * @param gamma The collection of gamma values
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void R61523<TOrientation,TColourDepth,TAccessMode>::applyGamma(const R61523Gamma& gamma) const {

    applyGamma(r61523::GAMMA_SET_A,gamma);
    applyGamma(r61523::GAMMA_SET_B,gamma);
    applyGamma(r61523::GAMMA_SET_C,gamma);
  }


  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void R61523<TOrientation,TColourDepth,TAccessMode>::applyGamma(uint16_t command,const R61523Gamma& gamma) const {

    uint8_t i;

    TAccessMode::writeCommand(command);

    // positive

    for(i=0;i<2;i++) {
      TAccessMode::writeData(gamma[0]);
      TAccessMode::writeData(gamma[1]);
      TAccessMode::writeData(gamma[3] << 4 | gamma[2]);
      TAccessMode::writeData(gamma[5] << 4 | gamma[4]);
      TAccessMode::writeData(gamma[6]);
      TAccessMode::writeData(gamma[8] << 4 | gamma[7]);
      TAccessMode::writeData(gamma[10] << 4 | gamma[9]);
      TAccessMode::writeData(gamma[11]);
      TAccessMode::writeData(gamma[12]);
    }
  }


  /**
   * Send the panel to sleep
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void R61523<TOrientation,TColourDepth,TAccessMode>::sleep() const {

    TAccessMode::writeCommand(r61523::DISPLAY_OFF);
    TAccessMode::writeCommand(r61523::SLEEP_IN);
    delay(120);
  }


  /**
   * Wake the panel up
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void R61523<TOrientation,TColourDepth,TAccessMode>::wake() const {

    TAccessMode::writeCommand(r61523::SLEEP_OUT);
    delay(120);
    TAccessMode::writeCommand(r61523::DISPLAY_ON);
    delay(5);
  }


  /**
   * Issue the command that allows graphics ram writing to commence
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void R61523<TOrientation,TColourDepth,TAccessMode>::beginWriting() const {
    TAccessMode::writeCommand(r61523::MEMORY_WRITE);
  }


  /**
   * Read the device ID code. This can be used to verify that you are talking to an R61523
   * and that you've got the timings correct for read transactions.
   * @return The device ID code. It should match DEVICE_CODE.
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline uint32_t R61523<TOrientation,TColourDepth,TAccessMode>::readDeviceCode() const {

    uint32_t deviceCode;

    // the device code is 4 bytes

    TAccessMode::writeCommand(r61523::DEVICE_CODE_READ);
    TAccessMode::readData();

    deviceCode=static_cast<uint32_t>(TAccessMode::readData()) << 24;
    deviceCode|=static_cast<uint32_t>(TAccessMode::readData()) << 16;
    deviceCode|=static_cast<uint32_t>(TAccessMode::readData()) << 8;
    deviceCode|=static_cast<uint32_t>(TAccessMode::readData());

    return deviceCode;
  }


  /**
   * Transfer data bytes, en-masse from flash
   * @param data The 32-bit address in flash
   * @param numBytes The number of bytes to transfer
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void R61523<TOrientation,TColourDepth,TAccessMode>::rawFlashTransfer(uint32_t data,uint32_t numBytes) const {

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
   * Enable the tearing effect signal
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  void R61523<TOrientation,TColourDepth,TAccessMode>::enableTearingEffect(TearingEffectMode teMode) const {

    TAccessMode::writeCommand(r61523::SET_TEAR_ON);
    TAccessMode::writeData(teMode==TE_VBLANK ? 0 : 1);
  }


  /**
   * Disable the tearing effect signal
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  void R61523<TOrientation,TColourDepth,TAccessMode>::disableTearingEffect() const {
    TAccessMode::writeCommand(r61523::SET_TEAR_OFF);
  }


  /**
   * Write raw bytes from SRAM
   * @param data data source
   * @param numBytes number of bytes to write.
   */

  template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
  inline void R61523<TOrientation,TColourDepth,TAccessMode>::rawSramTransfer(uint8_t *data,uint32_t numBytes) const {

    uint32_t numPixels;

    numPixels=numBytes/2;

    while(numPixels--) {
      TAccessMode::writeData(data[0],data[1]);
      data+=2;
    }
  }
}
