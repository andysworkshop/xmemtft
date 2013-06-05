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
	 * Specialisation of ILI9327Orientation for the panel in LANDSCAPE mode.
	 * @tparam TAccessMode the access mode implementation, e.g. Xmem16AccessMode
	 */

	template<class TAccessMode,class TPanelTraits>
	class ILI9327Orientation<LANDSCAPE,TAccessMode,TPanelTraits> {

		protected:
			uint16_t getOrientationAddressMode() const;

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

	template<class TAccessMode,class TPanelTraits>
	inline uint16_t ILI9327Orientation<LANDSCAPE,TAccessMode,TPanelTraits>::getOrientationAddressMode() const {
		return ili9327::PAGECOL_SELECTION | ili9327::HORIZONTAL_FLIP;
	}


	/**
	 * Get the width in pixels
	 * @return The panel width (e.g. 240)
	 */

	template<class TAccessMode,class TPanelTraits>
	inline int16_t ILI9327Orientation<LANDSCAPE,TAccessMode,TPanelTraits>::getWidth() const {
		return TPanelTraits::LONG_SIDE;
	}


	/**
	 * Get the height in pixels
	 * @return The panel height (e.g. 400)
	 */

	template<class TAccessMode,class TPanelTraits>
	inline int16_t ILI9327Orientation<LANDSCAPE,TAccessMode,TPanelTraits>::getHeight() const {
		return TPanelTraits::SHORT_SIDE;
	}


	/**
	 * Move the display output rectangle
	 * @param rc The display output rectangle
	 */

	template<class TAccessMode,class TPanelTraits>
	inline void ILI9327Orientation<LANDSCAPE,TAccessMode,TPanelTraits>::moveTo(const Rectangle& rc) const {

		uint16_t xoffset;

		// bump past any hidden pixels

		xoffset=432-TPanelTraits::LONG_SIDE;

		TAccessMode::writeCommand(ili9327::SET_COLUMN_ADDRESS);
		TAccessMode::writeData((rc.X+xoffset) >> 8);
		TAccessMode::writeData((rc.X+xoffset) & 0xff);
		TAccessMode::writeData((rc.X+xoffset+rc.Width-1) >>8);
		TAccessMode::writeData((rc.X+xoffset+rc.Width-1) & 0xff);

		TAccessMode::writeCommand(ili9327::SET_PAGE_ADDRESS);
		TAccessMode::writeData(rc.Y >> 8);
		TAccessMode::writeData(rc.Y & 0xff);
		TAccessMode::writeData((rc.Y+rc.Height-1) >>8);
		TAccessMode::writeData((rc.Y+rc.Height-1) & 0xff);
	}


	/**
	 * Set a vertical scroll position
	 * @param scrollPosition The new scroll position
	 */

	template<class TAccessMode,class TPanelTraits>
	inline void ILI9327Orientation<LANDSCAPE,TAccessMode,TPanelTraits>::setScrollPosition(int16_t scrollPosition) const {

		uint16_t yoffset;

		if(scrollPosition<0)
			scrollPosition+=TPanelTraits::LONG_SIDE;
		else if(scrollPosition>TPanelTraits::LONG_SIDE-1)
			scrollPosition-=TPanelTraits::LONG_SIDE;

		yoffset=432-TPanelTraits::LONG_SIDE;

		// write to the register

		TAccessMode::writeCommand(ili9327::SET_SCROLL_START);
		TAccessMode::writeData(((scrollPosition + yoffset) >> 8) & 1);
		TAccessMode::writeData((scrollPosition + yoffset) & 0xff);
	}
}

