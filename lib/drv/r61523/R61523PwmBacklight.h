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
 * @file R61523PwmBacklight.h
 * @brief Implementation of the R61523 backlight.
 * @ingroup R61523
 */

#pragma once


namespace lcd {

  /**
   * Possible frequencies for the backlight
   */

  enum R61523BacklightFrequency {
    FREQUENCY_33_3 = 0x00,
    FREQUENCY_27_4 = 0x01,
    FREQUENCY_18_3 = 0x02,
    FREQUENCY_13_7 = 0x03,
    FREQUENCY_6_86 = 0x07,
    FREQUENCY_3_43 = 0x0f,
    FREQUENCY_1_72 = 0x1f,
    FREQUENCY_0_86 = 0x3f,
    FREQUENCY_0_43 = 0x7f,
    FREQUENCY_0_21 = 0xff
  };


  /**
   * The R61523 supports direct control of the PWM LED pin as well as a combination of
   * the calculated required backlight and the PWM register setting. This is the mode
   * where you directly control the PWM output on the BLPWM pin
   * @tparam TFrequency The desired frequency for the PWM signal from the available enumeration
   * @tparam TSmooth true if changes are to be applied gradually over approx 500ms in hardware
   * @tparam TPolarity 0 means signal high is lit, 1 means signal low is lit.
   */

  template<class TAccessMode,bool TSmooth=true,R61523BacklightFrequency TFrequency=FREQUENCY_13_7,uint8_t TPolarity=0>
  class R61523PwmBacklight {

    protected:
      uint16_t _currentPercentage;

    public:
      R61523PwmBacklight();

      void fadeTo(uint16_t newPercentage,int msPerStep);
      void setPercentage(uint16_t newPercentage);
  };


  /**
   * Constructor. The device constructor sets up the backlight with 0% cycle
   */

  template<class TAccessMode,bool TSmooth,R61523BacklightFrequency TFrequency,uint8_t TPolarity>
  inline R61523PwmBacklight<TAccessMode,TSmooth,TFrequency,TPolarity>::R61523PwmBacklight()
    : _currentPercentage(0) {
  }


  /**
   * Fade up or down to the supplied percentage waiting for msPerStep millis between each step.
   * If TSmooth is true then this parameter is ignored because the R61523 will go smooth for us.
   * @param newPercentage 0..100
   * @param msPerStep Milliseconds to pause between each step
   */

  template<class TAccessMode,bool TSmooth,R61523BacklightFrequency TFrequency,uint8_t TPolarity>
  inline void R61523PwmBacklight<TAccessMode,TSmooth,TFrequency,TPolarity>::fadeTo(uint16_t newPercentage,int msPerStep) {

    int8_t direction;

    // check for no change

    if(newPercentage==_currentPercentage)
      return;

    if(TSmooth)
      setPercentage(newPercentage);     // hardware controlled smooth operation
    else {

      // control the smooth operation ourselves

      direction=newPercentage>_currentPercentage ? 1 : -1;

      while(newPercentage!=_currentPercentage) {
        newPercentage+=direction;
        setPercentage(newPercentage);

        delay(msPerStep);
      }
    }
  }


  /**
   * Set the backlight percentage value
   * @param newPercentage
   */

  template<class TAccessMode,bool TSmooth,R61523BacklightFrequency TFrequency,uint8_t TPolarity>
  inline void R61523PwmBacklight<TAccessMode,TSmooth,TFrequency,TPolarity>::setPercentage(uint16_t newPercentage) {

    uint8_t dutyCycle,dim,polarity;

    // calculate the duty cycle (0..255)

    dutyCycle=(newPercentage*255)/100;

    dim=TSmooth ? 1 : 0;
    polarity=TPolarity ? 1 << 2 : 0;

    // set the register value

    TAccessMode::writeCommand(r61523::BACKLIGHT_CONTROL_2);
    TAccessMode::writeData(0x1);                       // PWMON=1
    TAccessMode::writeData(dutyCycle);                 // BDCV=duty cycle
    TAccessMode::writeData(TFrequency);                // 13.7kHz
    TAccessMode::writeData(0x18 | dim | polarity);     // PWMWM=1, LEDPWME=1

    // remember current setting

    _currentPercentage=newPercentage;
  }
}
