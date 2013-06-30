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
 * @file LDS285Colour.h
 * @brief Generic template definition.
 * @ingroup LDS285
 */

#pragma once


namespace lcd {

	/**
	 * @brief Forward declaration of the LDS285Colour template
	 *
	 * Empty generic class definition for LDS285 colour-dependent operations
	 * Everything is provided in the specialisations.
	 *
	 * @ingroup LDS285
	 */

	template<ColourDepth TColour,class TAccessMode,class TPanelTraits>
	class LDS285Colour;
}


/*
 * Now include the specialisations
 */

#include "LDS285Colour16Specialisation.h"
#include "LDS285Colour18Specialisation.h"
#include "LDS285Colour24Specialisation.h"
