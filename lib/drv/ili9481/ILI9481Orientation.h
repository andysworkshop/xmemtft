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
 * @file ILI9481Orientation.h
 * @brief Generic template definition.
 * @ingroup ILI9481
 */


#pragma once


namespace lcd {


	/**
	 * @brief Forward declaration of the ILI9481Orientation template
	 * Empty generic class definition for ILI9481 orientation-dependent operations
	 * Everything is provided in the specialisations.
	 * @ingroup ILI9481
	 */

	template<Orientation TOrientation,class TAccessMode>
	class ILI9481Orientation {
	};
}


/*
 * Now include the specialisations
 */

#include "ILI9481PortraitSpecialisation.h"
#include "ILI9481LandscapeSpecialisation.h"
