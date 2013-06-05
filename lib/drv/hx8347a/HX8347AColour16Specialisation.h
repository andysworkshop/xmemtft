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


	/**
	 * Template class holding the specialisation of HX8347AColour for 16-bit colours
	 */

	template<class TAccessMode>
	class HX8347AColour<COLOURS_16BIT,TAccessMode> {

		protected:
			typedef uint32_t TColour;

			struct UnpackedColour {
				uint8_t lo8,hi8;
			};

		public:
			void unpackColour(TColour src,UnpackedColour& dest) const;
			void unpackColour(uint8_t red,uint8_t green,uint8_t blue,UnpackedColour& dest) const;

			void writePixel(const UnpackedColour& cr) const;
			void fillPixels(uint32_t numPixels,const UnpackedColour& cr) const;

			void allocatePixelBuffer(uint32_t numPixels,uint8_t*& buffer,uint32_t& bytesPerPixel) const;
			void rawFlashTransfer(uint32_t pixels,uint32_t numPixels) const;

			uint8_t getBytesPerPixel() const;
	};


	/**
	 * Unpack the colour from rrggbb to the internal 5-6-5 format

	 * 00000000RRRRRRRRGGGGGGGGBBBBBBBB ->
	 * RRRRRGGG,GGGBBBBB

	 * @param src rrggbb
	 * @param dest The unpacked colour structure
	 */

	template<class TAccessMode>
	inline void HX8347AColour<COLOURS_16BIT,TAccessMode>::unpackColour(TColour src,UnpackedColour& dest) const {

		uint8_t r,g,b;

		r=src >> 16;
		g=src >> 8;
		b=src;

		r &= 0xf8;
		g &= 0xfc;
		b &= 0xf8;

		dest.hi8=r | (g>>5);
		dest.lo8=(g << 3) | (b >> 3);
	}


	/**
	 * Unpack the colour from components to the internal format
	 * @param red
	 * @param green
	 * @param blue
	 * @param dest
	 */

	template<class TAccessMode>
	inline void HX8347AColour<COLOURS_16BIT,TAccessMode>::unpackColour(uint8_t red,uint8_t green,uint8_t blue,UnpackedColour& dest) const {

		red &= 0xf8;
		green &= 0xfc;
		blue &= 0xf8;

		dest.hi8=red | (green>>5);
		dest.lo8=(green << 3) | (blue >> 3);
	}


	/**
	 * Write a single pixel to the current output position.
	 * Assumes that the caller has already issued the beginWriting() command.
	 * @param cr The pixel to write
	 */

	template<class TAccessMode>
	inline void HX8347AColour<COLOURS_16BIT,TAccessMode>::writePixel(const UnpackedColour& cr) const {
		TAccessMode::writeData(cr.lo8,cr.hi8);
	}


	/**
	 * Fill a block of pixels with the same colour. This operation will issue the
	 * beginWriting() command for you.
	 * @param numPixels how many
	 * @param cr The unpacked colour to write
	 */

	template<class TAccessMode>
	inline void HX8347AColour<COLOURS_16BIT,TAccessMode>::fillPixels(uint32_t numPixels,const UnpackedColour& cr) const {

		uint8_t first,second;

		first=cr.lo8;
		second=cr.hi8;

		TAccessMode::writeCommand(hx8347a::MEMORY_WRITE);

		while(numPixels--)
			TAccessMode::writeData(first,second);
	}


	/**
	 * Allocate a buffer for pixel data. You supply the number of pixels and this allocates the buffer as a uint8_t[].
	 * Allocated buffers should be freed with free()
	 *
	 * @param numPixels The number of pixels to allocate
	 * @param buffer The output buffer
	 * @param bytesPerPixel Output the number of bytes per pixel
	 */

	template<class TAccessMode>
	inline void HX8347AColour<COLOURS_16BIT,TAccessMode>::allocatePixelBuffer(uint32_t numPixels,uint8_t*& buffer,uint32_t& bytesPerPixel) const {
		buffer=(uint8_t *)malloc(numPixels*2);
		bytesPerPixel=2;
	}


	/**
	 * Bulk-copy some pixels from the memory buffer to the LCD. The pixels must already be formatted ready
	 * for transfer.
	 * @param buffer The memory buffer
	 * @param numPixels The number of pixels to transfer from the buffer
	 */

	template<class TAccessMode>
	inline void HX8347AColour<COLOURS_16BIT,TAccessMode>::rawFlashTransfer(uint32_t buffer,uint32_t numPixels) const {

		TAccessMode::writeCommand(hx8347a::MEMORY_WRITE);
		TAccessMode::rawFlashTransfer(buffer,numPixels*2);
	}


	/**
	 * Get the number of bytes per pixel
	 * @return 2
	 */

	template<class TAccessMode>
	inline uint8_t HX8347AColour<COLOURS_16BIT,TAccessMode>::getBytesPerPixel() const {
		return 2;
	}
}
