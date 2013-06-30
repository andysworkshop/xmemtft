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
 * @file ILI9481LandscapeSpecialisation.h
 * @brief Specialisation of ILI9481Orientation for landscape mode.
 * @ingroup ILI9481
 */


#pragma once


namespace lcd {


	/**
	 * Specialisation of ILI9481Orientation for the panel in LANDSCAPE mode.
	 * @tparam TAccessMode the access mode implementation, e.g. Xmem16AccessMode
	 * @ingroup ILI9481
	 */

	template<class TAccessMode>
	class ILI9481Orientation<LANDSCAPE,TAccessMode> {

		protected:
			uint16_t getAddressMode() const;

		public:
			int16_t getWidth() const;
			int16_t getHeight() const;
			void moveTo(const Rectangle& rc) const;
			void moveTo(int16_t xstart,int16_t ystart,int16_t xend,int16_t yend) const;
			void moveX(int16_t xstart,int16_t xend) const;
			void moveY(int16_t ystart,int16_t yend) const;

			void setScrollPosition(int16_t scrollPosition) const;
	};


	/**
	 * Get the register setting for memory access control
	 * @return The entry mode register setting for portrait
	 */

	template<class TAccessMode>
	inline uint16_t ILI9481Orientation<LANDSCAPE,TAccessMode>::getAddressMode() const {
		return ili9481::PAGECOL_SELECTION;
	}


	/**
	 * Get the width in pixels
	 * @return The panel width (i.e. 480)
	 */

	template<class TAccessMode>
	inline int16_t ILI9481Orientation<LANDSCAPE,TAccessMode>::getWidth() const {
		return 480;
	}


	/**
	 * Get the height in pixels
	 * @return The panel height (i.e. 320)
	 */

	template<class TAccessMode>
	inline int16_t ILI9481Orientation<LANDSCAPE,TAccessMode>::getHeight() const {
		return 320;
	}


	/**
	 * Move the display output rectangle
	 * @param rc The display output rectangle
	 */

	template<class TAccessMode>
	inline void ILI9481Orientation<LANDSCAPE,TAccessMode>::moveTo(const Rectangle& rc) const {
		moveTo(rc.X,rc.Y,rc.X+rc.Width-1,rc.Y+rc.Height-1);
	}


	/**
	 * Move the display output rectangle
	 * @param xstart left-most x co-ordinate
	 * @param ystart top-most y co-ordinate
	 * @param xend right-most x co-ordinate
	 * @param yend bottom-most y co-ordinate
	 */

	template<class TAccessMode>
	inline void ILI9481Orientation<LANDSCAPE,TAccessMode>::moveTo(int16_t xstart,int16_t ystart,int16_t xend,int16_t yend) const {

		TAccessMode::writeCommand(ili9481::SET_COLUMN_ADDRESS);
		TAccessMode::writeData(xstart >> 8);
		TAccessMode::writeData(xstart & 0xff);
		TAccessMode::writeData(xend >> 8);
		TAccessMode::writeData(xend & 0xff);

		TAccessMode::writeCommand(ili9481::SET_PAGE_ADDRESS);
		TAccessMode::writeData(ystart >> 8);
		TAccessMode::writeData(ystart & 0xff);
		TAccessMode::writeData(yend >> 8);
		TAccessMode::writeData(yend & 0xff);
	}


	/**
	 * Move the X position
	 * @param xstart The new X start position
	 * @param xend The new X end position
	 */

	template<class TAccessMode>
	inline void ILI9481Orientation<LANDSCAPE,TAccessMode>::moveX(int16_t xstart,int16_t xend) const {

		TAccessMode::writeCommand(ili9481::SET_COLUMN_ADDRESS);
		TAccessMode::writeData(xstart >> 8);
		TAccessMode::writeData(xstart & 0xff);
		TAccessMode::writeData(xend >> 8);
		TAccessMode::writeData(xend & 0xff);
	}


	/**
	 * Move the Y start position
	 * @param ystart The new Y start position
	 */

	template<class TAccessMode>
	inline void ILI9481Orientation<LANDSCAPE,TAccessMode>::moveY(int16_t ystart,int16_t yend) const {

		TAccessMode::writeCommand(ili9481::SET_PAGE_ADDRESS);
		TAccessMode::writeData(ystart >> 8);
		TAccessMode::writeData(ystart & 0xff);
		TAccessMode::writeData(yend >> 8);
		TAccessMode::writeData(yend & 0xff);
	}


	/**
	 * Set a vertical scroll position
	 * @param scrollPosition The new scroll position
	 */

	template<class TAccessMode>
	inline void ILI9481Orientation<LANDSCAPE,TAccessMode>::setScrollPosition(int16_t scrollPosition) const {

		if(scrollPosition<0)
      scrollPosition+=480;
    else if(scrollPosition>479)
      scrollPosition-=480;

    // write to the register

		TAccessMode::writeCommand(ili9481::SET_SCROLL_START);
		TAccessMode::writeData((scrollPosition >> 8) & 1);
		TAccessMode::writeData(scrollPosition & 0xff);
	}
}

