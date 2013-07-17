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

#pragma once


/**
 * @file LzgText.inl
 * @brief Compressed TrueType font output functions
 *
 * The LzgFontConv utility allows you to compress and save characters from TrueType fonts that will
 * be compiled into flash memory as bitmaps. These functions are used to decompress and write out
 * those characters using a familiar character 'string' interface.
 *
 * @ingroup GraphicsLibrary
 */


namespace lcd {


	/**
	 * Write a null terminated string of characters to the display.
	 * @param p The upper-left co-ordinate on the panel to start writing at.
	 * @param font The LzgFont that the characters will come from.
	 * @param str The character string to write.
	 * @return The pixel size of the string.
	 */

	template<class TDevice,class TAccessMode>
	inline Size GraphicsLibrary<TDevice,TAccessMode>::writeString(const Point& p,const LzgFont& font,const char *str) const {

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

			if(fc.Code!=' ')										// space is special and never has any data but does have a size
				writeCharacter(pos,font,fc);

			width=fc.PixelWidth+font.getCharacterSpacing();
			pos.X+=width;
			s.Width+=width;
		}

		return s;
	}


	/**
	 * Write a single character
	 * @param p The upper-left co-ordinate on the panel to start writing at.
	 * @param font The LzgFont that the characters will come from.
	 * @param fc The FontChar definition of the character to write. LzgFont.getCharacter() will get you this structure,.
	 */

	template<class TDevice,class TAccessMode>
	inline void GraphicsLibrary<TDevice,TAccessMode>::writeCharacter(const Point& p,const LzgFont& font,const FontChar& fc) const {

		Bitmap bm;
		uint16_t lsb,msb;
		const uint8_t *ptr;
		Point charLocation(p);

		// extract the data size and data ptr

		ptr=fc.Data;
		lsb=pgm_read_byte(ptr++);
		msb=pgm_read_byte(ptr++);

		// set up the rest of the structure

		bm.Dimensions.Width=fc.PixelWidth;
		bm.Dimensions.Height=font.getHeight();
		bm.DataSize=(msb<<8) | lsb;
		bm.Pixels=reinterpret_cast<uint32_t>(ptr);

		// draw the bitmap

		drawCompressedBitmap(charLocation,bm);
	}
}
