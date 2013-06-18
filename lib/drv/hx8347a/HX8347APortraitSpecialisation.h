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
 * @file HX8347APortraitSpecialisation.h
 * @brief Specialisation of HX8347AOrientation for portrait mode.
 */


#pragma once


namespace lcd {


	/**
	 * @brief Specialisation of HX8347AOrientation for the panel in PORTRAIT mode.
	 * @tparam TAccessMode the access mode implementation, eg Xmem16AccessMode
	 * @ingroup HX8347A
	 */

	template<class TAccessMode>
	class HX8347AOrientation<PORTRAIT,TAccessMode> {

		protected:
			uint16_t getOrientationMemoryAccessCtrl() const;

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
	inline void HX8347AOrientation<PORTRAIT,TAccessMode>::moveTo(int16_t xstart,int16_t ystart,int16_t xend,int16_t yend) const {

		TAccessMode::writeCommandData(hx8347a::COLUMN_ADDRESS_START_HIGH,xstart >> 8);
		TAccessMode::writeCommandData(hx8347a::COLUMN_ADDRESS_START_LOW,xstart & 0xff);
		TAccessMode::writeCommandData(hx8347a::COLUMN_ADDRESS_END_HIGH,xend >> 8);
		TAccessMode::writeCommandData(hx8347a::COLUMN_ADDRESS_END_LOW,xend & 0xff);

		TAccessMode::writeCommandData(hx8347a::ROW_ADDRESS_START_HIGH,ystart >> 8);
		TAccessMode::writeCommandData(hx8347a::ROW_ADDRESS_START_LOW,ystart & 0xff);
		TAccessMode::writeCommandData(hx8347a::ROW_ADDRESS_END_HIGH,yend >> 8);
		TAccessMode::writeCommandData(hx8347a::ROW_ADDRESS_END_LOW,yend & 0xff);
	}


	/**
	 * Move the X position
	 * @param xstart The new X start position
	 * @param xend The new X end position
	 */

	template<class TAccessMode>
	inline void HX8347AOrientation<PORTRAIT,TAccessMode>::moveX(int16_t xstart,int16_t xend) const {

		TAccessMode::writeCommandData(hx8347a::COLUMN_ADDRESS_START_HIGH,xstart >> 8);
		TAccessMode::writeCommandData(hx8347a::COLUMN_ADDRESS_START_LOW,xstart & 0xff);
		TAccessMode::writeCommandData(hx8347a::COLUMN_ADDRESS_END_HIGH,xend >> 8);
		TAccessMode::writeCommandData(hx8347a::COLUMN_ADDRESS_END_LOW,xend & 0xff);
	}


	/**
	 * Move the Y start position
	 * @param ystart The new Y start position
	 */

	template<class TAccessMode>
	inline void HX8347AOrientation<PORTRAIT,TAccessMode>::moveY(int16_t ystart,int16_t yend) const {

		TAccessMode::writeCommandData(hx8347a::ROW_ADDRESS_START_HIGH,ystart >> 8);
		TAccessMode::writeCommandData(hx8347a::ROW_ADDRESS_START_LOW,ystart & 0xff);
		TAccessMode::writeCommandData(hx8347a::ROW_ADDRESS_END_HIGH,yend >> 8);
		TAccessMode::writeCommandData(hx8347a::ROW_ADDRESS_END_LOW,yend & 0xff);
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

