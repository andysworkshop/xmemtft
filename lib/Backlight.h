/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012,2013 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

#pragma once

#include "Arduino.h"


namespace lcd {

	/*
	 * Simple class to encapsulate a 0..100% backlight
	 * control managed on a PWM pin
	 */

	template<uint8_t pwmPin=2>
	class Backlight {

		protected:
			uint8_t _currentPercentage;

		public:

			/*
			 * Constructor, initialise the pin
			 */

			Backlight(uint8_t initialPercentage=0) {
				pinMode(pwmPin,OUTPUT);
				analogWrite(pwmPin,initialPercentage);
				_currentPercentage=initialPercentage;
			}


			/*
			 * Set the percentage
			 */

			void setPercentage(uint8_t percentage) {
				analogWrite(pwmPin,((uint16_t)percentage)*255/100);
				_currentPercentage=percentage;
			}


			/*
			 * fade up or down to the supplied percentage waiting
			 * for msPerStep millis between each step
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

