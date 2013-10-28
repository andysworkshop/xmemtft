/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012,2013 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

/**
 * @file ILI9481Gamma.h
 * @brief Gamma support for the ILI9481
 * @ingroup ILI9481
 */

#pragma once

#include "DisplayDeviceGamma.h"


namespace lcd {

	/**
	 * @brief Gamma values for the ILI9481
	 *
	 * Samples for 3.5 inch QDS LCD: 0,0x30,0x36,0x45,0x4,0x16,0x37,0x75,0x77,0x54,0xf,0x0
	 *
	 * @ingroup ILI9481
	 */

	struct HX8352AGamma : DisplayDeviceGamma<HX8352AGamma,uint8_t> {

	/**
	 * Constructor. The HX8352A takes 12 gamma values. The constructor must be supplied with those values.
	 * Example: 0xA0,0x03,0x00,0x45,0x03,0x47,0x23,0x77,0x01,0x1F,0x0F,0x03
	 */

		HX8352AGamma(
				uint16_t g1,uint16_t g2,uint16_t g3,uint16_t g4,uint16_t g5,uint16_t g6,
				uint16_t g7,uint16_t g8,uint16_t g9,uint16_t g10,uint16_t g11,uint16_t g12)
					: DisplayDeviceGamma<HX8352AGamma,uint8_t>(12) {

			_gamma[0]=g1;
			_gamma[1]=g2;
			_gamma[2]=g3;
			_gamma[3]=g4;
			_gamma[4]=g5;
			_gamma[5]=g6;
			_gamma[6]=g7;
			_gamma[7]=g8;
			_gamma[8]=g9;
			_gamma[9]=g10;
			_gamma[10]=g11;
			_gamma[11]=g12;
		}

		/**
     * Get the maximum value for an index
     * @return the index maximum
     */

    static uint16_t getMaximumValue(uint16_t index) {
      return 0xffff;
    }
};
}
