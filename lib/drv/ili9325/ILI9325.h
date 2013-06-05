/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012,2013 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

/*
 * Implementation for Adafruit TFT LCD copyright (c) 2013 Colin Irwin, see
 * http://aethersdr.org/ for details. Provided under original terms and
 * conditions.
 *
 */

#pragma once

#include "Arduino.h"
#include "commands/Allcommands.h"
#include "ILI9325Colour.h"
#include "ILI9325Orientation.h"

namespace lcd {

	/**
	 * Generic ILI9325 template. The user can specialise based on the desired colour
	 * depth, orientation and access mode.
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

		TAccessMode::writeCommandData(ILI932X_START_OSC,0x0001);

		delay(50);

		TAccessMode::writeCommandData(ILI932X_DRIV_OUT_CTRL,0x0100);
		TAccessMode::writeCommandData(ILI932X_DRIV_WAV_CTRL,0x0700);
		TAccessMode::writeCommandData(ILI932X_RESIZE_CTRL,0x0000);
		TAccessMode::writeCommandData(ILI932X_DISP_CTRL2,0x0202);
		TAccessMode::writeCommandData(ILI932X_DISP_CTRL3,0x0000);
		TAccessMode::writeCommandData(ILI932X_DISP_CTRL4,0x0000);
		TAccessMode::writeCommandData(ILI932X_RGB_DISP_IF_CTRL1,0x0);
		TAccessMode::writeCommandData(ILI932X_FRM_MARKER_POS,0x0);
		TAccessMode::writeCommandData(ILI932X_RGB_DISP_IF_CTRL2,0x0);
		TAccessMode::writeCommandData(ILI932X_POW_CTRL1,0x0000);
		TAccessMode::writeCommandData(ILI932X_POW_CTRL2,0x0007);
		TAccessMode::writeCommandData(ILI932X_POW_CTRL3,0x0000);
		TAccessMode::writeCommandData(ILI932X_POW_CTRL4,0x0000);

		delay(200);

		TAccessMode::writeCommandData(ILI932X_POW_CTRL1,0x1690);
		TAccessMode::writeCommandData(ILI932X_POW_CTRL2,0x0227);

		delay(50);

		TAccessMode::writeCommandData(ILI932X_POW_CTRL3,0x001A);

		delay(50);

		TAccessMode::writeCommandData(ILI932X_POW_CTRL4,0x1800);
		TAccessMode::writeCommandData(ILI932X_POW_CTRL7,0x002A);

		delay(50);

		TAccessMode::writeCommandData(ILI932X_GAMMA_CTRL1,0x0000);
		TAccessMode::writeCommandData(ILI932X_GAMMA_CTRL2,0x0000);
		TAccessMode::writeCommandData(ILI932X_GAMMA_CTRL3,0x0000);
		TAccessMode::writeCommandData(ILI932X_GAMMA_CTRL4,0x0206);
		TAccessMode::writeCommandData(ILI932X_GAMMA_CTRL5,0x0808);
		TAccessMode::writeCommandData(ILI932X_GAMMA_CTRL6,0x0007);
		TAccessMode::writeCommandData(ILI932X_GAMMA_CTRL7,0x0201);
		TAccessMode::writeCommandData(ILI932X_GAMMA_CTRL8,0x0000);
		TAccessMode::writeCommandData(ILI932X_GAMMA_CTRL9,0x0000);
		TAccessMode::writeCommandData(ILI932X_GAMMA_CTRL10,0x0000);
		TAccessMode::writeCommandData(ILI932X_GRAM_HOR_AD,0x0000);
		TAccessMode::writeCommandData(ILI932X_GRAM_VER_AD,0x0000);
		TAccessMode::writeCommandData(ILI932X_HOR_START_AD,0x0000);
		TAccessMode::writeCommandData(ILI932X_HOR_END_AD,0x00EF);
		TAccessMode::writeCommandData(ILI932X_VER_START_AD,0X0000);
		TAccessMode::writeCommandData(ILI932X_VER_END_AD,0x013F);
		TAccessMode::writeCommandData(ILI932X_GATE_SCAN_CTRL1,0xA700);
		TAccessMode::writeCommandData(ILI932X_GATE_SCAN_CTRL2,0x0003);
		TAccessMode::writeCommandData(ILI932X_GATE_SCAN_CTRL3,0x0000);
		TAccessMode::writeCommandData(ILI932X_PANEL_IF_CTRL1,0X0010);
		TAccessMode::writeCommandData(ILI932X_PANEL_IF_CTRL2,0X0000);
		TAccessMode::writeCommandData(ILI932X_PANEL_IF_CTRL3,0X0003);
		TAccessMode::writeCommandData(ILI932X_PANEL_IF_CTRL4,0X1100);
		TAccessMode::writeCommandData(ILI932X_PANEL_IF_CTRL5,0X0000);
		TAccessMode::writeCommandData(ILI932X_PANEL_IF_CTRL6,0X0000);
		TAccessMode::writeCommandData(ILI932X_DISP_CTRL1,0x0133);

		// The following needs to be reviewed/changed potentially to deal
		// with a different orientation.
		// (Other values depending on the exact orientation are:
		//      default: 0x1030
		//      case 1 : 0x1028
		//      case 2 : 0x1000
		//      case 3 : 0x1018)

		TAccessMode::writeCommandData(ILI932X_ENTRY_MOD,this->getInterfacePixelFormat() | 0x1000 | this->getMemoryAccessControl());
	}

	/**
	 * Send the panel to sleep
	 */

