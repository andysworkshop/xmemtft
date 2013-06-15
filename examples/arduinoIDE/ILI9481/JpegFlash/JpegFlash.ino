/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

#include "Generic16BitILI9481.h"

using namespace lcd;

// Graphics compiled in to flash

extern const uint32_t Test0Pixels,Test0PixelsSize;
extern const uint32_t Test1Pixels,Test1PixelsSize;

// We'll be working in portrait mode, 64K

typedef ILI9481_Landscape_64K_Gpio LcdAccess;
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
  
  // set some gamma values for the panel (change or delete for your panel)

  ILI9481Gamma gamma(0,0xf3,0,0xbc,0x50,0x1f,0,7,0x7f,0x7,0xf,0);
  tft->applyGamma(gamma);

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

  // show the demo with fade out/in between frames

  showJpeg(GET_FAR_ADDRESS(Test0Pixels),GET_FAR_ADDRESS(Test0PixelsSize),true);
  showJpeg(GET_FAR_ADDRESS(Test1Pixels),GET_FAR_ADDRESS(Test1PixelsSize),true);
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

