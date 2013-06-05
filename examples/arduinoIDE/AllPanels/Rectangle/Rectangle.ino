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
  
  Rectangle rc;
  
  // draw a red border around the display
  
  rc.X=rc.Y=0;
  rc.Width=tft->getXmax();
  rc.Height=tft->getYmax();

  tft->setForeground(ColourNames::RED);
  tft->drawRectangle(rc);

  // fill a rectangle in the center with blue
  
  rc.X=20;
  rc.Y=20;
  rc.Width=tft->getXmax()-40;
  rc.Height=tft->getYmax()-40;

  tft->setForeground(ColourNames::BLUE);
  tft->fillRectangle(rc);
  
  // erase a central rectangle from the blue one
  
  rc.X+=40;
  rc.Y+=40;
  rc.Width-=80;
  rc.Height-=80;
  
  tft->setBackground(ColourNames::BLACK);
  tft->clearRectangle(rc);
  
  // the end
  
  for(;;);
}

