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
 * @file Rectangle.inl
 * @brief Functions that operate on rectangles.
 * @ingroup GraphicsLibrary
 */

#pragma once


namespace lcd {

  /**
   * Fill a rectangle with the foreground colour
   * @parm rc The rectangle to fill.
   */

  template<class TDevice,class TAccessMode>
  inline void GraphicsLibrary<TDevice,TAccessMode>::fillRectangle(const Rectangle& rc) const {

    this->moveTo(rc);
    this->fillPixels((int32_t)rc.Width*(int32_t)rc.Height,_foreground);
  }


  /**
   * Fill a rectangle with the background colour
   * @param rc The rectangle to clear.
   */

  template<class TDevice,class TAccessMode>
  inline void GraphicsLibrary<TDevice,TAccessMode>::clearRectangle(const Rectangle& rc) const {

    this->moveTo(rc);
    this->fillPixels((int32_t)rc.Width*(int32_t)rc.Height,_background);
  }


  /**
   * Convenience function to draw an outline of a rectangle by calling fillRectangle 4 times
   * Filling rectangles is much more efficient than plotting points
   * @param rect The rectangle to draw.
   */

  template<class TDevice,class TAccessMode>
  inline void GraphicsLibrary<TDevice,TAccessMode>::drawRectangle(const Rectangle& rect) const {

    Rectangle rc(rect);

    // top

    rc.Height=1;
    fillRectangle(rc);

    // bottom

    rc.Y+=rect.Height-1;
    fillRectangle(rc);

    // left

    rc.Height=rect.Height;
    rc.Y=rect.Y;
    rc.Width=1;
    fillRectangle(rc);

    // right
    rc.X+=rect.Width-1;
    fillRectangle(rc);
  }


  /**
   * Gradient fill a rectangle from the foreground to the background colour. This uses line
   * draing to create the gradient, which will fall back to a fast rectangle fill because
   * all the lines are straight.
   * @param rc The bounding rectangle of the entire gradient.
   * @param dir The direction of the gradient, horizontal or vertical.
   * @param first The starting colour of the gradient.
   * @param last The ending colour of the gradient.
   */

  template<class TDevice,class TAccessMode>
  inline void GraphicsLibrary<TDevice,TAccessMode>::gradientFillRectangle(
              const Rectangle& rc,
              Direction dir,
              TColour first,
              TColour last) const {

    uint8_t r1,g1,b1,r2,g2,b2;
    int32_t rstep,gstep,bstep;
    int16_t raccum,gaccum,baccum,i,r,g,b,val,div,xdisp,ydisp,px;
    Rectangle rcBlock;
    TColour cr;
    UnpackedColour lineColour;

    // get the start and end colour components

    r1=first >> 16;
    g1=first >> 8;
    b1=first;

    r2=last >> 16;
    g2=last >> 8;
    b2=last;

    // calculate initial sizes and directions

    rcBlock.X=rc.X;
    rcBlock.Y=rc.Y;

    if(dir==VERTICAL) {
      rcBlock.Width=rc.Width;
      rcBlock.Height=1;
      xdisp=0;
      ydisp=1;
      div=rc.Height;
      px=rc.Width;
    }
    else {
      rcBlock.Width=1;
      rcBlock.Height=rc.Height;
      xdisp=1;
      ydisp=0;
      div=rc.Width;
      px=rc.Height;
    }

    // calculate the step values, scaled up x256 for greater precision

    rstep=(((int32_t)r2-(int32_t)r1)*256)/div;
    gstep=(((int32_t)g2-(int32_t)g1)*256)/div;
    bstep=(((int32_t)b2-(int32_t)b1)*256)/div;

    // initial colour and reset accumulators

    cr=first;
    raccum=gaccum=baccum=0;

    r=r1;
    g=g1;
    b=b1;

    for(i=0;i<div;i++) {

      // draw the line

      this->moveTo(rcBlock);
      this->unpackColour(cr,lineColour);
      this->fillPixels(px,lineColour);

      // update for the next line

      rcBlock.X+=xdisp;
      rcBlock.Y+=ydisp;

      // update the accumulators

      raccum+=rstep;
      gaccum+=gstep;
      baccum+=bstep;

      // if any accumulator has moved past 0 (scaled by 256) then add that accumulator
      // to the colour and reduce the accumulator accordingly

      if((val=raccum/256)!=0) {
        r+=val;
        raccum-=val*256;
      }

      if((val=gaccum/256)!=0) {
        g+=val;
        gaccum-=val*256;
      }

      if((val=baccum/256)!=0) {
        b+=val;
        baccum-=val*256;
      }

      // if any accumulator was reset then we have a new colour

      cr=(uint32_t)r<<16 | (uint32_t)g<<8 | b;
    }
  }
}
