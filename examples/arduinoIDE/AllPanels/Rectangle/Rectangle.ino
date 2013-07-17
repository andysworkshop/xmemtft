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

