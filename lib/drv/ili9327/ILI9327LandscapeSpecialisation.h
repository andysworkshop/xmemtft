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
 * @file ILI9327LandscapeSpecialisation.h
 * @brief Specialisation of ILI9327Orientation for landscape mode.
 * @ingroup ILI9327
 */

#pragma once


namespace lcd {


  /**
   * Specialisation of ILI9327Orientation for the panel in LANDSCAPE mode.
   * @tparam TAccessMode the access mode implementation, e.g. Gpio16LatchAccessMode
   * @ingroup ILI9327
   */

  template<class TAccessMode,class TPanelTraits>
  class ILI9327Orientation<LANDSCAPE,TAccessMode,TPanelTraits> {

    protected:
      uint16_t getOrientationAddressMode() const;

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

  template<class TAccessMode,class TPanelTraits>
  inline uint16_t ILI9327Orientation<LANDSCAPE,TAccessMode,TPanelTraits>::getOrientationAddressMode() const {
    return ili9327::PAGECOL_SELECTION | ili9327::HORIZONTAL_FLIP;
  }


  /**
   * Get the width in pixels from the panel traits.
   * @return The panel width (e.g. 240)
   */

  template<class TAccessMode,class TPanelTraits>
  inline int16_t ILI9327Orientation<LANDSCAPE,TAccessMode,TPanelTraits>::getWidth() const {
    return TPanelTraits::LONG_SIDE;
  }


  /**
   * Get the height in pixels from the panel traits.
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
    moveTo(rc.X,rc.Y,rc.X+rc.Width-1,rc.Y+rc.Height-1);
  }


  /**
   * Move the display output rectangle
   * @param xstart left-most x co-ordinate
   * @param ystart top-most y co-ordinate
   * @param xend right-most x co-ordinate
   * @param yend bottom-most y co-ordinate
   */

  template<class TAccessMode,class TPanelTraits>
  inline void ILI9327Orientation<LANDSCAPE,TAccessMode,TPanelTraits>::moveTo(int16_t xstart,int16_t ystart,int16_t xend,int16_t yend) const {

    uint16_t xoffset;

    // bump past any hidden pixels

    xoffset=432-TPanelTraits::LONG_SIDE;

    TAccessMode::writeCommand(ili9327::SET_COLUMN_ADDRESS);
    TAccessMode::writeData((xstart+xoffset) >> 8);
    TAccessMode::writeData((xstart+xoffset) & 0xff);
    TAccessMode::writeData((xend+xoffset) >>8);
    TAccessMode::writeData((xend+xoffset) & 0xff);

    TAccessMode::writeCommand(ili9327::SET_PAGE_ADDRESS);
    TAccessMode::writeData(ystart >> 8);
    TAccessMode::writeData(ystart & 0xff);
    TAccessMode::writeData(yend >>8);
    TAccessMode::writeData(yend & 0xff);
  }


  /**
   * Move the X position
   * @param xstart The new X start position
   * @param xend The new X end position
   */

  template<class TAccessMode,class TPanelTraits>
  inline void ILI9327Orientation<LANDSCAPE,TAccessMode,TPanelTraits>::moveX(int16_t xstart,int16_t xend) const {

    uint16_t xoffset;

    // bump past any hidden pixels

    xoffset=432-TPanelTraits::LONG_SIDE;

    TAccessMode::writeCommand(ili9327::SET_COLUMN_ADDRESS);
    TAccessMode::writeData((xstart+xoffset) >> 8);
    TAccessMode::writeData((xstart+xoffset) & 0xff);
    TAccessMode::writeData((xend+xoffset) >>8);
    TAccessMode::writeData((xend+xoffset) & 0xff);
  }


  /**
   * Move the Y position
   * @param ystart The new Y position
   */

  template<class TAccessMode,class TPanelTraits>
  inline void ILI9327Orientation<LANDSCAPE,TAccessMode,TPanelTraits>::moveY(int16_t ystart,int16_t yend) const {

    TAccessMode::writeCommand(ili9327::SET_PAGE_ADDRESS);
    TAccessMode::writeData(ystart >> 8);
    TAccessMode::writeData(ystart & 0xff);
    TAccessMode::writeData(yend >>8);
    TAccessMode::writeData(yend & 0xff);
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

