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
	 * Specialisation of ILI9481Orientation for the panel in PORTRAIT mode.
	 * @tparam TAccessMode the access mode implementation, eg Xmem16AccessMode
	 */

	template<class TAccessMode>
	class ILI9481Orientation<PORTRAIT,TAccessMode> {

		protected:
			uint16_t getAddressMode() const;

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
	inline uint16_t ILI9481Orientation<PORTRAIT,TAccessMode>::getAddressMode() const {
		return 1;			// VERTICAL_FLIP
	}


	/**
	 * Get the width in pixels
	 * @return The panel width (i.e. 320)
	 */

	template<class TAccessMode>
	inline int16_t ILI9481Orientation<PORTRAIT,TAccessMode>::getWidth() const {
		return 320;
	}


	/**
	 * Get the height in pixels
	 * @return The panel height (i.e. 480)
	 */

	template<class TAccessMode>
	inline int16_t ILI9481Orientation<PORTRAIT,TAccessMode>::getHeight() const {
		return 480;
	}


	/**
	 * Move the display output rectangle
	 * @param rc The display output rectangle
	 */

	template<class TAccessMode>
	inline void ILI9481Orientation<PORTRAIT,TAccessMode>::moveTo(const Rectangle& rc) const {

		TAccessMode::writeCommand(ili9481::SET_COLUMN_ADDRESS,rc.X >> 8);
		TAccessMode::writeData(rc.X & 0xff);
		TAccessMode::writeData((rc.X+rc.Width-1) >> 8);
		TAccessMode::writeData((rc.X+rc.Width-1) & 0xff);

		TAccessMode::writeCommand(ili9481::SET_PAGE_ADDRESS,rc.Y >> 8);
		TAccessMode::writeData(rc.Y & 0xff);
		TAccessMode::writeData((rc.Y+rc.Height-1) >> 8);
		TAccessMode::writeData((rc.Y+rc.Height-1) & 0xff);
	}


	/**
	 * Set a vertical scroll position
	 * @param scrollPosition The new scroll position
	 */

	template<class TAccessMode>
	inline void ILI9481Orientation<PORTRAIT,TAccessMode>::setScrollPosition(int16_t scrollPosition) const {

		if(scrollPosition<0)
      scrollPosition+=480;
    else if(scrollPosition>479)
      scrollPosition-=480;

    // write to the register

		TAccessMode::writeCommand(ili9481::SET_SCROLL_START);
		TAccessMode::writeData(scrollPosition >> 8) & 1);
		TAccessMode::writeData(scrollPosition & 0xff);
	}
}

