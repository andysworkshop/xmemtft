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
 * @file HX8347ALandscapeSpecialisation.h
 * @brief Specialisation of HX8347AOrientation for landscape mode.
 * @ingroup HX8347A
 */


#pragma once


namespace lcd {


  /**
   * @brief Specialisation of HX8347AOrientation for the panel in LANDSCAPE mode.
   * @tparam TAccessMode the access mode implementation, e.g. Gpio16LatchAccessMode
   * @ingroup HX8347A
   */

  template<class TAccessMode>
  class HX8347AOrientation<LANDSCAPE,TAccessMode> {

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
   * @return The entry mode register setting for landscape
   */

  template<class TAccessMode>
  inline uint16_t HX8347AOrientation<LANDSCAPE,TAccessMode>::getOrientationMemoryAccessCtrl() const {
    return (1 << 5);
  }


  /**
   * Get the width in pixels
   * @return 320px
   */

  template<class TAccessMode>
  inline int16_t HX8347AOrientation<LANDSCAPE,TAccessMode>::getWidth() const {
    return 320;
  }


  /**
   * Get the height in pixels
   * @return 240px
   */

  template<class TAccessMode>
  inline int16_t HX8347AOrientation<LANDSCAPE,TAccessMode>::getHeight() const {
    return 240;
  }


  /**
   * Move the display output rectangle
   * @param rc The display output rectangle
   */

  template<class TAccessMode>
  inline void HX8347AOrientation<LANDSCAPE,TAccessMode>::moveTo(const Rectangle& rc) const {
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
  inline void HX8347AOrientation<LANDSCAPE,TAccessMode>::moveTo(int16_t xstart,int16_t ystart,int16_t xend,int16_t yend) const {

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
  inline void HX8347AOrientation<LANDSCAPE,TAccessMode>::moveX(int16_t xstart,int16_t xend) const {
    TAccessMode::writeCommandData(hx8347a::COLUMN_ADDRESS_START_HIGH,xstart >> 8);
    TAccessMode::writeCommandData(hx8347a::COLUMN_ADDRESS_START_LOW,xstart & 0xff);
    TAccessMode::writeCommandData(hx8347a::COLUMN_ADDRESS_END_HIGH,xend >> 8);
    TAccessMode::writeCommandData(hx8347a::COLUMN_ADDRESS_END_LOW,xend & 0xff);
  }


  /**
   * Move the Y start position
   * @param ystart The new Y start position
   * @param yend The new Y end position
   */

  template<class TAccessMode>
  inline void HX8347AOrientation<LANDSCAPE,TAccessMode>::moveY(int16_t ystart,int16_t yend) const {
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
  inline void HX8347AOrientation<LANDSCAPE,TAccessMode>::setScrollPosition(int16_t scrollPosition) const {

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

