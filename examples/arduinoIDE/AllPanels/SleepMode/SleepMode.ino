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

  Rectangle rc;

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
  
  // fill a rectangle in the center with green
  
  rc.X=20;
  rc.Y=20;
  rc.Width=tft->getXmax()-40;
  rc.Height=tft->getYmax()-40;

  tft->setForeground(ColourNames::RED);
  tft->fillRectangle(rc);
}

void loop() {
  
  // wait 3 seconds

  delay(3000);
  
  // fade out the backlight and go to sleep
  
  backlight->fadeTo(0,4);
  tft->sleep();

  // wait 2 seconds
  
  delay(2000);

  // wake up and fade back in

  tft->wake();
  backlight->fadeTo(100,4);  
}

