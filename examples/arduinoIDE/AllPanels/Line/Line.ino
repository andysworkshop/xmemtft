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

  Point p1,p2;
  int i;
  TftPanel::TColour randomColour;
 
  for(i=0;i<1000;i++) {

    p1.X=rand() % tft->getXmax();
    p1.Y=rand() % tft->getYmax();
    p2.X=rand() % tft->getXmax();
    p2.Y=rand() % tft->getYmax();

    randomColour=(((uint32_t)rand() << 16) | rand()) & 0xffffff;

    tft->setForeground(randomColour);
    tft->drawLine(p1,p2);
  }
  
  tft->clearScreen();
}

