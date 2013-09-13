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
 * @file Text.inl
 * @brief Text output functions.
 *
 * Fonts are created by using the FontConv utility to export bitmap fonts (that part is important, they must be
 * bitmap fonts) from a TrueType font file. A good source of these files is http://www.dafont.com. The functionality
 * provided in this file allows you to write these characters out to the display in a foreground colour and filled
 * with a background colour. The fonts may be proportional width. The fonts must be compiled into the lower 64Kb of
 * flash memory because we use pgm_read_byte() to access them.
 *
 * @ingroup GraphicsLibrary
 */

#pragma once


namespace lcd {

  /**
   * Write a null terminated string of characters to the display. Characters are written in the foreground colour
   * and blank spaces are filled using the background colour. Additional spacing between characters is not filled.
   * @param p The upper-left point to write out at.
   * @param font The font structure reference created by FontConv and compiled in by you.
   * @param str The character string to write out.
   * @return the bounding size of the string in pixels.
   */

  template<class TDevice,class TAccessMode>
  inline Size GraphicsLibrary<TDevice,TAccessMode>::writeString(const Point& p,const Font& font,const char *str) const {

    const char *ptr;
    Point pos(p);
    FontChar fc;
    int16_t width;
    Size s;

    s.Height=font.getHeight();
    s.Width=0;

    // print each character in turn

    for(ptr=str;*ptr;ptr++) {

      font.getCharacter(*ptr,fc);
      writeCharacter(pos,font,fc);

      width=fc.PixelWidth+font.getCharacterSpacing();
      pos.X+=width;
      s.Width+=width;
    }

    return s;
  }


  /**
   * Write a single character from a bitmap font
   * @param p The upper-left point to write out at.
   * @param font The font structure reference created by FontConv and compiled in by you.
   * @param fc The FontChar structure defining the character. You can use Font.getCharacter() to get this.
   */

  template<class TDevice,class TAccessMode>
  inline void GraphicsLibrary<TDevice,TAccessMode>::writeCharacter(const Point& p,const Font& font,const FontChar& fc) const {

    const uint8_t *ptr;
    uint8_t value,i,x,y;

    // move to the rectangle that encloses the character

    this->moveTo(
      Rectangle(
          p.X,
          p.Y,
          fc.PixelWidth,
          font.getHeight()
      )
    );

    // get the first value

    ptr=fc.Data;
    value=pgm_read_byte(ptr);
    ptr++;
    i=1;

    // go from top to bottom, left to right

    this->beginWriting();

    for(y=0;y<font.getHeight();y++) {

      for(x=0;x<fc.PixelWidth;x++) {

        // if there's a value at this position, write a pixel

        if((value & i)!=0)
          this->writePixel(_foreground);
        else
          this->writePixel(_background);

        // move to the next bit, or the next byte if we've run out of bits

        if(i==0x80) {
          i=1;
          value=pgm_read_byte(ptr);
          ptr++;
        }
        else
          i<<=1;
      }
    }
  }


  /**
   * Measure the rectangle required to display the given null terminated string.
   * @param The font to measure from. This is compatible with LZG and bitmap fonts.
   * @param str The string to measure.
   * @return The size in pixels of the bounding rectangle.
   */

  template<class TDevice,class TAccessMode>
  inline Size GraphicsLibrary<TDevice,TAccessMode>::measureString(const FontBase& font,const char *str) const {

    Size size;
    uint8_t c;
    FontChar fc;

    size.Height=font.getHeight();
    size.Width=0;

    while((c=*str++) != 0) {
      font.getCharacter(c,fc);
      size.Width+=fc.PixelWidth+font.getCharacterSpacing();
    }

    return size;
  }


  /**
   * Output a string using a stream operator using the currently selected font.
   * @param str The string to write out.
   * @return a self reference to allow chaining of << operators.
   */

