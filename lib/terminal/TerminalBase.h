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
 * @defgroup Terminal
 * @brief Terminal emulation functionality.
 *
 * The terminal emulation functionality allows you to use the panel as a left to right, top to bottom
 * text-output terminal using a fixed font for output. If the panel supports hardware scrolling in the
 * direction appropriate for your chosen panel orientation then it is utilised to provide smooth scrolling
 * when the text reaches the bottom of the terminal.
 */

/**
 * @file TerminalBase.h
 * @brief Common functionality for portrait and landscape orienatation terminals.
 * @ingroup Terminal
 */

#pragma once


namespace lcd {

  /**
   * @brief Base class to manage the display as a character terminal.
   *
   * Derivations for both landscape and portrait mode are supplied. Hardware scrolling is supported
   * in portrait mode. In landscape mode the terminal will clear and restart at the top when the end is reached.
   * The font must be fixed width or wierd stuff will happen. Each controller implementation contains appropriate
   * typedefs for terminal implementations in landscape and portrait.
   *
   * @tparam TImpl This a CRTP-style class. TImpl is the type of the derived class.
   * @tparam TGraphicsLibrary. The graphics library implementation.
   * @ingroup Terminal
   */

  template<class TImpl,class TGraphicsLibrary>
  class TerminalBase {

    protected:
      TGraphicsLibrary *_gl;
      const Font *_font;

      Size _terminalSize;
      Size _fontSize;
      Point _cursor;

    protected:
      void calcTerminalSize();
      void incrementY();

    public:
      TerminalBase(
          TGraphicsLibrary *gl,
          const Font *font);

      void writeCharacter(char c);
      void writeString(const char *str);

      TerminalBase& operator<<(const char *str);
      TerminalBase& operator<<(char c);
      TerminalBase& operator<<(int16_t val);
      TerminalBase& operator<<(int32_t val);
      TerminalBase& operator<<(const DoublePrecision& val);
      TerminalBase& operator<<(double val);

      void clearScreen();
      void clearLine();
  };


  /**
   * @brief Constructor. You probably want to call clearScreen before you get going.
   * @param gl A pointer to the graphics library implementation.
   * @param font A pointer to the fixed-width font to use.
   */

  template<class TImpl,class TGraphicsLibrary>
  inline TerminalBase<TImpl,TGraphicsLibrary>::TerminalBase(
      TGraphicsLibrary *gl,
      const Font *font)
    : _gl(gl),
      _font(font) {

    calcTerminalSize();
  }


  /**
   * @brief Calculate the terminal size, in characters.
   */

  template<class TImpl,class TGraphicsLibrary>
  inline void TerminalBase<TImpl,TGraphicsLibrary>::calcTerminalSize() {

    FontChar fc;

    // need to know the width of the characters. They're all the same so measure a space.

    _font->getCharacter(' ',fc);

    _fontSize.Height=_font->getHeight();
    _fontSize.Width=fc.PixelWidth;

    // height is rounded down if the fixed lines don't sum to a multiple of the font height

    _terminalSize.Width=_gl->getWidth()/fc.PixelWidth;
    _terminalSize.Height=(_gl->getHeight())/_font->getHeight();
  }


  /**
   * @brief Clear the screen and reset to (0,0)
   */

  template<class TImpl,class TGraphicsLibrary>
  inline void TerminalBase<TImpl,TGraphicsLibrary>::clearScreen() {

    this->_cursor.X=0;
    this->_cursor.Y=0;

    // allow the derivation to reset any parameters

    static_cast<TImpl *>(this)->reset();

    // clear the rectangle between the fixed areas

    _gl->clearRectangle(
        Rectangle(0,
                  0,
                  _gl->getWidth(),
                  _gl->getHeight()
                 )
               );
  }


  /**
   * @brief Clear just the current line and reset X to zero.
   */

  template<class TImpl,class TGraphicsLibrary>
  inline void TerminalBase<TImpl,TGraphicsLibrary>::clearLine() {

    Rectangle rc;

    rc.X=0;
    rc.Y=(_cursor.Y % _terminalSize.Height)*_fontSize.Height;
    rc.Height=_fontSize.Height;
    rc.Width=_terminalSize.Width*_fontSize.Width;

    _gl->clearRectangle(rc);

    _cursor.X=0;
  }


  /**
   * @brief Write a line to the display
   * @param str The string to write.
   */

