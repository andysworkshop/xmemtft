/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

#pragma once


namespace lcd {

	/*
	 * set the foreground
	 */

	template<class TDevice,class TDeviceAccessMode>
	inline void GraphicsLibrary<TDevice,TDeviceAccessMode>::setForeground(TColour cr) {
		this->unpackColour(cr,_foreground);
	}

	/*
	 * set the background
	 */

	template<class TDevice,class TDeviceAccessMode>
	inline void GraphicsLibrary<TDevice,TDeviceAccessMode>::setBackground(TColour cr) {
		this->unpackColour(cr,_background);
	}


	/*
	 * Get the panel maximum x-coord
	 */

	template<class TDevice,class TDeviceAccessMode>
	inline int16_t GraphicsLibrary<TDevice,TDeviceAccessMode>::getXmax() const {
	  return this->getWidth()-1;
	}

	/*
	 * Get the panel maximum y-coord
	 */

	template<class TDevice,class TDeviceAccessMode>
	inline int16_t GraphicsLibrary<TDevice,TDeviceAccessMode>::getYmax() const {
		return this->getHeight()-1;
	}

	/*
	 * clear screen to the background colour
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


	/*
	 * min, max, abs in the C libraries are a total trainwreck. macros? functions? you just can't rely on it.
	 * We'll avoid that disaster zone and do it the STL way. i.e. the right way.
	 */

	template<class TDevice,class TDeviceAccessMode>
	template<typename T>
	inline const T& GraphicsLibrary<TDevice,TDeviceAccessMode>::Max(const T& a,const T& b) {
		return (a>b) ? a : b;
	}

	template<class TDevice,class TDeviceAccessMode>
	template<typename T>
	inline const T& GraphicsLibrary<TDevice,TDeviceAccessMode>::Min(const T& a,const T& b) {
		return (a<b) ? a : b;
	}

	template<class TDevice,class TDeviceAccessMode>
	template<typename T>
	inline const T GraphicsLibrary<TDevice,TDeviceAccessMode>::Abs(const T a) {
		return a<0 ? -a : a;
	}
}
