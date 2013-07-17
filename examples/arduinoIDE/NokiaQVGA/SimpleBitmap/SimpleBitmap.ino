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

#include "Nokia6300.h"

using namespace lcd;

// set up in Landscape mode 

typedef Nokia6300_Landscape_262K TftPanel;

TftPanel *tft;
DefaultBacklight *backlight;

// reference to the bitmap pixels and size in flash

extern const uint32_t GlobePixels;
extern const uint32_t GlobePixelsSize;

// some program control variables

int8_t xdir,ydir;
Bitmap bm;
Size panelSize;
Point bmPos;

void setup() {

  // create a backlight controller and use it
  // to switch the backlight off
  
  backlight=new DefaultBacklight;
  backlight->setPercentage(0);

  // reset and initialise the panel

  tft=new TftPanel;

  // clear to black

  tft->setBackground(ColourNames::BLACK);
  tft->clearScreen();

  // fade up the backlight to 100% in 4ms steps (400ms total)

  backlight->fadeTo(100,4);

  // set up the bitmap descriptor

  bm.Dimensions.Width=66;
  bm.Dimensions.Height=66;
  bm.DataSize=GET_FAR_ADDRESS(GlobePixelsSize);
  bm.Pixels=GET_FAR_ADDRESS(GlobePixels);

  // store the panel width and height

  panelSize.Width=tft->getWidth();
  panelSize.Height=tft->getHeight();

  // starting co-ordinates and directions

  bmPos.X=(panelSize.Width/2)-33;
  bmPos.Y=(panelSize.Height/2)-33;
  xdir=ydir=1;
}

void loop() {

  // draw the bitmap
  
  tft->drawUncompressedBitmap(bmPos,bm);

  // move it

  bmPos.X+=xdir;
  bmPos.Y+=ydir;

  // if the edge is hit, bounce it back

  if(bmPos.X==panelSize.Width-66)
    xdir=-1;
  else if(bmPos.X==0)
    xdir=1;

  if(bmPos.Y==panelSize.Height-66)
    ydir=-1;
  else if(bmPos.Y==0)
    ydir=1;
}

