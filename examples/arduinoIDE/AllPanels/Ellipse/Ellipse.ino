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

