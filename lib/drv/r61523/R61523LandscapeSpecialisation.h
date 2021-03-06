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

  template<class TAccessMode>
  class R61523Orientation<LANDSCAPE,TAccessMode> {

    protected:
      void setOrientation() const;

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
   * Set the orientation to landscape
   */

  template<class TAccessMode>
  inline void R61523Orientation<LANDSCAPE,TAccessMode>::setOrientation() const {
    TAccessMode::writeCommand(r61523::SET_ADDRESS_MODE);
    TAccessMode::writeData(0xe0);
  }


  /**
   * Get the width in pixels
   * @return 360px
   */

  template<class TAccessMode>
  inline int16_t R61523Orientation<LANDSCAPE,TAccessMode>::getWidth() const {
    return 640;
  }


  /**
   * Get the height in pixels
   * @return 640px
   */

  template<class TAccessMode>
  inline int16_t R61523Orientation<LANDSCAPE,TAccessMode>::getHeight() const {
    return 360;
  }


  /**
   * Move the display output rectangle
   * @param rc The display output rectangle
   */

  template<class TAccessMode>
  inline void R61523Orientation<LANDSCAPE,TAccessMode>::moveTo(const Rectangle& rc) const {
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
  inline void R61523Orientation<LANDSCAPE,TAccessMode>::moveTo(int16_t xstart,int16_t ystart,int16_t xend,int16_t yend) const {

    TAccessMode::writeCommand(r61523::SET_COLUMN_ADDRESS);
    TAccessMode::writeData(xstart >> 8);
    TAccessMode::writeData(xstart & 0xff);
    TAccessMode::writeData(xend >> 8);
    TAccessMode::writeData(xend & 0xff);

    TAccessMode::writeCommand(r61523::SET_PAGE_ADDRESS);
    TAccessMode::writeData(ystart >> 8);
    TAccessMode::writeData(ystart & 0xff);
    TAccessMode::writeData(yend >> 8);
    TAccessMode::writeData(yend & 0xff);
  }


  /**
   * Move the X position
   * @param xstart The new X start position
   * @param xend The new X end position
   */

  template<class TAccessMode>
  inline void R61523Orientation<LANDSCAPE,TAccessMode>::moveX(int16_t xstart,int16_t xend) const {
    TAccessMode::writeCommand(r61523::SET_COLUMN_ADDRESS);
    TAccessMode::writeData(xstart >> 8);
    TAccessMode::writeData(xstart & 0xff);
    TAccessMode::writeData(xend >> 8);
    TAccessMode::writeData(xend & 0xff);
  }


  /**
   * Move the Y position
   * @param ystart The new Y start position
   * @param yend The new Y end position
   */

  template<class TAccessMode>
  inline void R61523Orientation<LANDSCAPE,TAccessMode>::moveY(int16_t ystart,int16_t yend) const {
    TAccessMode::writeCommand(r61523::SET_PAGE_ADDRESS);
    TAccessMode::writeData(ystart >> 8);
    TAccessMode::writeData(ystart & 0xff);
    TAccessMode::writeData(yend >> 8);
    TAccessMode::writeData(yend & 0xff);
  }


  /**
   * Hardware scrolling is not supported by this controller
   */

  template<class TAccessMode>
  inline void R61523Orientation<LANDSCAPE,TAccessMode>::setScrollPosition(int16_t /* scrollPosition */) const {
  }
}

