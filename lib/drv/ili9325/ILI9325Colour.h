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

namespace lcd {

	/**
	 * Empty generic class definition for ILI9325 colour-dependent operations
	 * Everything is provided in the specialisations.
	 */

	template<ColourDepth TColour,class TAccessMode>
	class ILI9325Colour;
}

/*
 * Now include the specialisations
 */

#include "ILI9325Colour16Specialisation.h"
#include "ILI9325Colour18Specialisation.h"
