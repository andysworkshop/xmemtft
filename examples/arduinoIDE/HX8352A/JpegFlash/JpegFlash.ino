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

#include "Generic16BitHX8352A.h"

using namespace lcd;

// Graphics compiled in to flash

extern const uint32_t Test0Pixels,Test0PixelsSize;
extern const uint32_t Test1Pixels,Test1PixelsSize;
extern const uint32_t Test2Pixels,Test2PixelsSize;
extern const uint32_t Test3Pixels,Test3PixelsSize;
extern const uint32_t Test4Pixels,Test4PixelsSize;

// We'll be working in portrait mode, 64K

typedef LG_KF700_Portrait_64K_Gpio16Latch LcdAccess;
LcdAccess *tft;
DefaultBacklight *backlight;


void setup() {

  // create a backlight manager and switch off the backlight
  // so the user doesn't see the random data that can appear
  // during initialisation

  backlight=new DefaultBacklight;
  backlight->setPercentage(0);

  // create and initialise the panel

  tft=new LcdAccess;

  // clear to white

  tft->setBackground(ColourNames::WHITE);
  tft->clearScreen();

  // fade up the backlight to 100% in 4ms steps (400ms total)
  // now that we are in a known good state

  backlight->fadeTo(100,4);
}


void loop() {

  // show the demo with no fade out/in between frames

  showJpeg(GET_FAR_ADDRESS(Test0Pixels),GET_FAR_ADDRESS(Test0PixelsSize),false);
  showJpeg(GET_FAR_ADDRESS(Test1Pixels),GET_FAR_ADDRESS(Test1PixelsSize),false);
  showJpeg(GET_FAR_ADDRESS(Test2Pixels),GET_FAR_ADDRESS(Test2PixelsSize),false);
  showJpeg(GET_FAR_ADDRESS(Test3Pixels),GET_FAR_ADDRESS(Test3PixelsSize),false);
  showJpeg(GET_FAR_ADDRESS(Test4Pixels),GET_FAR_ADDRESS(Test4PixelsSize),false);

  // show the demo with fade out/in between frames

  showJpeg(GET_FAR_ADDRESS(Test0Pixels),GET_FAR_ADDRESS(Test0PixelsSize),true);
  showJpeg(GET_FAR_ADDRESS(Test1Pixels),GET_FAR_ADDRESS(Test1PixelsSize),true);
  showJpeg(GET_FAR_ADDRESS(Test2Pixels),GET_FAR_ADDRESS(Test2PixelsSize),true);
  showJpeg(GET_FAR_ADDRESS(Test3Pixels),GET_FAR_ADDRESS(Test3PixelsSize),true);
  showJpeg(GET_FAR_ADDRESS(Test4Pixels),GET_FAR_ADDRESS(Test4PixelsSize),true);
}


void showJpeg(uint32_t pixelData,uint32_t pixelDataSize,bool fade) {

  // fade down the lights if we're doing that

  if(fade)
    backlight->fadeTo(0,5);

  // draw the image

  JpegFlashDataSource ds(pixelData,pixelDataSize);
  tft->drawJpeg(Point(0,0),ds);

  // fade up the lights

  if(fade)
    backlight->fadeTo(100,5);

  // pause for appreciation :)

  delay(5000);
}

