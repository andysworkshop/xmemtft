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

using namespace lcd;

typedef Nokia6300_Portrait_262K TftPanel;

TftPanel *tft;
DefaultBacklight *backlight;
Font *font;
int scrollPos,scrollDisp;


void setup() {

  int numRows,i;
  Point p;
  
  // create a backlight controller and use it
  // to switch the backlight off
  
  backlight=new DefaultBacklight;
  backlight->setPercentage(0);

  // reset and initialise the panel

  tft=new TftPanel;

  // create the font

  font=new Font_VOLTER__28GOLDFISH_299;

  // set scroll parameters
  
  tft->setForeground(ColourNames::WHITE);

  scrollPos=0;
  scrollDisp=1;

  // clear to black

  tft->setBackground(ColourNames::BLACK);
  tft->clearScreen();

  // fade up the backlight to 100% in 4ms steps (400ms total)

  backlight->fadeTo(100,4);

  // print the text

  numRows=((tft->getYmax()+1)/font->getHeight())/3;
  p.X=0;

  for(i=0;i<numRows;i++) {
    p.Y=(numRows+i)*font->getHeight();
    tft->writeString(p,*font,"Test text row");
  }
}

void loop() {

  tft->setScrollPosition(scrollPos);
  scrollPos+=scrollDisp;
  
  if(scrollPos==100)
    scrollDisp=-1;
  else if(scrollPos==0)
    scrollDisp=1;
    
  delay(5);
}


