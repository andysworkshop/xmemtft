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


namespace lcd {

	/*
	 * Base class to manage the display as a character terminal. Derivations for both landscape
	 * and portrait mode are supplied. Hardware scrolling is supported in portrait mode. In landscape
	 * mode the terminal will clear and restart at the top when the end is reached.
	 *
	 * The font must be fixed width or wierd stuff will happen.
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


	/*
	 * Constructor. You probably want to call clearScreen before you get going
	 */

	template<class TImpl,class TGraphicsLibrary>
	inline TerminalBase<TImpl,TGraphicsLibrary>::TerminalBase(
			TGraphicsLibrary *gl,
			const Font *font)
		: _gl(gl),
		  _font(font) {

		calcTerminalSize();
	}


	/*
	 * Calculate the terminal size, in characters.
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


	/*
	 * Clear the screen
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
	 * Clear just the current line
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


	/*
	 * Write a line to the display
	 */

	template<class TImpl,class TGraphicsLibrary>
	inline void TerminalBase<TImpl,TGraphicsLibrary>::writeString(const char *str) {

		const char *ptr;

		for(ptr=str;*ptr;writeCharacter(*ptr++));
	}


	/*
	 * Write a character to the display
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


	/*
	 * Increment the row and scroll if we have hit the bottom. If the LCD implementation supports
	 * hardware scrolling then we will use it, otherwise we just clear the display and start again
	 * at the top left.
	 */

	template<class TImpl,class TGraphicsLibrary>
	inline void TerminalBase<TImpl,TGraphicsLibrary>::incrementY() {

		_cursor.Y++;

		if(_cursor.Y>=_terminalSize.Height)
			static_cast<TImpl *>(this)->scroll();
	}


	/*
	 * Write a string using the stream operator
	 */

	template<class TImpl,class TGraphicsLibrary>
	inline TerminalBase<TImpl,TGraphicsLibrary>& TerminalBase<TImpl,TGraphicsLibrary>::operator<<(const char *str) {

		writeString(str);
		return *this;
	}

	/*
	 * Write various types
	 */

	template<class TImpl,class TGraphicsLibrary>
	inline TerminalBase<TImpl,TGraphicsLibrary>& TerminalBase<TImpl,TGraphicsLibrary>::operator<<(char c) {

		writeCharacter(c);
		return *this;
	}

	template<class TImpl,class TGraphicsLibrary>
	inline TerminalBase<TImpl,TGraphicsLibrary>& TerminalBase<TImpl,TGraphicsLibrary>::operator<<(int16_t val) {

		char buf[10];
		itoa(val,buf,10);
		writeString(buf);

		return *this;
	}

	template<class TImpl,class TGraphicsLibrary>
	inline TerminalBase<TImpl,TGraphicsLibrary>& TerminalBase<TImpl,TGraphicsLibrary>::operator<<(int32_t val) {

		char buf[15];
		ltoa(val,buf,10);
		writeString(buf);

		return *this;
	}

	template<class TImpl,class TGraphicsLibrary>
	inline TerminalBase<TImpl,TGraphicsLibrary>& TerminalBase<TImpl,TGraphicsLibrary>::operator<<(double val) {

		operator<<(DoublePrecision(val,TGraphicsLibrary::MAX_DOUBLE_FRACTION_DIGITS));
		return *this;
	}

	template<class TImpl,class TGraphicsLibrary>
	inline TerminalBase<TImpl,TGraphicsLibrary>& TerminalBase<TImpl,TGraphicsLibrary>::operator<<(const DoublePrecision& val) {

		char buf[25];

		TGraphicsLibrary::modp_dtoa(val.Value,val.Precision,buf);
		writeString(buf);
		return *this;
	}
}

