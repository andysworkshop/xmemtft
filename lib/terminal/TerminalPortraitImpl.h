/*
  XMEM LCD Library for the Arduino

  Copyright 2012,2013 Andrew Brown

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This notice may not be removed or altered from any source distribution.
*/

/**
 * @file TerminalPortraitImpl.h
 * @brief Functionality for portrait orienatation terminals.
 * @ingroup Terminal
 */

#pragma once

#include "terminal/TerminalBase.h"


namespace lcd {


  /**
   * @brief Implementation of a terminal for LCDs in portrait mode.
   *
   * In this mode hardware
   * scrolling is supported and will be used when the terminal "goes off the bottom".
   *
   * @tparam TGraphicsLibrary. The graphics library implementation.
   * @ingroup Terminal
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


  /**
   * @brief Constructor. You probably want to call clearScreen before you get going.
   * @param gl A pointer to the graphics library implementation.
   * @param font A pointer to the fixed-width font to use.
   * @param smoothScrollStep The number of milliseconds to wait between scrolling lines to give the impression of
   * smoothness. The default is 5.
   */

  template<class TGraphicsLibrary>
  inline TerminalPortraitImpl<TGraphicsLibrary>::TerminalPortraitImpl(TGraphicsLibrary *gl,
                                                               const Font *font,
                                                               uint8_t smoothScrollStep)
    : TerminalBase<TerminalPortraitImpl<TGraphicsLibrary>,TGraphicsLibrary>(gl,font),
      _smoothScrollStep(smoothScrollStep),
      _scrollPosition(0) {
  }


  /**
   * Scroll the display by one line (required by TerminalBase).
   * This implementation does smooth scrolling using the hardware.
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


  /**
   * Reset after clear (required by TerminalBase).
   * The scroll position is reset to zero.
   */

  template<class TGraphicsLibrary>
  inline void TerminalPortraitImpl<TGraphicsLibrary>::reset() {

    _scrollPosition=0;
    this->_gl->setScrollPosition(0);
  }
}
