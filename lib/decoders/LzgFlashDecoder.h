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
 * @file LzgFlashDecoder.h
 * @brief LZG decompression interface.
 * @ingroup Decoders
 */

#pragma once


namespace lcd {


  /**
   * LZG decoder template class
   * @tparam AccessMode The access mode in use
   * @ingroup Decoders
   */

  template<class TAccessMode>
  class LzgFlashDecoder {

    protected:
      static uint8_t readNextByte(uint32_t src);

    public:
      static void decode(uint32_t in,uint32_t insize);
  };


  /**
   * Decode the LZG stream and write to the LCD. This function costs you
   * 2Kb of stack to call (note the circbuf size)
   * @param in The 32-bit flash address of the data.
   * @param insize The size of the compressed data.
   */

  template<class TAccessMode>
  inline void LzgFlashDecoder<TAccessMode>::decode(uint32_t in,uint32_t insize) {

    static const uint8_t LZG_LENGTH_DECODE_LUT[32]= { 2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,35,48,72,128 };

    uint8_t *dst,*dstEnd,*copy,symbol,b,b2;
    uint8_t marker1,marker2,marker3,marker4;
    uint32_t inEnd,src;
    uint16_t offset,length,i;
    char isMarkerSymbolLUT[256];
    uint8_t circbuf[2056];          // this is the history buffer

    // Initialize the byte streams
    src=in;
    inEnd=in+insize;
    dst=circbuf;
    dstEnd=circbuf+sizeof(circbuf);

    // Skip header information
    src+=16;

    // Get marker symbols from the input stream
    marker1=readNextByte(src++);
    marker2=readNextByte(src++);
    marker3=readNextByte(src++);
    marker4=readNextByte(src++);

    // Initialize marker symbol LUT
    for(i=0;i<256;++i)
      isMarkerSymbolLUT[i]=0;

    isMarkerSymbolLUT[marker1]=1;
    isMarkerSymbolLUT[marker2]=1;
    isMarkerSymbolLUT[marker3]=1;
    isMarkerSymbolLUT[marker4]=1;

    // Main decompression loop
    while(src<inEnd) {
      // Get the next symbol
      symbol=readNextByte(src++);

      // Marker symbol?
      if(!isMarkerSymbolLUT[symbol]) {

        // Literal copy

        TAccessMode::writeStreamedData(symbol);
        *dst++=symbol;
        if(dst==dstEnd)
          dst=circbuf;

      } else {

        b=readNextByte(src++);

        if(b) {

          // Decode offset / length parameters

          if(symbol == marker1) {
            // Distant copy is not supported on the Arduino due to lack of memory
            return;
          } else if(symbol == marker2) {

            // Medium copy

            length=LZG_LENGTH_DECODE_LUT[b & 0x1f];
            b2=readNextByte(src++);
            offset=(((uint16_t)(b & 0xe0)) << 3) | b2;
            offset+=8;
          } else if(symbol == marker3) {

            // Short copy

            length=(b >> 6) + 3;
            offset=(b & 0x3f) + 8;
          } else {

            // Near copy (including RLE)

            length=LZG_LENGTH_DECODE_LUT[b & 0x1f];
            offset=(b >> 5) + 1;
          }

          // Copy corresponding data from history window

          if(offset<=static_cast<uint16_t>(dst-circbuf))
            copy=dst-offset;
          else
            copy=dstEnd-(offset-(uint16_t)(dst-circbuf));

          for(i=0;i<length;i++) {
            TAccessMode::writeStreamedData(*copy);

            *dst++=*copy++;

            if(dst==dstEnd)
              dst=circbuf;

            if(copy==dstEnd)
              copy=circbuf;
          }

        } else {
          // Single occurance of a marker symbol...
          TAccessMode::writeStreamedData(symbol);
          *dst++=symbol;
          if(dst==dstEnd)
            dst=circbuf;
        }
      }
    }
  }


  /**
   * Read the next byte from flash
   * @param src flash address
   * @return The next byte
   */

  template<class TAccessMode>
  inline uint8_t LzgFlashDecoder<TAccessMode>::readNextByte(uint32_t src) {
    return src<65536 ? pgm_read_byte_near(src) : pgm_read_byte_far(src);
  }
}
