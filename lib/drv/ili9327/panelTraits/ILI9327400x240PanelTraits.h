/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

/**
 * @file ILI9327400x240PanelTraits.h
 * @brief Panel traits for a 400x240 ILI9327 panel
 * @ingroup ILI9327
 */


#pragma once


namespace lcd {


	/**
	 * Traits class for the ILI9327 that declares a "short" panel
	 * of 400x240, less than the driver maximum of 432x240
	 * @ingroup ILI9327
	 */

	class ILI9327400x240PanelTraits {

		public:
			enum {
				LONG_SIDE = 400,						///< this panel is 400 on the long side
				SHORT_SIDE = 240						///< this panel is 240 on the short side
			};
	};
}
