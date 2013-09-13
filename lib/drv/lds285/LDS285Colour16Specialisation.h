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
 * @file LDS285Colour16Specialisation.h
 * @brief Specialisation of LDS285Colour for 16-bit colours.
 * @ingroup LDS285
 */

#pragma once


namespace lcd {


  /**
   * @brief Template specialisation of LDS285Colour for 16-bit colours
   * @tparam TAccessMode The access mode in use.
   * @ingroup LDS285
   */

  template<class TAccessMode,class TPanelTraits>
  class LDS285Colour<COLOURS_16BIT,TAccessMode,TPanelTraits> {

    protected:
      uint16_t getInterfacePixelFormat() const;

      typedef uint32_t TColour;

      struct UnpackedColour {
        uint8_t first,second;
      };

    public:
      void unpackColour(TColour src,UnpackedColour& dest) const;
      void unpackColour(uint8_t red,uint8_t green,uint8_t blue,UnpackedColour& dest) const;

      void writePixel(const UnpackedColour& cr) const;
      void writePixelAgain(const UnpackedColour& cr) const;
      void fillPixels(uint32_t numPixels,const UnpackedColour& cr) const;

      void allocatePixelBuffer(uint32_t numPixels,uint8_t*& buffer,uint32_t& bytesPerPixel) const;
      void rawFlashTransfer(uint32_t pixels,uint32_t numPixels) const;

      uint8_t getBytesPerPixel() const;
  };


  /**
   * Get the register setting for 16-bit colours
   * @return 16-bit interface pixel format register setting
   */

  template<class TAccessMode,class TPanelTraits>
  inline uint16_t LDS285Colour<COLOURS_16BIT,TAccessMode,TPanelTraits>::getInterfacePixelFormat() const {
    return 0x55;
  }


  /**
   * Unpack the colour from rrggbb to the internal 5-6-5 format
   *
   * 00000000RRRRRRRRGGGGGGGGBBBBBBBB ->
   * 0000000000000000RRRRRGGGGGGBBBBB
   *
   * @param src rrggbb
   * @param dest The unpacked colour structure
   */

  template<class TAccessMode,class TPanelTraits>
  inline void LDS285Colour<COLOURS_16BIT,TAccessMode,TPanelTraits>::unpackColour(TColour src,UnpackedColour& dest) const {
    uint8_t r,g,b;

    r=src >> 16;
    g=src >> 8;
    b=src;

    r &= 0xf8;
    g &= 0xfc;
    b &= 0xf8;

    dest.first=r | (g>>5);
    dest.second=(g << 3) | (b >> 3);
  }


  /**
   * Unpack the colour from components to the internal format
   * @param red
   * @param green
   * @param blue
   * @param dest
   */

  template<class TAccessMode,class TPanelTraits>
  inline void LDS285Colour<COLOURS_16BIT,TAccessMode,TPanelTraits>::unpackColour(uint8_t red,uint8_t green,uint8_t blue,UnpackedColour& dest) const {

    red &= 0xf8;
    green &= 0xfc;
    blue &= 0xf8;

    dest.first=red | (green>>5);
    dest.second=(green << 3) | (blue >> 3);
  }


  /**
   * Write a single pixel to the current output position.
   * Assumes that the caller has already issued the beginWriting() command.
   * @param cr The pixel to write
   */

  template<class TAccessMode,class TPanelTraits>
  inline void LDS285Colour<COLOURS_16BIT,TAccessMode,TPanelTraits>::writePixel(const UnpackedColour& cr) const {
    TAccessMode::writeData(cr.first);
    TAccessMode::writeData(cr.second);
  }


  /**
   * Write the same colour pixel that we last wrote. This gives the access mode a chance to
   * optimise sequential pixel writes. The colour is provided for drivers that cannot optimise
   * and must fall back to a full write.
   * @param cr The pixel to write
   */

  template<class TAccessMode,class TPanelTraits>
  inline void LDS285Colour<COLOURS_16BIT,TAccessMode,TPanelTraits>::writePixelAgain(const UnpackedColour& cr) const {
    TAccessMode::writeData(cr.first);
    TAccessMode::writeData(cr.second);
  }


  /**
   * Fill a block of pixels with the same colour. This operation will issue the
   * beginWriting() command for you.
   * @param numPixels how many
   * @param cr The unpacked colour to write
   */

  template<class TAccessMode,class TPanelTraits>
  inline void LDS285Colour<COLOURS_16BIT,TAccessMode,TPanelTraits>::fillPixels(uint32_t numPixels,const UnpackedColour& cr) const {

    uint8_t first,second;

    TAccessMode::writeCommand(lds285::MEMORY_WRITE);

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

  template<class TAccessMode,class TPanelTraits>
  inline void LDS285Colour<COLOURS_16BIT,TAccessMode,TPanelTraits>::allocatePixelBuffer(uint32_t numPixels,uint8_t*& buffer,uint32_t& bytesPerPixel) const {
    buffer=(uint8_t *)malloc(numPixels*2);
    bytesPerPixel=2;
  }


  /**
   * Bulk-copy some pixels from the memory buffer to the LCD. The pixels must already be formatted ready
   * for transfer.
   * @param buffer The memory buffer
   * @param numPixels The number of pixels to transfer from the buffer
   */

  template<class TAccessMode,class TPanelTraits>
  inline void LDS285Colour<COLOURS_16BIT,TAccessMode,TPanelTraits>::rawFlashTransfer(uint32_t buffer,uint32_t numPixels) const {

    TAccessMode::writeCommand(lds285::MEMORY_WRITE);
    TAccessMode::rawFlashTransfer(buffer,numPixels*2);
  }


  /**
   * Get the number of bytes per pixel
   * @return 2
   */

  template<class TAccessMode,class TPanelTraits>
  inline uint8_t LDS285Colour<COLOURS_16BIT,TAccessMode,TPanelTraits>::getBytesPerPixel() const {
    return 2;
  }
}
