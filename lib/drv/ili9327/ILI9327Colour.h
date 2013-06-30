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
 * @file ILI9327Colour.h
 * @brief Generic template definition.
 * @ingroup ILI9327
 */

#pragma once


namespace lcd {


	/**
	 * @brief Forward declaration of the ILI9327Colour template
	 *
	 * Empty generic class definition for ILI9327 colour-dependent operations
	 * Everything is provided in the specialisations.
	 *
	 * @ingroup ILI9327
	 */

	template<ColourDepth TColour,class TAccessMode>
	class ILI9327Colour;
}


/*
 * Now include the specialisations
 */

#include "ILI9327Colour16Specialisation.h"
