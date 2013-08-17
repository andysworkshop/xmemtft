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
 * @defgroup HX8352A
 * @brief Himax HX8352A
 *
 * The user can specialise based on the desired colour depth, orientation and access mode.
 *
 * @file HX8352A.h
 * @brief Core HX8352A support. Contains the initialisation sequence and other non-specific members.
 * @ingroup HX8352A
 */

#pragma once

#include "commands/Allcommands.h"
#include "HX8352AColour.h"
#include "HX8352AOrientation.h"
#include "HX8352AGamma.h"


namespace lcd {

	/**
	 * @brief Generic HX8352A template.
	 * @tparam TOrientation The desired panel orientation, LANDSCAPE or PORTRAIT
	 * @tparam TColourDepth The colour depth for your use, just 64K is supported for this panel.
	 * @tparam TAccessMode The access mode that you want to talk to this panel with, e.g. Gpio16LatchAccessMode.
	 * @tparam TPanelTraits Constants and functions specific to the actual panel.
	 */

	template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
	class HX8352A : public HX8352AColour<TColourDepth,TAccessMode>,
									public HX8352AOrientation<TOrientation,TAccessMode,TPanelTraits> {

		public:
			enum {
				SHORT_SIDE = TPanelTraits::SHORT_SIDE,
				LONG_SIDE = TPanelTraits::LONG_SIDE
			};

		public:
			HX8352A();

			void initialise() const;

			void applyGamma(HX8352AGamma& gamma) const;
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
	inline HX8352A<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::HX8352A() {
		initialise();
	}


	/**
	 * Initialise the LCD. Do the reset sequence.
	 */

	template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
	inline void HX8352A<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::initialise() const {

		// initialise the access mode

		TAccessMode::initialise();

		// reset the device

		TAccessMode::hardReset();

		// the panels are different, so the setup and initialisation moves to the traits

		TPanelTraits::template initialise<TAccessMode>();

		// set the orientation and scroll area

		TAccessMode::writeCommandData(hx8352a::MEMORY_ACCESS_CONTROL,this->getMemoryAccessControl());
		setScrollArea(0,TPanelTraits::LONG_SIDE);
	}


	/**
	 * Send the panel to sleep
	 */

	template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
	inline void HX8352A<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::sleep() const {

		// display Off
		TAccessMode::writeCommandData(hx8352a::DISPLAY_CONTROL_2,0x38); 			//GON=1, DTE=1, D=10
		delay(40);

		TAccessMode::writeCommandData(hx8352a::DISPLAY_CONTROL_2,0x28); 			//GON=1, DTE=0, D=10
		delay(40);

		TAccessMode::writeCommandData(hx8352a::DISPLAY_CONTROL_2,0x00); 			//GON=0, DTE=0, D=00

		// power Off
		TAccessMode::writeCommandData(hx8352a::POWER_CONTROL_6,0x14); 			// VCOMG=0, VDV=1_0100
		delay(10);

		TAccessMode::writeCommandData(hx8352a::POWER_CONTROL_1,0x02); 		// GASENB=0, PON=0, DK=0, XDK=0, VLCD_TRI=1, STB=0
		delay(10);

		TAccessMode::writeCommandData(hx8352a::POWER_CONTROL_1,0x0A); 		// GASENB=0, PON=0, DK=1, XDK=0, VLCD_TRI=1, STB=0
		delay(10);

		TAccessMode::writeCommandData(hx8352a::POWER_CONTROL_3,0x40); 		// AP=000
		delay(10);

		TAccessMode::writeCommandData(hx8352a::SOURCE_CONTROL_1,0x00); 	// N_SAP=1100 0000
		delay(10);

		// into STB mode
		TAccessMode::writeCommandData(hx8352a::POWER_CONTROL_1,0x0B); 		// GASENB=0, PON=0, DK=0, XDK=0, VLCD_TRI=1, STB=1
		delay(10);

		// stop oscillation
		TAccessMode::writeCommandData(hx8352a::OSC_CONTROL_1,0x90); 			// RADJ=1001, OSC_EN=0
	}


	/**
	 * Apply the panel gamma settings
	 * @param gamma The gamma class containing the one value
	 */

	template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
	inline void HX8352A<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::applyGamma(HX8352AGamma& gamma) const {
		TAccessMode::writeCommand(hx8352a::GAMMA_1+0,gamma[0]);
		TAccessMode::writeCommand(hx8352a::GAMMA_1+1,gamma[1]);
		TAccessMode::writeCommand(hx8352a::GAMMA_1+2,gamma[2]);
		TAccessMode::writeCommand(hx8352a::GAMMA_1+3,gamma[3]);
		TAccessMode::writeCommand(hx8352a::GAMMA_1+4,gamma[4]);
		TAccessMode::writeCommand(hx8352a::GAMMA_1+5,gamma[5]);
		TAccessMode::writeCommand(hx8352a::GAMMA_1+6,gamma[6]);
		TAccessMode::writeCommand(hx8352a::GAMMA_1+7,gamma[7]);
		TAccessMode::writeCommand(hx8352a::GAMMA_1+8,gamma[8]);
		TAccessMode::writeCommand(hx8352a::GAMMA_1+9,gamma[9]);
		TAccessMode::writeCommand(hx8352a::GAMMA_1+10,gamma[10]);
		TAccessMode::writeCommand(hx8352a::GAMMA_1+11,gamma[11]);
	}


	/**
	 * Wake the panel up. The wakeup sequence needs to set the power and
	 * oscillation parameters which are panel-specific. Hence we defer to
	 * the panel traits for the implementation.
	 */

	template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
	inline void HX8352A<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::wake() const {
		TPanelTraits::template wake<TAccessMode>();
	}


	/**
	 * Issue the command that allows graphics ram writing to commence
	 */

	template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
	inline void HX8352A<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::beginWriting() const {
	  TAccessMode::writeCommand(hx8352a::MEMORY_WRITE);
	}


	/**
	 * Set the scroll area to a full-width rectangle region
	 * @param y The y-co-ord of the region
	 * @param height The height of the region
	 */

	template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
	inline void HX8352A<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::setScrollArea(uint16_t y,uint16_t height) const {

		uint16_t bfa;

		bfa=TPanelTraits::LONG_SIDE-height-y;

		TAccessMode::writeCommandData(hx8352a::VERTICAL_SCROLL_TOP_FIXED_AREA_H,y >> 8);
		TAccessMode::writeCommandData(hx8352a::VERTICAL_SCROLL_TOP_FIXED_AREA_L,y & 0xff);

		TAccessMode::writeCommandData(hx8352a::VERTICAL_SCROLL_HEIGHT_H,height >> 8);
		TAccessMode::writeCommandData(hx8352a::VERTICAL_SCROLL_HEIGHT_L,height & 0xff);

		TAccessMode::writeCommandData(hx8352a::VERTICAL_SCROLL_BOTTOM_FIXED_AREA_H,bfa >> 8);
		TAccessMode::writeCommandData(hx8352a::VERTICAL_SCROLL_BOTTOM_FIXED_AREA_L,bfa & 0xff);
	}


	/**
	 * Transfer data bytes from flash (program) memory, en-masse
	 * @param data The address of the bytes to transfer
	 * @param numBytes The number of bytes to transfer
	 */

	template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode,class TPanelTraits>
	inline void HX8352A<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::rawFlashTransfer(uint32_t data,uint32_t numBytes) const {

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
	inline void HX8352A<TOrientation,TColourDepth,TAccessMode,TPanelTraits>::rawSramTransfer(uint8_t *data,uint32_t numBytes) const {

		uint32_t numPixels;

		numPixels=numBytes/2;

		while(numPixels--) {
			TAccessMode::writeData(data[0],data[1]);
			data+=2;
		}
	}
}
