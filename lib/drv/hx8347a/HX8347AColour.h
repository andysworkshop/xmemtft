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
	 * Empty generic class definition for HX8347A colour-dependent operations
	 * Everything is provided in the specialisations.
	 */

	template<ColourDepth TColour,class TAccessMode>
	class HX8347AColour;
}


/*
 * Now include the specialisations
 */

#include "HX8347AColour16Specialisation.h"
