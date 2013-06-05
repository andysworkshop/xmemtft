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
  
  Size s;
  Point p;

  // draw an outline of ellipse around the edge
  
  p.X=(tft->getXmax()+1)/2;
  p.Y=(tft->getYmax()+1)/2;
  s.Width=((tft->getXmax()+1)/2)-1;
  s.Height=((tft->getYmax()+1)/2)-1;
  
  tft->setForeground(ColourNames::GOLDENROD);
  tft->drawEllipse(p,s);
  
  // fill a circle in the center
  
  tft->setForeground(ColourNames::INDIANRED1);
  tft->fillEllipse(p,Size(100,100));
  
  // finished
  
  for(;;);
}