	template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
	inline void ILI9325<TOrientation,TColourDepth,TAccessMode>::sleep() const {
		TAccessMode::writeCommandData(ILI932X_DISP_CTRL1,0x0000);
		TAccessMode::writeCommandData(ILI932X_POW_CTRL1,0x0001);
	}

	/**
	 * Wake the panel up
	 */

	template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
	inline void ILI9325<TOrientation,TColourDepth,TAccessMode>::wake() const {
		TAccessMode::writeCommandData(ILI932X_POW_CTRL1,0x1690);
		TAccessMode::writeCommandData(ILI932X_DISP_CTRL1,0x0133);
	}

	/**
	 * Issue the command that allows graphics ram writing to commence
	 */

	template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
	inline void ILI9325<TOrientation,TColourDepth,TAccessMode>::beginWriting() const {
		TAccessMode::writeCommand(ILI932X_RW_GRAM);
	}

	/**
	 * Set the scroll area to a full-width rectangle region
	 * @param y The y-co-ord of the region
	 * @param height The height of the region
	 */

	template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
	inline void ILI9325<TOrientation,TColourDepth,TAccessMode>::setScrollArea(uint16_t y,uint16_t height) const {
		/*
		 uint16_t bfa;

		 bfa=320-height-y;

		 //        TAccessMode::writeCommand(ili9325::VERTICAL_SCROLLING_DEFINITION);
		 TAccessMode::writeData(y >> 8);
		 TAccessMode::writeData(y & 0xff);
		 TAccessMode::writeData(height >> 8);
		 TAccessMode::writeData(height & 0xff);
		 TAccessMode::writeData(bfa >> 8);
		 TAccessMode::writeData(bfa & 0xff);
		 */
	}

	/**
	 * Transfer data bytes, en-masse
	 */

	template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
	inline void ILI9325<TOrientation,TColourDepth,TAccessMode>::rawFlashTransfer(uint32_t data,uint32_t numBytes) const {
		while(numBytes--)
			TAccessMode::writeData(pgm_read_byte_near(data++));
	}

	/**
	 * Write raw bytes from SRAM
	 * @param data data source
	 * @param numBytes number of bytes to write.
	 */

	template<Orientation TOrientation,ColourDepth TColourDepth,class TAccessMode>
	inline void ILI9325<TOrientation,TColourDepth,TAccessMode>::rawSramTransfer(uint8_t *data,uint32_t numBytes) const {
		while(numBytes--)
			TAccessMode::writeData(*data++);
	}
}
