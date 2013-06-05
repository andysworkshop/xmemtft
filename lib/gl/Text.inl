/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

#pragma once


namespace lcd {

	/*
	 * Write a null terminated string of characters to the display.
	 * Returns the size of the string
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


	/*
	 * Write a single character from a bitmap font
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

	/*
	 * Measure the rectangle required to display the given null terminated string.
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

	/*
	 * Text stream operators
	 */

	template<class TDevice,class TAccessMode>
	inline GraphicsLibrary<TDevice,TAccessMode>& GraphicsLibrary<TDevice,TAccessMode>::operator<<(const char *str) {

		_streamSelectedPoint.X+=writeString(_streamSelectedPoint,*_streamSelectedFont,str).Width;
		return *this;
	}

	template<class TDevice,class TAccessMode>
	inline GraphicsLibrary<TDevice,TAccessMode>& GraphicsLibrary<TDevice,TAccessMode>::operator<<(char c) {

		FontChar fc;

		_streamSelectedFont->getCharacter(c,fc);
		writeCharacter(_streamSelectedPoint,*_streamSelectedFont,fc);
		_streamSelectedPoint.X+=fc.PixelWidth+_streamSelectedFont->getCharacterSpacing();

		return *this;
	}

	template<class TDevice,class TAccessMode>
	inline GraphicsLibrary<TDevice,TAccessMode>& GraphicsLibrary<TDevice,TAccessMode>::operator<<(int16_t val) {

		char buf[10];
		itoa(val,buf,10);
		_streamSelectedPoint.X+=writeString(_streamSelectedPoint,*_streamSelectedFont,buf).Width;

		return *this;
	}

	template<class TDevice,class TAccessMode>
	inline GraphicsLibrary<TDevice,TAccessMode>& GraphicsLibrary<TDevice,TAccessMode>::operator<<(int32_t val) {

		char buf[15];
		ltoa(val,buf,10);
		_streamSelectedPoint.X+=writeString(_streamSelectedPoint,*_streamSelectedFont,buf).Width;

		return *this;
	}

	template<class TDevice,class TAccessMode>
	inline GraphicsLibrary<TDevice,TAccessMode>& GraphicsLibrary<TDevice,TAccessMode>::operator<<(const Point& p) {
		_streamSelectedPoint=p;
		return *this;
	}

	template<class TDevice,class TAccessMode>
	inline GraphicsLibrary<TDevice,TAccessMode>& GraphicsLibrary<TDevice,TAccessMode>::operator<<(const Font& f) {
		_streamSelectedFont=&f;
		return *this;
	}

	template<class TDevice,class TAccessMode>
	GraphicsLibrary<TDevice,TAccessMode>& GraphicsLibrary<TDevice,TAccessMode>::operator<<(double val) {
		operator<<(DoublePrecision(val,MAX_DOUBLE_FRACTION_DIGITS));
		return *this;
	}

	template<class TDevice,class TAccessMode>
	inline GraphicsLibrary<TDevice,TAccessMode>& GraphicsLibrary<TDevice,TAccessMode>::operator<<(const DoublePrecision& val) {

		char str[25];

		modp_dtoa(val.Value,val.Precision,str);
		_streamSelectedPoint.X+=writeString(_streamSelectedPoint,*_streamSelectedFont,str).Width;
		return *this;
	}


	/*
	 * Derived from http://code.google.com/p/stringencoders/source/browse/trunk/src/modp_numtoa.c
	 * "string encoders: A collection of high performance c-string transformations".
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

		// andy's mod: reverse the string in place. this is probably optimal.

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
