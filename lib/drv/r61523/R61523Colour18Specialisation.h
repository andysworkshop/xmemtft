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
 * @file R61523Colour18Specialisation.h
 * @brief Specialisation of R61523Colour for 18-bit colours.
 * @ingroup R61523
 */

#pragma once


namespace lcd {

  /**
   * Template class holding the specialisation of R61523Colour for 18-bit colours
   * @tparam TAccessMode The access mode class
   * @ingroup R61523
   */

  template<class TAccessMode>
  class R61523Colour<COLOURS_18BIT,TAccessMode> {

    protected:
      void setColourDepth() const;

      typedef uint32_t TColour;

      struct UnpackedColour {
        uint16_t first,second;
      };

    public:
      void unpackColour(TColour src,UnpackedColour& dest) const;
      void unpackColour(uint8_t red,uint8_t green,uint8_t blue,UnpackedColour& dest) const;

      void writePixel(const UnpackedColour& cr) const;
      void writePixelAgain(const UnpackedColour& cr) const;
      void fillPixels(uint32_t numPixels,const UnpackedColour& cr) const;

      void allocatePixelBuffer(uint32_t numPixels,uint8_t*& buffer,uint32_t& bytesPerPixel) const;
      void rawFlashTransfer(uint32_t data,uint32_t numPixels) const;

      uint8_t getBytesPerPixel() const;
  };


  /**
   * Set the colour depth to 18-bit
   */

  template<class TAccessMode>
  inline void R61523Colour<COLOURS_18BIT,TAccessMode>::setColourDepth() const {

    // set the pixel format to 18bpp

    TAccessMode::writeCommand(r61523::SET_PIXEL_FORMAT);
    TAccessMode::writeData(0x6);

    // now set DFM to 1 (2 transfers = 1 pixel) (this is requires MCAP enable)

    TAccessMode::writeCommand(r61523::SET_FRAME_AND_INTERFACE);
    TAccessMode::writeData(0x80);
    TAccessMode::writeData(0x1 << 4);
  }


  /**
   * Unpack the colour from rrggbb to the interal 6-6-6 format
   *
   * 00000000RRRRRRRRGGGGGGGGBBBBBBBB ->
   * 00000000RRRRRR00GGGGGG00BBBBBB00
   *
   * @param src rrggbb
   * @param dest The unpacked colour structure
   */

  template<class TAccessMode>
  inline void R61523Colour<COLOURS_18BIT,TAccessMode>::unpackColour(TColour src,UnpackedColour& dest) const {
    dest.first=src & 0xfc;
    dest.second=((src >> 16) | (src & 0xFF00)) & 0xfcfc;
  }

  /**
   * Unpack the colour from components to the internal format
   * @param red
   * @param green
   * @param blue
   * @param dest
   */

  template<class TAccessMode>
  inline void R61523Colour<COLOURS_18BIT,TAccessMode>::unpackColour(uint8_t red,uint8_t green,uint8_t blue,UnpackedColour& dest) const {
    dest.first=blue & 0xfc;
    dest.second=((static_cast<uint16_t>(green) << 8) | red) & 0xfcfc;
  }

  /**
   * Write a single pixel to the current output position.
   * Assumes that the caller has already issued the beginWriting() command.
   * @param cr The pixel to write
   */

  template<class TAccessMode>
  inline void R61523Colour<COLOURS_18BIT,TAccessMode>::writePixel(const UnpackedColour& cr) const {
    TAccessMode::writeData(cr.first);
    TAccessMode::writeData(cr.second);
  }


  /**
   * Write the same colour pixel that we last wrote. This gives the access mode a chance to
   * optimise sequential pixel writes. The colour is provided for drivers that cannot optimise
   * and must fall back to a full write.
   * @param cr The pixel to write
   */

  template<class TAccessMode>
  inline void R61523Colour<COLOURS_18BIT,TAccessMode>::writePixelAgain(const UnpackedColour& cr) const {
    TAccessMode::writeData(cr.first);
    TAccessMode::writeData(cr.second);
  }


  /**
   * Fill a block of pixels with the same colour. This operation will issue the
   * beginWriting() command for you.
   * @param numPixels how many
   * @param cr The unpacked colour to write
   */

  template<class TAccessMode>
  inline void R61523Colour<COLOURS_18BIT,TAccessMode>::fillPixels(uint32_t numPixels,const UnpackedColour& cr) const {

    uint16_t first,second;

    TAccessMode::writeCommand(r61523::MEMORY_WRITE);

    first=cr.first;
    second=cr.second;

    while(numPixels--) {
      TAccessMode::writeData(first);
      TAccessMode::writeData(second);
    }
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
  inline void R61523Colour<COLOURS_18BIT,TAccessMode>::allocatePixelBuffer(uint32_t numPixels,uint8_t*& buffer,uint32_t& bytesPerPixel) const {
    buffer=new uint8_t[numPixels*3];
    bytesPerPixel=3;
  }


  /**
   * Bulk-copy some pixels from the memory buffer to the LCD. The pixels must already be formatted ready
   * for transfer.
   * @param buffer The memory buffer
   * @param numPixels The number of pixels to transfer from the buffer
   */

  template<class TAccessMode>
  inline void R61523Colour<COLOURS_18BIT,TAccessMode>::rawFlashTransfer(uint32_t data,uint32_t numPixels) const {

    TAccessMode::writeCommand(r61523::MEMORY_WRITE);
    TAccessMode::rawTransfer(data,numPixels*3);
  }


  /**
   * Get the number of bytes per pixel
   * @return 3
   */

  template<class TAccessMode>
  inline uint8_t R61523Colour<COLOURS_18BIT,TAccessMode>::getBytesPerPixel() const {
    return 3;
  }
}
