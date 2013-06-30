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
 * @file Point.cpp
 * @brief Static initialisers
 * @ingroup GraphicsLibrary
 */


#include <stdint.h>
#include "Point.h"


namespace lcd {

	/**
	 * @brief initialise the static member
	 */

	const Point Point::Origin=Point(0,0);
}
