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
 * @file MC2PA8201Colour18Specialisation.h
 * @brief Specialisation of MC2PA8201Colour for 18-bit colours.
 * @ingroup MC2PA8201
 */

#pragma once


namespace lcd {

  /**
   * Template class holding the specialisation of MC2PA8201Colour for 18-bit colours
   * @tparam TAccessMode The access mode class
   */

  template<class TAccessMode,class TPanelTraits>
  class MC2PA8201Colour<COLOURS_18BIT,TAccessMode,TPanelTraits> {

    protected:
      uint16_t getInterfacePixelFormat() const;

      typedef uint32_t TColour;

      struct UnpackedColour {
        uint8_t r,g,b;
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
   * Get the register setting for 16-bit colours
   * @return 16-bit interface pixel format register setting
   */

  template<class TAccessMode,class TPanelTraits>
  inline uint16_t MC2PA8201Colour<COLOURS_18BIT,TAccessMode,TPanelTraits>::getInterfacePixelFormat() const {
    return 0x66;
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

  template<class TAccessMode,class TPanelTraits>
  inline void MC2PA8201Colour<COLOURS_18BIT,TAccessMode,TPanelTraits>::unpackColour(TColour src,UnpackedColour& dest) const {
    dest.r=(src >> 16) & 0xfc;
    dest.g=(src >> 8) & 0xfc;
    dest.b=src & 0xfc;
  }

  /**
   * Unpack the colour from components to the internal format
   * @param red
   * @param green
   * @param blue
   * @param dest
   */

  template<class TAccessMode,class TPanelTraits>
  inline void MC2PA8201Colour<COLOURS_18BIT,TAccessMode,TPanelTraits>::unpackColour(uint8_t red,uint8_t green,uint8_t blue,UnpackedColour& dest) const {
    dest.r=red & 0xfc;
    dest.g=green & 0xfc;
    dest.b=blue & 0xfc;
  }

  /**
   * Write a single pixel to the current output position.
   * Assumes that the caller has already issued the beginWriting() command.
   * @param cr The pixel to write
   */

  template<class TAccessMode,class TPanelTraits>
  inline void MC2PA8201Colour<COLOURS_18BIT,TAccessMode,TPanelTraits>::writePixel(const UnpackedColour& cr) const {
    TAccessMode::writeData(cr.r);
    TAccessMode::writeData(cr.g);
    TAccessMode::writeData(cr.b);
  }


  /**
   * Write the same colour pixel that we last wrote. This gives the access mode a chance to
   * optimise sequential pixel writes. The colour is provided for drivers that cannot optimise
   * and must fall back to a full write.
   * @param cr The pixel to write
   */

  template<class TAccessMode,class TPanelTraits>
  inline void MC2PA8201Colour<COLOURS_18BIT,TAccessMode,TPanelTraits>::writePixelAgain(const UnpackedColour& cr) const {
    TAccessMode::writeData(cr.r);
    TAccessMode::writeData(cr.g);
    TAccessMode::writeData(cr.b);
  }


  /**
   * Fill a block of pixels with the same colour. This operation will issue the
   * beginWriting() command for you.
   * @param numPixels how many
   * @param cr The unpacked colour to write
   */

  template<class TAccessMode,class TPanelTraits>
  inline void MC2PA8201Colour<COLOURS_18BIT,TAccessMode,TPanelTraits>::fillPixels(uint32_t numPixels,const UnpackedColour& cr) const {

    uint8_t b,g,r;

    TAccessMode::writeCommand(mc2pa8201::MEMORY_WRITE);

    b=cr.b;
    g=cr.g;
    r=cr.r;

    while(numPixels--) {
      TAccessMode::writeData(r);
      TAccessMode::writeData(g);
      TAccessMode::writeData(b);
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
  inline void MC2PA8201Colour<COLOURS_18BIT,TAccessMode,TPanelTraits>::allocatePixelBuffer(uint32_t numPixels,uint8_t*& buffer,uint32_t& bytesPerPixel) const {
    buffer=(uint8_t *)malloc(numPixels*3);
    bytesPerPixel=3;
  }


  /**
   * Bulk-copy some pixels from the memory buffer to the LCD. The pixels must already be formatted ready
   * for transfer.
   * @param buffer The memory buffer
   * @param numPixels The number of pixels to transfer from the buffer
   */

  template<class TAccessMode,class TPanelTraits>
  inline void MC2PA8201Colour<COLOURS_18BIT,TAccessMode,TPanelTraits>::rawFlashTransfer(uint32_t data,uint32_t numPixels) const {

    TAccessMode::writeCommand(mc2pa8201::MEMORY_WRITE);
    TAccessMode::rawTransfer(data,numPixels*3);
  }


  /**
   * Get the number of bytes per pixel
   * @return 3
   */

  template<class TAccessMode,class TPanelTraits>
  inline uint8_t MC2PA8201Colour<COLOURS_18BIT,TAccessMode,TPanelTraits>::getBytesPerPixel() const {
    return 3;
  }
}
