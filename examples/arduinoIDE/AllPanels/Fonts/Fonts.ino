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

