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
 * @defgroup GraphicsLibrary
 * @brief Drawing and bitmap output functions.
 *
 * The graphics library provides the interface to the user that allows drawing,
 * text output and bitmap drawing.
 *
 * @file GraphicsLibrary.h
 * @brief The main graphics library header file.
 * @ingroup GraphicsLibrary
 *
 * @mainpage
 *
 * Welcome to the documentation for the xmemtft library. This documentation is automatically
 * generated from comments in the source code by the Doyxgen utility.
 *
 * @section getting_started Getting Started
 *
 * This library started out as a companion to my reverse engineering efforts for the Nokia 6300
 * TFT panel and has evolved over time to support more and more panels, not just from Nokia but
 * from generic interfaces such as the ILI9325, 9327, 9481 and HX8347A.
 *
 * Step-by-step instructions can be found at my website:
 *
 * http://andybrown.me.uk/wk/2012/06/04/nokia-qvga-tft-lcd-for-the-arduino-mega-graphics-library-part-2-of-2/
 *
 * Also see the initial reverse-engineering effort:
 *
 * http://andybrown.me.uk/wk/2012/06/05/nokia-lcd-for-arduino-mega-1/
 *
 * Other articles are available on my website that describe the reverse engineering of the Nokia N82,
 * N93, N95 8Gb and E73.
 *
 * The 16-bit latched interface, the high-performance access modes and examples for the Ilitek and
 * Himax controllers are documented here:
 *
 * http://andybrown.me.uk/wk/2013/06/08/a-generic-16-bit-lcd-adaptor-for-the-arduino
 */

#pragma once


namespace lcd {

  /**
   * Template implementation of a graphics library. This library inherits from the device implementation
   * that provides the methods that the graphics library needs to access the hardware
   * @ingroup GraphicsLibrary
   * @tparam TDevice the underlying device (e.g. an instantiation of the ILI9325 template)
   * @tparam TAccessMode The access mode, (e.g. an instantiation of the Gpio16LatchAccessMode template)
   */

  template<class TDevice,class TAccessMode>
  class GraphicsLibrary : public TDevice {

    public:
      typedef typename TDevice::UnpackedColour UnpackedColour;
      typedef typename TDevice::TColour TColour;

      enum {
        MAX_DOUBLE_FRACTION_DIGITS = 5
      };

    protected:
      UnpackedColour _foreground;
      UnpackedColour _background;

      Point _streamSelectedPoint;                 // need to keep a copy so rvalue points can be used
      const Font *_streamSelectedFont;            // can keep a ptr, user should not delete font while selected

    protected:
      void plot4EllipsePoints(int16_t cx,int16_t cy,int16_t x,int16_t y) const;

      template<typename T>
      static const T& Max(const T& a,const T& b);

      template<typename T>
      static const T& Min(const T& a,const T& b);

      template<typename T>
      static const T Abs(const T a);

    public:
      // colour choices

      void setForeground(TColour cr);
      void setBackground(TColour cr);

      // panel querying

      int16_t getXmax() const;
      int16_t getYmax() const;

      // text output methods - any font

      Size measureString(const FontBase& font,const char *str) const;

      // text output methods - pixel fonts

      Size writeString(const Point& p,const Font& font,const char *str) const;
      void writeCharacter(const Point& p,const Font& font,const FontChar& fc) const;

      // text output methods - LZG fonts

      Size writeString(const Point& p,const LzgFont& font,const char *str) const;
      void writeCharacter(const Point& p,const LzgFont& font,const FontChar& fc) const;

      // text stream operators

      GraphicsLibrary& operator<<(const char *str);
      GraphicsLibrary& operator<<(char c);
      GraphicsLibrary& operator<<(int16_t val);
      GraphicsLibrary& operator<<(int32_t val);
      GraphicsLibrary& operator<<(const DoublePrecision& val);
      GraphicsLibrary& operator<<(double val);
      GraphicsLibrary& operator<<(const Point& p);
      GraphicsLibrary& operator<<(const Font& f);

      static void modp_dtoa(double value,int8_t prec,char *str);

      // drawing primitives

      void clearScreen() const;
      void plotPoint(const Point& p) const;
      void plotPoint(int16_t x,int16_t y) const;
      void drawRectangle(const Rectangle& rc) const;
      void fillRectangle(const Rectangle& rc) const;
      void clearRectangle(const Rectangle& rc) const;
      void gradientFillRectangle(const Rectangle& rc,Direction dir,TColour first,TColour last) const;
      void drawEllipse(const Point& center,const Size& size) const;
      void fillEllipse(const Point& center,const Size& size) const;
      void drawLine(const Point& p1,const Point& p2) const;

      void drawUncompressedBitmap(const Point& p,const Bitmap& bm) const;
      void drawCompressedBitmap(const Point& p,const Bitmap& bm) const;

      void drawJpeg(const Point& p,JpegDataSource& ds) const;
  };
}


/*
 * include the template implementations
 */

#include "gl/Fundamentals.inl"
#include "gl/Primitives.inl"
#include "gl/Ellipse.inl"
#include "gl/Rectangle.inl"
#include "gl/Bitmap.inl"
#include "gl/Text.inl"
#include "gl/LzgText.inl"
