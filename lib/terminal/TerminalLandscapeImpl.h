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

#include "terminal/TerminalBase.h"


namespace lcd {


	/*
	 * Implementation of a terminal for LCDs in landscape mode. In this mode hardware
	 * scrolling is not supported and the terminal will clear down and go back to the
	 * top when the bottom is reached.
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


	/*
	 * Constructor
	 */

	template<class TGraphicsLibrary>
	inline TerminalLandscapeImpl<TGraphicsLibrary>::TerminalLandscapeImpl(
					TGraphicsLibrary *gl,
					const Font *font)
		: TerminalBase<TerminalLandscapeImpl<TGraphicsLibrary>,TGraphicsLibrary>(gl,font) {
	}


	/*
	 * Scroll the display by one line
	 */

	template<class TGraphicsLibrary>
	inline void TerminalLandscapeImpl<TGraphicsLibrary>::scroll() {
	  this->clearScreen();
	}


	/*
	 * Reset after clear
	 */

	template<class TGraphicsLibrary>
	inline void TerminalLandscapeImpl<TGraphicsLibrary>::reset() {
		// no addition requirements
	}
}
