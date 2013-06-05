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


/*
 * Carrier class for a double and it's desired output
 * precision
 */

struct DoublePrecision {

	// public members

	double Value;
	uint8_t Precision;

	/*
	 * Constructor. Must be fully constructed.
	 */

	DoublePrecision(double d,uint8_t precision) {
		Value=d;
		Precision=precision;
	}
};
