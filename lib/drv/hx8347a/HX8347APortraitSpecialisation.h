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
	 * Specialisation of HX8347AOrientation for the panel in PORTRAIT mode.
	 * @tparam TAccessMode the access mode implementation, eg Xmem16AccessMode
	 */

	template<class TAccessMode>
	class HX8347AOrientation<PORTRAIT,TAccessMode> {

		protected:
			uint16_t getOrientationMemoryAccessCtrl() const;

		public:
			int16_t getWidth() const;
			int16_t getHeight() const;
			void moveTo(const Rectangle& rc) const;

			void setScrollPosition(int16_t scrollPosition) const;
	};


	/**
	 * Get the register setting for memory access control
	 * @return The entry mode register setting for portrait
	 */

	template<class TAccessMode>
	inline uint16_t HX8347AOrientation<PORTRAIT,TAccessMode>::getOrientationMemoryAccessCtrl() const {
		return 1 << 6;		// MX
	}


	/**
	 * Get the width in pixels
	 * @return 240px
	 */

	template<class TAccessMode>
	inline int16_t HX8347AOrientation<PORTRAIT,TAccessMode>::getWidth() const {
		return 240;
	}


	/**
	 * Get the height in pixels
	 * @return 320px
	 */

	template<class TAccessMode>
	inline int16_t HX8347AOrientation<PORTRAIT,TAccessMode>::getHeight() const {
		return 320;
	}


	/**
	 * Move the display output rectangle
	 * @param rc The display output rectangle
	 */

	template<class TAccessMode>
	inline void HX8347AOrientation<PORTRAIT,TAccessMode>::moveTo(const Rectangle& rc) const {

		TAccessMode::writeCommandData(hx8347a::COLUMN_ADDRESS_START_HIGH,rc.X >> 8);
		TAccessMode::writeCommandData(hx8347a::COLUMN_ADDRESS_START_LOW,rc.X & 0xff);
		TAccessMode::writeCommandData(hx8347a::COLUMN_ADDRESS_END_HIGH,(rc.X+rc.Width-1) >> 8);
		TAccessMode::writeCommandData(hx8347a::COLUMN_ADDRESS_END_LOW,(rc.X+rc.Width-1) & 0xff);

		TAccessMode::writeCommandData(hx8347a::ROW_ADDRESS_START_HIGH,rc.Y >> 8);
		TAccessMode::writeCommandData(hx8347a::ROW_ADDRESS_START_LOW,rc.Y & 0xff);
		TAccessMode::writeCommandData(hx8347a::ROW_ADDRESS_END_HIGH,(rc.Y+rc.Height-1) >> 8);
		TAccessMode::writeCommandData(hx8347a::ROW_ADDRESS_END_LOW,(rc.Y+rc.Height-1) & 0xff);
	}


	/**
	 * Set a vertical scroll position
	 * @param scrollPosition The new scroll position
	 */

	template<class TAccessMode>
	inline void HX8347AOrientation<PORTRAIT,TAccessMode>::setScrollPosition(int16_t scrollPosition) const {

		scrollPosition=scrollPosition ? 320-scrollPosition : 0;

		if(scrollPosition<0)
			scrollPosition+=320;
		else if(scrollPosition>319)
			scrollPosition-=320;

		// write to the register

		TAccessMode::writeCommandData(hx8347a::SET_SCROLL_START_HIGH,scrollPosition >> 8);
		TAccessMode::writeCommandData(hx8347a::SET_SCROLL_START_LOW,scrollPosition & 0xff);
	}
}

