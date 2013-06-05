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

#include "drv/lds285/commands/AllCommands.h"


namespace lcd {

	/**
	 * Panel traits for a Type A Nokia N95 8Gb. The type A screen does not
	 * flip column and row addresses in portrait mode
	 */

	class NokiaN95_8Gb_TypeA {
		public:
			template<Orientation TOrientation>
			static uint8_t getColumnAddressCommand();

			template<Orientation TOrientation>
			static uint8_t getRowAddressCommand();
	};


	/**
	 * Get the command used to set column address in portrait mode
	 * @return lds285::COLUMN_ADDRESS_SET
	 */

	template<>
	inline uint8_t NokiaN95_8Gb_TypeA::getColumnAddressCommand<PORTRAIT>() {
		return lds285::COLUMN_ADDRESS_SET;
	}


	/**
	 * Get the command used to set row address in portrait mode
	 * @return lds285::ROW_ADDRESS_SET
	 */

	template<>
	inline uint8_t NokiaN95_8Gb_TypeA::getRowAddressCommand<PORTRAIT>() {
		return lds285::ROW_ADDRESS_SET;
	}
}
