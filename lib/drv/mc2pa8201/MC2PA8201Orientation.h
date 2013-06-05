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


	/**
	 * Empty generic class definition for MC2PA8201 orientation-dependent operations
	 * Everything is provided in the specialisations.
	 */

	template<Orientation TOrientation,class TAccessMode,class TPanelTraits>
	class MC2PA8201Orientation {
	};
}


/*
 * Now include the specialisations
 */

#include "MC2PA8201PortraitSpecialisation.h"
#include "MC2PA8201LandscapeSpecialisation.h"
