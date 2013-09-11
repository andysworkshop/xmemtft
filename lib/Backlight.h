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
 * @file Backlight.h
 * @brief Simple backlight control using a PWM pin
 */

#pragma once

#include "Arduino.h"


namespace lcd {

  /**
   * Simple class to encapsulate a 0..100% backlight.
   * control managed on a PWM pin.
   * @tparam pwmPin The arduino PWM pin number.
   */

  template<uint8_t pwmPin=2>
  class Backlight {

    protected:
      uint8_t _currentPercentage;

    public:

      /**
       * Constructor, initialise the pin
       * @param initialPercentage The initial backlight percentage, default is zero.
       */

      Backlight(uint8_t initialPercentage=0) {
        pinMode(pwmPin,OUTPUT);
        analogWrite(pwmPin,initialPercentage);
        _currentPercentage=initialPercentage;
      }


      /**
       * Set the percentage.
       * @param percentage The percentage to set to.
       */

      void setPercentage(uint8_t percentage) {
        analogWrite(pwmPin,((uint16_t)percentage)*255/100);
        _currentPercentage=percentage;
      }


      /**
       * Fade up or down to the supplied percentage waiting for msPerStep millis between each step.
       * @param newPercentage The percentage that we will finish at.
       * @param msPerStep The number of milliseconds to pause between each percent increment/decrement.
       */

      void fadeTo(uint8_t newPercentage,int msPerStep) {

        int8_t direction;

        if(newPercentage==_currentPercentage)
          return;

        direction=newPercentage>_currentPercentage ? 1 : -1;

        while(newPercentage!=_currentPercentage) {
          setPercentage(_currentPercentage+direction);
          delay(msPerStep);
        }
      }
  };
}

