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
 * @file LDS285Backlight.h
 * @brief Implementation of the LDS285 backlight.
 * @ingroup LDS285
 */

#pragma once


namespace lcd {


  /**
   * Class to encapsulate a 0..100% backlight control on a Nokia 95 8Gb
   * controller (LDS285) where the backlight is built in to the panel
   * and managed by software.
   * @tparam The access mode in use.
   */

  template<class TAccessMode>
  class LDS285Backlight {

    protected:
      uint8_t _currentPercentage;

    public:
      LDS285Backlight(uint8_t initialPercentage=0);
      void fadeTo(uint8_t newPercentage,int msPerStep);
      void setPercentage(uint8_t percentage);
  };


  /**
   * Constructor - set to the user start value (default zero) but don't write out
   * to the panel because we can't guarantee that the user has initialised the panel
   * at the point this constructor is called.
   * @param initialPercentage The 0..100 percentage to start off with.
   */

  template<class TAccessMode>
  inline LDS285Backlight<TAccessMode>::LDS285Backlight(uint8_t initialPercentage) {
    _currentPercentage=initialPercentage;
  }


  /**
   * fade up or down to the supplied percentage waiting
   * for msPerStep millis between each step
   * @param newPercentage The new backlight percentage.
   * @param msPerStep How many milliseconds to wait between 1% steps.
   */

  template<class TAccessMode>
  inline void LDS285Backlight<TAccessMode>::fadeTo(uint8_t newPercentage,int msPerStep) {

    int8_t direction;

    if(newPercentage==_currentPercentage)
      return;

    direction=newPercentage>_currentPercentage ? 1 : -1;

    while(newPercentage!=_currentPercentage) {
      setPercentage(_currentPercentage+direction);
      delay(msPerStep);
    }
  }


  /**
   * Set a new backlight brightness level to a percentage
   * @param percentage The new percentage to go straight to.
   */

  template<class TAccessMode>
  inline void LDS285Backlight<TAccessMode>::setPercentage(uint8_t percentage) {

    uint8_t value;

    value=static_cast<uint8_t>((255*(uint16_t)percentage)/100);

    TAccessMode::writeCommand(lds285::WRITE_DISPLAY_BRIGHTNESS);
    TAccessMode::writeData(value);
    _currentPercentage=percentage;
  }
}