  template<class TDevice,class TAccessMode>
  inline GraphicsLibrary<TDevice,TAccessMode>& GraphicsLibrary<TDevice,TAccessMode>::operator<<(const char *str) {

    _streamSelectedPoint.X+=writeString(_streamSelectedPoint,*_streamSelectedFont,str).Width;
    return *this;
  }


  /**
   * Output a character using a stream operator using the currently selected font.
   * @param c The character to write out.
   * @return a self reference to allow chaining of << operators.
   */

  template<class TDevice,class TAccessMode>
  inline GraphicsLibrary<TDevice,TAccessMode>& GraphicsLibrary<TDevice,TAccessMode>::operator<<(char c) {

    FontChar fc;

    _streamSelectedFont->getCharacter(c,fc);
    writeCharacter(_streamSelectedPoint,*_streamSelectedFont,fc);
    _streamSelectedPoint.X+=fc.PixelWidth+_streamSelectedFont->getCharacterSpacing();

    return *this;
  }


  /**
   * Output a 16-bit signed integer using a stream operator using the currently selected font.
   * @param val the value to write out.
   * @return a self reference to allow chaining of << operators.
   */

  template<class TDevice,class TAccessMode>
  inline GraphicsLibrary<TDevice,TAccessMode>& GraphicsLibrary<TDevice,TAccessMode>::operator<<(int16_t val) {

    char buf[10];
    itoa(val,buf,10);
    _streamSelectedPoint.X+=writeString(_streamSelectedPoint,*_streamSelectedFont,buf).Width;

    return *this;
  }


  /**
   * Output a 32-bit signed integer using a stream operator using the currently selected font.
   * @param val the value to write out.
   * @return a self reference to allow chaining of << operators.
   */

  template<class TDevice,class TAccessMode>
  inline GraphicsLibrary<TDevice,TAccessMode>& GraphicsLibrary<TDevice,TAccessMode>::operator<<(int32_t val) {

    char buf[15];
    ltoa(val,buf,10);
    _streamSelectedPoint.X+=writeString(_streamSelectedPoint,*_streamSelectedFont,buf).Width;

    return *this;
  }


  /**
   * Move the current output position to this point.
   * @param p The output position.
   * @return a self reference to allow chaining of << operators.
   */

  template<class TDevice,class TAccessMode>
  inline GraphicsLibrary<TDevice,TAccessMode>& GraphicsLibrary<TDevice,TAccessMode>::operator<<(const Point& p) {
    _streamSelectedPoint=p;
    return *this;
  }


  /**
   * Change the curently selected font to this font.
   * @param f The font to set as the current font.
   * @return a self reference to allow chaining of << operators.
   */

  template<class TDevice,class TAccessMode>
  inline GraphicsLibrary<TDevice,TAccessMode>& GraphicsLibrary<TDevice,TAccessMode>::operator<<(const Font& f) {
    _streamSelectedFont=&f;
    return *this;
  }


  /**
   * Output a double-precision number using the maximum number of fractional digits available. The maximum
   * number of fractional digits is 5 which is in line with the limits of the 32-bit floating point numbers
   * provided by avr-gcc.
   * @param val the value to write out.
   * @return a self reference to allow chaining of << operators.
   */

  template<class TDevice,class TAccessMode>
  GraphicsLibrary<TDevice,TAccessMode>& GraphicsLibrary<TDevice,TAccessMode>::operator<<(double val) {
    operator<<(DoublePrecision(val,MAX_DOUBLE_FRACTION_DIGITS));
    return *this;
  }


  /**
   * Output a double-precision number using a structure that defines the number and the number of fractional
   * digits that you want to write (up to 5).
   * @param val the value to write out.
   * @return a self reference to allow chaining of << operators.
   */

  template<class TDevice,class TAccessMode>
  inline GraphicsLibrary<TDevice,TAccessMode>& GraphicsLibrary<TDevice,TAccessMode>::operator<<(const DoublePrecision& val) {

    char str[25];

    modp_dtoa(val.Value,val.Precision,str);
    _streamSelectedPoint.X+=writeString(_streamSelectedPoint,*_streamSelectedFont,str).Width;
    return *this;
  }


