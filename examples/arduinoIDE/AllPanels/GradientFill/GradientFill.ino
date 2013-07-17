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


