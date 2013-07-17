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

#include "Generic16BitILI9327.h"
#include "Lzg_font_happysans.h"
#include "Lzg_font_applegaramond.h"

using namespace lcd;

extern const uint32_t LogoPixels;
extern const uint32_t LogoPixelsSize;

/*
 * The orientation and colour depth that we will use
 */

typedef ILI9327_400x240_Landscape_64K_Gpio16Latch LcdAccess;

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

