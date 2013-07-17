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
#include "Font_volter_goldfish_9.h"
//#include "Font_apple.h"    // fixed width
//#include "Font_kyrou9_regular_8.h"
//#include "Font_kyrou9_bold_8.h"
//#include "Font_tama_ss01.h"

using namespace lcd;

typedef Nokia6300_Portrait_262K TftPanel;

TftPanel *tft;
DefaultBacklight *backlight;
Font *font;

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
  
  // create the font to use later

  font=new Font_VOLTER__28GOLDFISH_299;
  // font=new Font_APPLE8;
  // font=new Font_KYROU_9_REGULAR8;
  // font=new Font_KYROU_9_REGULAR_BOLD8;
  // font=new Font_TAMA_SS0117;
  
  // select the font so we can use the
  // streaming operators
  
  *tft << *font;
}


void loop() {
	
  int i;
  const char *str="The quick brown fox";
  Size size;
  Point p;
  TftPanel::TColour randomColour;
  
  size=tft->measureString(*font,str);

  for(i=0;i<3000;i++) {
    p.X=rand() % (tft->getXmax()-size.Width);
    p.Y=rand() % (tft->getYmax()-size.Height);

    randomColour=(((uint32_t)rand() << 16) | rand()) & 0xffffff;

    tft->setForeground(randomColour);

    *tft << p << str;
  }
}

