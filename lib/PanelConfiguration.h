/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012,2013 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

/**
 * @file PanelConfiguration.h
 * @brief Enumerations for panel configuration.
 */

#pragma once


namespace lcd {

	/**
	 * Possible locations for data
	 */

	enum MemoryLocation {
		FLASH_UNCOMPRESSED,     ///< it's in flash (program) memory
   	FLASH_COMPRESSED,       ///< it's in flash, and it's compressed
   	SRAM                  	///< it's in the SRAM address space
	};


	/**
	 * Possible display orientations
	 */

	enum Orientation {
		PORTRAIT,								///< long side up
		LANDSCAPE								///< short side up
	};


	/**
	 * Possible colour depths. Not every colour depth is guaranteed to be
	 * supported by the driver embedded in the panel.
	 */

	enum ColourDepth {
		COLOURS_16BIT,					///< 64K colours
		COLOURS_18BIT,					///< 262K colours
		COLOURS_24BIT						///< 16M colours
	};


	/**
	 * Possible directions (used by gradient fill)
	 */

	enum Direction {
		HORIZONTAL,						///< going horizontally
		VERTICAL							///< going vertically
	};
}
