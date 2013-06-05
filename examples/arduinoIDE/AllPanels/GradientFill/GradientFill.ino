/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */
 
#include "Nokia6300.h"

using namespace lcd;

typedef Nokia6300_Portrait_262K TftPanel;

TftPanel *tft;
DefaultBacklight *backlight;


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
}

void loop() {
  doGradientFills(true);
  doGradientFills(false);
}

void doGradientFills(bool horz) {

  Rectangle rc;
  uint16_t i;
  static uint32_t colours[7]={
    ColourNames::RED,
    ColourNames::GREEN,
    ColourNames::BLUE,
    ColourNames::CYAN,
    ColourNames::MAGENTA,
    ColourNames::YELLOW,
    ColourNames::WHITE,
  };

  rc.Width=tft->getXmax()+1;
  rc.Height=(tft->getYmax()+1)/2;

  for(i=0;i<sizeof(colours)/sizeof(colours[0]);i++) {

    rc.X=0;
    rc.Y=0;

    tft->gradientFillRectangle(rc,horz ? HORIZONTAL : VERTICAL,ColourNames::BLACK,colours[i]);
    rc.Y=rc.Height;
    tft->gradientFillRectangle(rc,horz ? HORIZONTAL : VERTICAL,colours[i],ColourNames::BLACK);

    delay(2000);
  }
}