  /**
   * Derived from http://code.google.com/p/stringencoders/source/browse/trunk/src/modp_numtoa.c
   * "string encoders: A collection of high performance c-string transformations". This converts
   * double precision to ascii using a higher performance algorithm than the naiive implementation
   * included with the Arduino libraries.
   *
   * The following license applies:
   *
   * MODP_B64 - High performance base64 encoder/decoder
   * http://code.google.com/p/stringencoders/
   *
   * Copyright (c) 2005, 2006, 2007  Nick Galbreath -- nickg [at] modp [dot] com
   * All rights reserved.
   *
   * Redistribution and use in source and binary forms, with or without
   * modification, are permitted provided that the following conditions are
   * met:
   *
   *   Redistributions of source code must retain the above copyright
   *   notice, this list of conditions and the following disclaimer.
   *
   *   Redistributions in binary form must reproduce the above copyright
   *   notice, this list of conditions and the following disclaimer in the
   *   documentation and/or other materials provided with the distribution.
   *
   *   Neither the name of the modp.com nor the names of its
   *   contributors may be used to endorse or promote products derived from
   *   this software without specific prior written permission.
   *
   * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
   * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
   * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
   * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
   * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
   * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
   *
   * This is the standard "new" BSD license:
   * http://www.opensource.org/licenses/bsd-license.php
   *
   * @param value The value to write out.
   * @param prec The number of fractional digits.
   * @param[out] str Where to write out the value - must be large enough to hold it.
   */

  template<class TDevice,class TAccessMode>
  inline void GraphicsLibrary<TDevice,TAccessMode>::modp_dtoa(double value,int8_t prec,char *str) {

    static const double pow10[] = { 1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000 };

    if(!(value==value)) {

      str[0]='n';
      str[1]='a';
      str[2]='n';
      str[3]='\0';
      return;
    }

    int8_t count;
    double diff=0.0;
    char *wstr=str;

    // we'll work in positive values and deal with the negative sign issue later

    bool neg=false;

    if(value<0) {
      neg=true;
      value=-value;
    }

    uint32_t whole=(uint32_t)value;
    double tmp=(value-whole)*pow10[prec];
    uint32_t frac=(uint32_t)(tmp);

    diff=tmp-frac;

    if(diff>0.5) {

      ++frac;

      // handle rollover, e.g.  case 0.99 with prec 1 is 1.0

      if(frac>=pow10[prec]) {
        frac=0;
        ++whole;
      }

    } else if(diff==0.5 && ((frac==0) || (frac & 1))) {

      // if halfway, round up if odd, OR if last digit is 0.  That last part is strange

      ++frac;
    }

    if(prec==0) {

      diff=value-whole;

      if(diff>0.5) {
      // greater than 0.5, round up, e.g. 1.6 -> 2

        ++whole;

      } else if(diff==0.5 && (whole & 1)) {

        // exactly 0.5 and ODD, then round up
        // 1.5 -> 2, but 2.5 -> 2 */

        ++whole;
      }

    } else if(frac) {

      count=prec;

      // now do fractional part, as an unsigned number
      // we know it is not 0 but we can have leading zeros, these should be removed

      while(!(frac % 10)) {
        --count;
        frac/=10;
      }

      // now do fractional part, as an unsigned number

      do {
        --count;
        *wstr++=(char)(48 + (frac % 10));
      } while(frac/=10);

      // add extra 0s

      while(count-- > 0)
        *wstr++='0';

      // add decimal

      *wstr++='.';
    }

    // do whole part. Take care of sign conversion. Number is reversed.

    do {
      *wstr++=(char)(48 + (whole % 10));
    } while(whole/=10);

    if(neg)
      *wstr++='-';

    *wstr='\0';

    // andy's mod: reverse the string in place

    wstr--;

    while(str<wstr) {

      *str^=*wstr;
      *wstr^=*str;
      *str^=*wstr;

      wstr--;
      str++;
    }
  }
}
