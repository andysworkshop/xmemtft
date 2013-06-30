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
 * @file TerminalLandscapeImpl.h
 * @brief Functionality for landscape orienatation terminals.
 * @ingroup Terminal
 */

#pragma once

#include "terminal/TerminalBase.h"


namespace lcd {


	/**
	 * @brief Implementation of a terminal for LCDs in landscape mode.
	 *
	 * In this mode hardware
	 * scrolling is not supported and the terminal will clear down and go back to the
	 * top when the bottom is reached.
	 *
	 * @tparam TGraphicsLibrary. The graphics library implementation.
	 * @ingroup Terminal
	 */

	template<class TGraphicsLibrary>
	class TerminalLandscapeImpl : public TerminalBase<TerminalLandscapeImpl<TGraphicsLibrary>,TGraphicsLibrary> {

		public:
			TerminalLandscapeImpl(
					TGraphicsLibrary *gl,
					const Font *font
					);

			void reset();
			void scroll();
	};


	/**
	 * @brief Constructor. You probably want to call clearScreen before you get going.
	 * @param gl A pointer to the graphics library implementation.
	 * @param font A pointer to the fixed-width font to use.
	 */

	template<class TGraphicsLibrary>
	inline TerminalLandscapeImpl<TGraphicsLibrary>::TerminalLandscapeImpl(
					TGraphicsLibrary *gl,
					const Font *font)
		: TerminalBase<TerminalLandscapeImpl<TGraphicsLibrary>,TGraphicsLibrary>(gl,font) {
	}


	/**
	 * Scroll the display by one line (required by TerminalBase).
	 * This implementation just clears the screen.
	 */

	template<class TGraphicsLibrary>
	inline void TerminalLandscapeImpl<TGraphicsLibrary>::scroll() {
	  this->clearScreen();
	}


	/**
	 * Reset after clear (required by TerminalBase).
	 * This does nothing.
	 */

	template<class TGraphicsLibrary>
	inline void TerminalLandscapeImpl<TGraphicsLibrary>::reset() {
		// no addition requirements
	}
}
