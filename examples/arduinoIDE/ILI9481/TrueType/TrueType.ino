/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

#include "Generic16BitILI9481.h"
#include "Lzg_font_happysans.h"
#include "Lzg_font_applegaramond.h"

using namespace lcd;

extern const uint32_t LogoPixels;
extern const uint32_t LogoPixelsSize;

/*
 * The orientation and colour depth that we will use
 */

typedef ILI9481_Landscape_64K_Gpio LcdAccess;

DefaultBacklight *backlight;
LcdAccess *tft;
LzgFont *happyFont;
LzgFont *garamondFont;

/*
 * Set up the display and the fonts
 */
 
void setup() {

  // create a backlight controller and use it
  // to switch the backlight off

  backlight=new DefaultBacklight;
  backlight->setPercentage(0);

  // reset and initialise the panel

  tft=new LcdAccess;
  
  // set some gamma values for the panel (change or delete for your panel)

  ILI9481Gamma gamma(0,0xf3,0,0xbc,0x50,0x1f,0,7,0x7f,0x7,0xf,0);
  tft->applyGamma(gamma);

  // clear the screen to black

  tft->setBackground(ColourNames::BLACK);
  tft->clearScreen();

  // create the two TrueType fonts

  happyFont=new Font_HAPPY_SANS_32;
  garamondFont=new Font_APPLE_GARAMOND_28;

  // fade up the backlight to 100% in 4ms steps (400ms total)

  backlight->fadeTo(100,4);
}

/*
 * Show the intro graphic
 */
 
void intro() {

  Bitmap bm;

  // set up a bitmap data structure

  bm.DataSize=GET_FAR_ADDRESS(LogoPixelsSize);
  bm.Pixels=GET_FAR_ADDRESS(LogoPixels);
  bm.Dimensions.Width=200;
  bm.Dimensions.Height=56;

  // draw the bitmap on screen
  
  tft->drawCompressedBitmap(Point((tft->getWidth()-bm.Dimensions.Width)/2,(tft->getHeight()-bm.Dimensions.Height)/3),bm);
  delay(2000);

  // write a TrueType font string below the logo
  
  tft->writeString(Point(160,145),*happyFont,"presents...");
  delay(3000);
}


/*
 * Show some TrueType text strings
 */
 
void ttfonts() {

  int fontHeight;

  fontHeight=garamondFont->getHeight();

  tft->clearScreen();

  tft->writeString(Point(2,0),*garamondFont,"TrueType fonts on the Arduino!");
  delay(3000);

  tft->writeString(Point(20,10+fontHeight),*garamondFont,"Great for headings");
  delay(1000);

  tft->writeString(Point(20,10+fontHeight*2),*garamondFont,"Ideal for alerts");
  delay(1000);

  tft->writeString(Point(20,10+fontHeight*3),*garamondFont,"Perfect for impact");
  delay(2000);

  tft->writeString(Point(2,20+fontHeight*4),*garamondFont,"Most fonts are supported");
  delay(1000);

  tft->writeString(Point(2,20+fontHeight*5),*happyFont,"even fancy comic script!");
  delay(3000);
  tft->clearScreen();
}


/*
 * Main loop
 */
 
void loop() {

  intro();
  ttfonts();
}

