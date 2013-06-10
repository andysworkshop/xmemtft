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


namespace lcd {
	namespace ili9481 {

		enum {

			ENTER_SLEEP_MODE = 0x10,
			EXIT_SLEEP_MODE = 0x11,
			ENTER_NORMAL_MODE = 0x13,

			SET_DISPLAY_ON = 0x29,

			SET_COLUMN_ADDRESS = 0x2a,
			SET_PAGE_ADDRESS   = 0x2b,

			WRITE_MEMORY_START = 0x2c,

			SET_SCROLL_AREA = 0x33,
			SET_ADDRESS_MODE = 0x36,
			SET_SCROLL_START = 0x37,
			SET_PIXEL_FORMAT = 0x3a,

			FRAME_MEMORY_ACCESS_AND_INTERFACE_SETTING = 0xb3,

			PANEL_DRIVING = 0xc0,
			DISPLAY_TIMING_SETTING_NORMAL_MODE = 0xc1,
			DISPLAY_TIMING_SETTING_IDLE_MODE = 0xc3,
			FRAME_RATE_AND_INVERSION_CONTROL = 0xc5,
			INTERFACE_CONTROL = 0xc6,

			GAMMA_SETTING = 0xc8,

			POWER_SETTING = 0xd0,
			VCOM = 0xd1,
			POWER_SETTING_NORMAL_MODE = 0xd2,

			// SET_ADDRESS_MODE bits

			VERTICAL_FLIP 				= 1,
			HORIZONTAL_FLIP				= 1 << 1,
			BGR										= 1 << 3,
			VERTICAL_ORDER				= 1 << 4,
			PAGECOL_SELECTION			= 1 << 5,
			COLUMN_ADDRESS_ORDER	= 1 << 6,
			PAGE_ADDRESS_ORDER		= 1 << 7,

			// POWER_SETTING bits

			VC_095=0, VC_090=1, VC_085=2, VC_080=3, VC_075=4, VC_070=5, VC_DISABLE=6, VC_100=7,
			BT_6_5=0, BT_6_4=1, BT_6_3=2, BT_5_5=3, BT_5_4=4, BT_5_3=5, BT_4_4=6, BT_4_3=7,
			VCIRE=1 << 7,

			// INTERFACE_CONTROL bits

			DPL=1, EPL=1 << 1, HSPL=1 << 3, VSPL=1 << 4, SDA_EN=1 << 7,

			// SET_COLOUR_MODE bits

			COLOURS_8=0x11,
			COLOURS_64K=0x55,
			COLOURS_262K=0x66
		};
	}
}
