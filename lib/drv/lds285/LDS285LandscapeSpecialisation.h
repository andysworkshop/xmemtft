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
 * @file LDS285LandscapeSpecialisation.h
 * @brief Specialisation of LDS285Orientation for landscape mode.
 * @ingroup LDS285
 */

#pragma once


namespace lcd {


  /**
   * Specialisation of LDS285Orientation for the panel in LANDSCAPE mode.
   * @tparam TAccessMode the access mode implementation, e.g. Gpio16LatchAccessMode
   * @ingroup LDS285
   */

  template<class TAccessMode,class TPanelTraits>
  class LDS285Orientation<LANDSCAPE,TAccessMode,TPanelTraits> {

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

  template<class TAccessMode,class TPanelTraits>
  inline uint16_t LDS285Orientation<LANDSCAPE,TAccessMode,TPanelTraits>::getMemoryAccessControl() const {
    return 0xc0;
  }


  /**
   * Get the width in pixels
   * @return 240px
   */

  template<class TAccessMode,class TPanelTraits>
  inline int16_t LDS285Orientation<LANDSCAPE,TAccessMode,TPanelTraits>::getWidth() const {
    return 320;
  }


  /**
   * Get the height in pixels
   * @return 320px
   */

  template<class TAccessMode,class TPanelTraits>
  inline int16_t LDS285Orientation<LANDSCAPE,TAccessMode,TPanelTraits>::getHeight() const {
    return 240;
  }


  /**
   * Move the display output rectangle
   * @param rc The display output rectangle
   */

  template<class TAccessMode,class TPanelTraits>
  inline void LDS285Orientation<LANDSCAPE,TAccessMode,TPanelTraits>::moveTo(const Rectangle& rc) const {
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
  inline void LDS285Orientation<LANDSCAPE,TAccessMode,TPanelTraits>::moveTo(int16_t xstart,int16_t ystart,int16_t xend,int16_t yend) const {

    TAccessMode::writeCommand(lds285::COLUMN_ADDRESS_SET);

    TAccessMode::writeData(xstart >> 8);          // x=0..319
    TAccessMode::writeData(xstart & 0xff);
    TAccessMode::writeData(xend >> 8);
    TAccessMode::writeData(xend & 0xff);

    TAccessMode::writeCommand(lds285::ROW_ADDRESS_SET);

    TAccessMode::writeData(0);                    // y=0..239
    TAccessMode::writeData(ystart);
    TAccessMode::writeData(0);
    TAccessMode::writeData(yend);
  }


  /**
   * Move the X position
   * @param xstart The new X start position
   * @param xend The new X end position
   */

  template<class TAccessMode,class TPanelTraits>
  inline void LDS285Orientation<LANDSCAPE,TAccessMode,TPanelTraits>::moveX(int16_t xstart,int16_t xend) const {

    TAccessMode::writeCommand(lds285::COLUMN_ADDRESS_SET);

    TAccessMode::writeData(xstart >> 8);          // x=0..319
    TAccessMode::writeData(xstart & 0xff);
    TAccessMode::writeData(xend >> 8);
    TAccessMode::writeData(xend & 0xff);
  }


  /**
   * Move the Y start position
   * @param ystart The new Y start position
   */

  template<class TAccessMode,class TPanelTraits>
  inline void LDS285Orientation<LANDSCAPE,TAccessMode,TPanelTraits>::moveY(int16_t ystart,int16_t yend) const {

    TAccessMode::writeCommand(lds285::ROW_ADDRESS_SET);

    TAccessMode::writeData(0);                    // y=0..239
    TAccessMode::writeData(ystart);
    TAccessMode::writeData(0);
    TAccessMode::writeData(yend);
  }


  /**
   * Set a vertical scroll position
   * @param scrollPosition The new scroll position
   */

  template<class TAccessMode,class TPanelTraits>
  inline void LDS285Orientation<LANDSCAPE,TAccessMode,TPanelTraits>::setScrollPosition(int16_t scrollPosition) {

    // pull into range

    if(scrollPosition<0)
      scrollPosition+=320;
    else if(scrollPosition>319)
      scrollPosition-=320;

    // don't ask me why, but when the scroll position is zero either the optimiser breaks the code or
    // there is a panel timing issue that does not occur when the optimiser is disabled (-O0). Inserting
    // this zero delay call fixes it. <sigh>

    if(!scrollPosition)
      delay(0);

    // write to the register

    TAccessMode::writeCommand(lds285::VERTICAL_SCROLLING_START_ADDRESS);
    TAccessMode::writeData(scrollPosition >> 8);
    TAccessMode::writeData(scrollPosition & 0xff);
  }
}

