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
