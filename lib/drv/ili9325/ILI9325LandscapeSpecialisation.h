/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012,2013 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

/*
 * Implementation for Adafruit TFT LCD copyright (c) 2013 Colin Irwin, see
 * http://aethersdr.org/ for details. Provided under original terms and
 * conditions.
 *
 */

#pragma once

namespace lcd {

	/**
	 * Specialisation of ILI9325Orientation for the panel in LANDSCAPE mode.
	 * @tparam TAccessMode the access mode implementation, eg XMEM
	 */

	template<class TAccessMode>
	class ILI9325Orientation<LANDSCAPE,TAccessMode> {

		protected:
			uint16_t getMemoryAccessControl() const;

		public:
			int16_t getWidth() const;
			int16_t getHeight() const;
			void moveTo(const Rectangle& rc) const;
			void moveTo(int16_t xstart,int16_t ystart,int16_t xend,int16_t yend) const;
			void moveX(int16_t xstart,int16_t xend) const;
			void moveY(int16_t ystart,int16_t yend) const;
			void setScrollPosition(int16_t scrollPosition);
	};


	/**
	 * Get the register setting for memory access control
	 * @return The entry mode register setting for portrait
	 */

	template<class TAccessMode>
	inline uint16_t ILI9325Orientation<LANDSCAPE,TAccessMode>::getMemoryAccessControl() const {
		return 0x0018;
	}


	/**
	 * Get the width in pixels
	 * @return 320px
	 */

	template<class TAccessMode>
	inline int16_t ILI9325Orientation<LANDSCAPE,TAccessMode>::getWidth() const {
		return 320;
	}


	/**
	 * Get the height in pixels
	 * @return 240px
	 */

	template<class TAccessMode>
	inline int16_t ILI9325Orientation<LANDSCAPE,TAccessMode>::getHeight() const {
		return 240;
	}


	/**
	 * Move the display output rectangle
	 * @param rc The display output rectangle
	 */

	template<class TAccessMode>
	inline void ILI9325Orientation<LANDSCAPE,TAccessMode>::moveTo(const Rectangle& rc) const {
		moveTo(rc.X,rc.Y,rc.X+rc.Width-1,rc.Y+rc.Height-1);
	}


	/**
	 * Move the display rectangle to the rectangle described by the co-ordinates
	 * @param xstart starting X position
	 * @param ystart starting Y position
	 * @param xend ending X position
	 * @param yend ending Y position
	 */

	template<class TAccessMode>
	inline void ILI9325Orientation<LANDSCAPE,TAccessMode>::moveTo(int16_t xstart,int16_t ystart,int16_t xend,int16_t yend) const {

		int16_t start,end;

		TAccessMode::writeCommandData(ili9325::ILI932X_HOR_START_AD,ystart,ystart >> 8);
		TAccessMode::writeCommandData(ili9325::ILI932X_HOR_END_AD,yend,yend >> 8);

		start=319-xend;
		TAccessMode::writeCommandData(ili9325::ILI932X_VER_START_AD,start,start >> 8);

		end=319-xstart;
		TAccessMode::writeCommandData(ili9325::ILI932X_VER_END_AD,end,end >> 8);
		TAccessMode::writeCommandData(ili9325::ILI932X_GRAM_VER_AD,end,end >> 8);

		TAccessMode::writeCommandData(ili9325::ILI932X_GRAM_HOR_AD,ystart,ystart >> 8);
	}


	/**
	 * Move the X position
	 * @param xstart The new X start position
	 * @param xend The new X end position
	 */

	template<class TAccessMode>
	inline void ILI9325Orientation<LANDSCAPE,TAccessMode>::moveX(int16_t xstart,int16_t xend) const {

		int16_t start,end;

		start=319-xend;
		end=319-xstart;

		TAccessMode::writeCommandData(ili9325::ILI932X_VER_START_AD,start,start >> 8);

		TAccessMode::writeCommandData(ili9325::ILI932X_VER_END_AD,end,end >> 8);
		TAccessMode::writeCommandData(ili9325::ILI932X_GRAM_VER_AD,end,end >> 8);
	}


	/**
	 * Move the Y start position
	 * @param ystart The new Y start position
	 */

	template<class TAccessMode>
	inline void ILI9325Orientation<LANDSCAPE,TAccessMode>::moveY(int16_t ystart,int16_t yend) const {

		TAccessMode::writeCommandData(ili9325::ILI932X_HOR_START_AD,ystart,ystart >> 8);
		TAccessMode::writeCommandData(ili9325::ILI932X_GRAM_HOR_AD,ystart,ystart >> 8);
		TAccessMode::writeCommandData(ili9325::ILI932X_HOR_END_AD,yend,yend >> 8);
	}


	/**
	 * Set a vertical scroll position
	 * @param scrollPosition The new scroll position
	 */

	template<class TAccessMode>
	inline void ILI9325Orientation<LANDSCAPE,TAccessMode>::setScrollPosition(int16_t scrollPosition) {

		if(scrollPosition < 0)
			scrollPosition+=320;
		else if(scrollPosition > 319)
			scrollPosition-=320;

		TAccessMode::writeCommandData(ili9325::ILI932X_GATE_SCAN_CTRL3,scrollPosition,scrollPosition >> 8);
	}
}

