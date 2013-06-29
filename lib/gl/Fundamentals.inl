/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

/**
 * @file Fundamentals.inl
 * @brief Helper functions, colour setters etc.
 * @ingroup GraphicsLibrary
 */

#pragma once


namespace lcd {

	/**
	 * Set the foreground colour
	 * @param cr The foreground colour.
	 */

	template<class TDevice,class TDeviceAccessMode>
	inline void GraphicsLibrary<TDevice,TDeviceAccessMode>::setForeground(TColour cr) {
		this->unpackColour(cr,_foreground);
	}


	/**
	 * Set the background colour
	 * @param cr The foreground colour.
	 */

	template<class TDevice,class TDeviceAccessMode>
	inline void GraphicsLibrary<TDevice,TDeviceAccessMode>::setBackground(TColour cr) {
		this->unpackColour(cr,_background);
	}


	/**
	 * Get the panel maximum x-coord
	 * @return The last co-ordinate on the X-axis
	 */

	template<class TDevice,class TDeviceAccessMode>
	inline int16_t GraphicsLibrary<TDevice,TDeviceAccessMode>::getXmax() const {
	  return this->getWidth()-1;
	}


	/**
	 * Get the panel maximum y-coord
	 * @return The last co-ordinate on the Y-axis
	 */

	template<class TDevice,class TDeviceAccessMode>
	inline int16_t GraphicsLibrary<TDevice,TDeviceAccessMode>::getYmax() const {
		return this->getHeight()-1;
	}


	/**
	 * Clear screen to the background colour
	 */

	template<class TDevice,class TDeviceAccessMode>
	inline void GraphicsLibrary<TDevice,TDeviceAccessMode>::clearScreen() const {

		this->moveTo(
				Rectangle(
						0,
						0,
						this->getWidth(),
						this->getHeight()
				)
		);

		this->fillPixels((int32_t)TDevice::LONG_SIDE * (int32_t)TDevice::SHORT_SIDE,_background);
	}


	/**
	 * template Max() implementation
	 * @param a The first type to compare, as a reference
	 * @param b The second type to compare, as a reference
	 * @return The greater of the two types, as a reference
	 */

	template<class TDevice,class TDeviceAccessMode>
	template<typename T>
	inline const T& GraphicsLibrary<TDevice,TDeviceAccessMode>::Max(const T& a,const T& b) {
		return (a>b) ? a : b;
	}


	/**
	 * template Min() implementation
	 * @param a The first type to compare, as a reference
	 * @param b The second type to compare, as a reference
	 * @return The lesser of the two types, as a reference
	 */

	template<class TDevice,class TDeviceAccessMode>
	template<typename T>
	inline const T& GraphicsLibrary<TDevice,TDeviceAccessMode>::Min(const T& a,const T& b) {
		return (a<b) ? a : b;
	}


	/**
	 * template Abs() implementation
	 * @param a The input value.
	 * @return The value, made positive if it wasn't already.
	 */

	template<class TDevice,class TDeviceAccessMode>
	template<typename T>
	inline const T GraphicsLibrary<TDevice,TDeviceAccessMode>::Abs(const T a) {
		return a<0 ? -a : a;
	}
}
