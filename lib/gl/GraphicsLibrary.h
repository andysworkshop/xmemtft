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
	 * Template implementation of a graphics library. This library inherits from the device implementation
	 * that provides the methods that the graphics library needs to access the hardware
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

			Point _streamSelectedPoint;									// need to keep a copy so rvalue points can be used
			const Font *_streamSelectedFont;						// can keep a ptr, user should not delete font while selected

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
