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
	 * Implementation of a terminal for LCDs in portrait mode. In this mode hardware
	 * scrolling is supported and will be used when the terminal "goes off the bottom".
	 */

	template<class TGraphicsLibrary>
	class TerminalPortraitImpl : public TerminalBase<TerminalPortraitImpl<TGraphicsLibrary>,TGraphicsLibrary> {

		protected:
			uint8_t _smoothScrollStep;
			int16_t _scrollPosition;

		public:
			enum {
				NO_SMOOTH_SCROLLING = 0,
				DEFAULT_SMOOTH_SCROLL_STEP = 5
			};

		public:
			TerminalPortraitImpl(
					TGraphicsLibrary *gl,
					const Font *font,
					uint8_t smoothScrollStep=DEFAULT_SMOOTH_SCROLL_STEP);

			void reset();
			void scroll();
	};


	/*
	 * Constructor
	 */

	template<class TGraphicsLibrary>
	inline TerminalPortraitImpl<TGraphicsLibrary>::TerminalPortraitImpl(TGraphicsLibrary *gl,
																															 const Font *font,
																															 uint8_t smoothScrollStep)
		: TerminalBase<TerminalPortraitImpl<TGraphicsLibrary>,TGraphicsLibrary>(gl,font),
		  _smoothScrollStep(smoothScrollStep),
		  _scrollPosition(0) {
	}


	/*
	 * Scroll the display by one line
	 */

	template<class TGraphicsLibrary>
	inline void TerminalPortraitImpl<TGraphicsLibrary>::scroll() {

		int i;
		Rectangle rc;
		int16_t screenHeight;

		screenHeight=this->_gl->getHeight();

		rc.Width=this->_gl->getWidth();
		rc.X=0;

		// smooth scroll

		rc.Height=1;

		for(i=0;i<this->_fontSize.Height;i++) {

			_scrollPosition++;

			if(_scrollPosition==screenHeight)
				_scrollPosition=0;

			this->_gl->setScrollPosition(_scrollPosition);

			rc.Y=_scrollPosition-1;
			this->_gl->clearRectangle(rc);

			delay(_smoothScrollStep);
		}

		// don't allow the cursor to run away and overflow

		if(this->_cursor.Y==this->_terminalSize.Height*2)
			this->_cursor.Y=this->_terminalSize.Height;
	}


	/*
	 * Reset after clear
	 */

	template<class TGraphicsLibrary>
	inline void TerminalPortraitImpl<TGraphicsLibrary>::reset() {

		_scrollPosition=0;
		this->_gl->setScrollPosition(0);
	}
}