  template<class TImpl,class TGraphicsLibrary>
  inline void TerminalBase<TImpl,TGraphicsLibrary>::writeString(const char *str) {

    const char *ptr;

    for(ptr=str;*ptr;writeCharacter(*ptr++));
  }


  /**
   * @brief Write a character to the display
   * @param c The character to write.
   */

  template<class TImpl,class TGraphicsLibrary>
  inline void TerminalBase<TImpl,TGraphicsLibrary>::writeCharacter(char c) {

    char buffer[2];
    Point p;

    if(c == '\n') {
      incrementY();
      _cursor.X=0;
    } else if(c=='\r') {
      _cursor.X=0;
    } else {

      // scale up the x,y character co-ords to pixel co-ords

      p.X=_cursor.X*_fontSize.Width;
      p.Y=(_cursor.Y % _terminalSize.Height)*_fontSize.Height;

      // create a string

      buffer[0]=c;
      buffer[1]='\0';

      // move the cursor and write

      _gl->writeString(p,*_font,buffer);

      if(++_cursor.X >= _terminalSize.Width) {
        _cursor.X=0;
        incrementY();
      }
    }
  }


  /**
   * @brief Increment the row and scroll if we have hit the bottom.
   *
   * If the LCD implementation supports
   * hardware scrolling then we will use it, otherwise we just clear the display and start again
   * at the top left.
   */

  template<class TImpl,class TGraphicsLibrary>
  inline void TerminalBase<TImpl,TGraphicsLibrary>::incrementY() {

    _cursor.Y++;

    if(_cursor.Y>=_terminalSize.Height)
      static_cast<TImpl *>(this)->scroll();
  }


  /**
   * @brief Write a string using the stream operator
   * @param str The string to write
   * @return a self reference to allow chaining of << operators.
   */

  template<class TImpl,class TGraphicsLibrary>
  inline TerminalBase<TImpl,TGraphicsLibrary>& TerminalBase<TImpl,TGraphicsLibrary>::operator<<(const char *str) {

    writeString(str);
    return *this;
  }


  /**
   * Output a character using a stream operator.
   * @param c The character to write out.
   * @return a self reference to allow chaining of << operators.
   */

  template<class TImpl,class TGraphicsLibrary>
  inline TerminalBase<TImpl,TGraphicsLibrary>& TerminalBase<TImpl,TGraphicsLibrary>::operator<<(char c) {

    writeCharacter(c);
    return *this;
  }


  /**
   * Output a 16-bit signed integer using a stream operator.
   * @param val the value to write out.
   * @return a self reference to allow chaining of << operators.
   */

  template<class TImpl,class TGraphicsLibrary>
  inline TerminalBase<TImpl,TGraphicsLibrary>& TerminalBase<TImpl,TGraphicsLibrary>::operator<<(int16_t val) {

    char buf[10];
    itoa(val,buf,10);
    writeString(buf);

    return *this;
  }


  /**
   * Output a 32-bit signed integer using a stream operator.
   * @param val the value to write out.
   * @return a self reference to allow chaining of << operators.
   */

  template<class TImpl,class TGraphicsLibrary>
  inline TerminalBase<TImpl,TGraphicsLibrary>& TerminalBase<TImpl,TGraphicsLibrary>::operator<<(int32_t val) {

    char buf[15];
    ltoa(val,buf,10);
    writeString(buf);

    return *this;
  }


  /**
   * Output a double-precision number using the maximum number of fractional digits available. The maximum
   * number of fractional digits is 5 which is in line with the limits of the 32-bit floating point numbers
   * provided by avr-gcc.
   * @param val the value to write out.
   * @return a self reference to allow chaining of << operators.
   */

  template<class TImpl,class TGraphicsLibrary>
  inline TerminalBase<TImpl,TGraphicsLibrary>& TerminalBase<TImpl,TGraphicsLibrary>::operator<<(double val) {

    operator<<(DoublePrecision(val,TGraphicsLibrary::MAX_DOUBLE_FRACTION_DIGITS));
    return *this;
  }


  /**
   * Output a double-precision number using a structure that defines the number and the number of fractional
   * digits that you want to write (up to 5).
   * @param val the value to write out.
   * @return a self reference to allow chaining of << operators.
   */

  template<class TImpl,class TGraphicsLibrary>
  inline TerminalBase<TImpl,TGraphicsLibrary>& TerminalBase<TImpl,TGraphicsLibrary>::operator<<(const DoublePrecision& val) {

    char buf[25];

    TGraphicsLibrary::modp_dtoa(val.Value,val.Precision,buf);
    writeString(buf);
    return *this;
  }
}

