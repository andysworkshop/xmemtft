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
 * @file DoublePrecision.h
 * @brief Management class for floating point output
 * @ingroup GraphicsLibrary
 */

#pragma once


/**
 * @brief Carrier class for a double and it's desired output precision.
 *
 * This class is used for text output so that you can specify how precise
 * you need the output to be.
 *
 * @ingroup GraphicsLibrary
 */

struct DoublePrecision {

	// public members

	double Value;						///< The floating point value
	uint8_t Precision;			///< The desired number of fractional digits

	/**
	 * Constructor. Must be fully constructed.
	 * @param d The double-precision value
	 * @param precision The desired number of fractional digits
	 */

	DoublePrecision(double d,uint8_t precision) {
		Value=d;
		Precision=precision;
	}
};
