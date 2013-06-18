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
 * @file Xmem16AccessMode.cpp
 * Initialise the static members in the class.
 */


#include "Arduino.h"
#include "Xmem16AccessMode.h"


namespace lcd {

	uint8_t Xmem16AccessMode::_streamIndex=0;
	uint8_t Xmem16AccessMode::_streamByte=0;
}

