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
 * @file JpegDecoder.h
 * @brief Picojpeg interface.
 * @ingroup Decoders
 */

#pragma once


namespace lcd {


  /**
   * @brief JPEG decoder
   *
   * This class implements the algorithm required by the picojpeg library.
   *
   * @tparam TAccessMode The access mode that we're using.
   * @ingroup Decoders
   */

  template<class TAccessMode>
  class JpegDecoder {

    typedef typename tLCD::template UnpackedColour<TColourDepth> UNPACKED_COLOUR;

    public:
      static void decode(const Point& pt,JpegDataSource& ds) {

        pjpeg_image_info_t imageInfo;
        UNPACKED_COLOUR cr;

        // initialise the decoder

        if(pjpeg_decode_init(&imageInfo,ds)!=0)
          return;

        int16_t mcu_x=0,mcu_y=0;

        for(;;) {

          if(pjpeg_decode_mcu()!=0)
            return;

          if(mcu_y>=imageInfo.m_MCUSPerCol)
            return;

          for(int y=0;y<imageInfo.m_MCUHeight;y+=8) {

            int by_limit=min(8,imageInfo.m_height-(mcu_y*imageInfo.m_MCUHeight+y));

            for(int x=0;x<imageInfo.m_MCUWidth;x+=8) {

              uint16_t src_ofs=(x*8U)+(y*16U);

              uint8_t *pSrcR=imageInfo.m_pMCUBufR+src_ofs;
              uint8_t *pSrcG=imageInfo.m_pMCUBufG+src_ofs;
              uint8_t *pSrcB=imageInfo.m_pMCUBufB+src_ofs;

              int bx_limit=min(8,imageInfo.m_width-(mcu_x*imageInfo.m_MCUWidth+x));

              tLCD::template moveTo<TOrientation>(
                  Rectangle(pt.X+mcu_x*imageInfo.m_MCUWidth+x,pt.Y+mcu_y*imageInfo.m_MCUHeight+y,bx_limit,by_limit));

              tLCD::beginWriting();

              if(imageInfo.m_scanType==PJPG_GRAYSCALE) {

                for(int by=0;by<by_limit;by++) {

                  for(int bx=0;bx < bx_limit;bx++) {
                    tLCD::template unpackColourParts(*pSrcR,*pSrcR,*pSrcR,cr);
                    tLCD::template writePixel(cr);
                    pSrcR++;
                  }

                  pSrcR+=(8-bx_limit);
                }
              } else {
                for(int by=0;by<by_limit;by++) {

                  for(int bx=0;bx<bx_limit;bx++) {

                    tLCD::template unpackColourParts(*pSrcR,*pSrcG,*pSrcB,cr);

                    pSrcR++;
                    pSrcG++;
                    pSrcB++;

                    tLCD::writePixel(cr);
                  }

                  pSrcR+=(8-bx_limit);
                  pSrcG+=(8-bx_limit);
                  pSrcB+=(8-bx_limit);
                }
              }
            }
          }

          mcu_x++;

          if(mcu_x==imageInfo.m_MCUSPerRow) {
            mcu_x=0;
            mcu_y++;
          }
        }
      }
  };
}

