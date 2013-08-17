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
 * @file LG_KF700PanelTraits.h
 * @brief Panel traits for the LG KF700 cellphone panel
 * @ingroup HX8352A
 */


#pragma once


namespace lcd {


	/**
	 * @ingroup HX8352A
	 */

	class LG_KF700PanelTraits {

		public:
			enum {
				LONG_SIDE = 480,						///< this panel is 480 on the long side
				SHORT_SIDE = 240						///< this panel is 240 on the short side
			};

		public:
			template<class TAccessMode>
			static void initialise();

			template<class TAccessMode>
			static void wake();
	};


	/**
	 * Initialise the panel
	 */

	template<class TAccessMode>
	inline void LG_KF700PanelTraits::initialise() {

		// do the startup sequence

		delay(160);
		TAccessMode::writeCommandData(hx8352a::TEST_MODE_CONTROL,0x02);        	// TESTM=1
		TAccessMode::writeCommandData(hx8352a::VDDD_CONTROL,0x02);        			// VDC_SEL=010.
		TAccessMode::writeCommandData(hx8352a::SOURCE_GAMMA_RESISTOR_1,0x00);   // STBA[15:8]=0x00
		TAccessMode::writeCommandData(hx8352a::SOURCE_GAMMA_RESISTOR_2,0xB3);   // STBA[7]=1, STBA[5:4]=11, STBA[1:0]=11
		TAccessMode::writeCommandData(hx8352a::TEST_MODE_CONTROL,0x00);        	// TESTM=0

		// Power Supply Setting

		TAccessMode::writeCommandData(hx8352a::OSC_CONTROL_1,0x91);         	// RADJ=0, OSC_EN=1 (100%)
		TAccessMode::writeCommandData(hx8352a::DISPLAY_CONTROL_1,0x01);       // TE ON
		TAccessMode::writeCommandData(hx8352a::CYCLE_CONTROL_1,0x14);        	// N_DCDC=0x14

		delay(20);

		TAccessMode::writeCommandData(hx8352a::POWER_CONTROL_3,0x13);        // BT=0001, AP=100
		TAccessMode::writeCommandData(hx8352a::POWER_CONTROL_2,0x11);        // VC3=001, VC1=001 (VLCD/DDVDH)=6.45V)
		TAccessMode::writeCommandData(hx8352a::POWER_CONTROL_4,0x0);         // gamma x2.8
		TAccessMode::writeCommandData(hx8352a::POWER_CONTROL_5,0x08);        // VBGP=1111
		TAccessMode::writeCommandData(hx8352a::VCOM_CONTROL,0x3B);        	 // VCM=011_1011

		delay(30);

		TAccessMode::writeCommandData(hx8352a::POWER_CONTROL_1,0x0A);        // GASENB=0, PON=0, DK=1, XDK=0, VLCD_TRI=1, STB=0
		TAccessMode::writeCommandData(hx8352a::POWER_CONTROL_1,0x1A);        // GASENB=0, PON=1, DK=1, XDK=0, VLCD_TRI=1, STB=0

		delay(50);

		TAccessMode::writeCommandData(hx8352a::POWER_CONTROL_1,0x12);      	// GASENB=0, PON=1, DK=0, XDK=0, VLCD_TRI=1, STB=0,

		// VLCD=2XVCI by 2 CAPs

		delay(50);
		TAccessMode::writeCommandData(hx8352a::POWER_CONTROL_6,0x2E);       // VCOMG=1, VDV=0_1110

		//VCOMG NEW LOCATION
		TAccessMode::writeCommandData(hx8352a::TEST_MODE_CONTROL,0x02);     // TESTM=1
		TAccessMode::writeCommandData(0x93,0x10);        										// R93[4]=1, VCOMG=1 ...undocumented!!!
		TAccessMode::writeCommandData(hx8352a::TEST_MODE_CONTROL,0x00);

		// DGC Function disabled
		TAccessMode::writeCommandData(0x5A,0x00);

		// Display ON Setting
		TAccessMode::writeCommandData(hx8352a::SOURCE_CONTROL_1,0xFF);      // N_SAP=0111 1111
		TAccessMode::writeCommandData(hx8352a::SOURCE_CONTROL_2,0x0E);      // I_SAP=0000 1110
		TAccessMode::writeCommandData(hx8352a::CYCLE_CONTROL_10,0x38);      // EQS=1000 0111
		TAccessMode::writeCommandData(hx8352a::CYCLE_CONTROL_11,0x38);      // EQP=0011 1000
		TAccessMode::writeCommandData(hx8352a::DISPLAY_CONTROL_2,0x38);     // GON=1, DTE=1, D=10

		delay(50);
		TAccessMode::writeCommandData(hx8352a::DISPLAY_CONTROL_2,0x3C);     		// GON=1, DTE=1, D=11
		TAccessMode::writeCommandData(hx8352a::DISPLAY_MODE_CONTROL,0x02);      // INVON=0, NORNO=1
	}


	/**
	 * Wake the panel up from standby mode. Only a subset of the initialisation sequence is actually
	 * required but we'll save some code and just call initialise() again to bring it back to life.
	 * @param accessMode The access mode
	 */

	template<class TAccessMode>
	inline void LG_KF700PanelTraits::wake() {
		LG_KF700PanelTraits::initialise<TAccessMode>();
	}
}
