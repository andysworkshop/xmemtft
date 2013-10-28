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

#include "Generic16BitR61523.h"
#include "Font_dos_16.h"
#include "Lzg_font_happysans.h"
#include "Lzg_font_applegaramond.h"

using namespace lcd;

extern const uint32_t CloudPixels;
extern const uint32_t CloudPixelsSize;
extern const uint32_t GlobePixelsSize,GlobePixels;
extern const uint32_t LogoPixels;
extern const uint32_t LogoPixelsSize;

/*
 * Declare types and variables for the panel and the backlight. We will
 * use the built-in PWM generation feature of the R61523 to dim the backlight.
 */

typedef R61523_Landscape_64K_Gpio16Latch TftPanel;
typedef R61523PwmBacklight<DefaultMegaGpio16LatchAccessMode> TftBacklight;

TftPanel *tft;
TftBacklight *backlight;

/*
 * Globals for the bitmap font and the two TrueType LZG compressed fonts
 */

Font *font;
LzgFont *happyFont;
LzgFont *garamondFont;


void setup() {

  // create a backlight manager. the default level is zero.

  backlight=new TftBacklight;

  // create and initialise the panel and font (the driver will clear it
  // to black before switching the display on)

  tft=new TftPanel;
  font=new Font_PERFECT_DOS_VGA_437_WIN16;

  // apply the gamma curve. Note that gammas are panel specific. This curve is appropriate
  // to a replacement (non-original) panel obtained from ebay.

  uint8_t levels[13]={ 0xe,0,1,1,0,0,0,0,0,0,3,4,0 };
  R61523Gamma gamma(levels);
  tft->applyGamma(gamma);

  // create the two TrueType fonts

  happyFont=new Font_HAPPY_SANS_32;
  garamondFont=new Font_APPLE_GARAMOND_28;

  // fade up the backlight to 100% - the fading is done automatically by
  // the R61523 hardware

  backlight->setPercentage(100);
  
  // select the font for the stream ops
  
  *tft << *font;
}


void loop() {

  // looping demo of the graphics library

  bmTest();
  lzgTest();
  trueTypeTest();
  gradientTest();
  rectTest();
  textTest();
  sleepTest();
  lineTest();
  ellipseTest();
  clearTest();
}

void gradientTest() {

  prompt("Gradient test");

  doGradientFills(true);
  doGradientFills(false);
}

void doGradientFills(bool horizontal) {

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

    tft->gradientFillRectangle(rc,horizontal ? HORIZONTAL : VERTICAL,ColourNames::BLACK,colours[i]);
    rc.Y=rc.Height;
    tft->gradientFillRectangle(rc,horizontal ? HORIZONTAL : VERTICAL,colours[i],ColourNames::BLACK);

    delay(2000);
  }
}

/*
 * Display a bouncing bitmap for 15 seconds
 */

void bmTest() {

  uint16_t x,y,width,height;
  uint32_t end;
  int8_t xdir,ydir;
  Bitmap bm;

  prompt("Bitmap test");

  bm.Dimensions.Width=100;
  bm.Dimensions.Height=100;
  bm.DataSize=GET_FAR_ADDRESS(CloudPixelsSize);
  bm.Pixels=GET_FAR_ADDRESS(CloudPixels);

  width=tft->getWidth();
  height=tft->getHeight();

  x=(width/2)-50;
  y=(height/2)-50;
  xdir=ydir=1;

  end=millis()+15000;
  while(millis()<end) {

    tft->drawUncompressedBitmap(Point(x,y),bm);
    x+=xdir;
    y+=ydir;

    if(x==width-100)
      xdir=-1;
    else if(x==0)
      xdir=1;

    if(y==height-100)
      ydir=-1;
    else if(y==0)
      ydir=1;
  }
}


/*
 * Display a selection of compressed bitmaps
 */

void lzgTest() {

  prompt("LZG bitmap test");
  drawCompressedBitmap(GET_FAR_ADDRESS(GlobePixels),GET_FAR_ADDRESS(GlobePixelsSize),193,219);
}

void drawCompressedBitmap(uint32_t pixelData,uint32_t pixelDataSize,uint16_t width,uint16_t height) {

  Bitmap bm;
  Point pos;

  tft->setBackground(ColourNames::WHITE);
  tft->clearScreen();

  bm.Pixels=pixelData;
  bm.DataSize=pixelDataSize;
  bm.Dimensions=Size(width,height);

  pos.X=(tft->getWidth()-width)/2;
  pos.Y=(tft->getHeight()-height)/2;

  tft->drawCompressedBitmap(pos,bm);
  delay(3000);
}


/*
 * Go to sleep for 3 seconds
 */

void sleepTest() {

  prompt("Sleep test");

  // go to sleep

  tft->writeString(Point(0,0),*font,"Sleeping now...");
  delay(1000);
  backlight->fadeTo(0,4);
  tft->sleep();
  delay(3000);

  // wake up

  tft->wake();
  tft->clearScreen();
  tft->writeString(Point(0,0),*font,"Woken up again...");
  backlight->fadeTo(100,4);
  delay(3000);
}


/*
 * Show randomly positioned text
 */

void textTest() {

  int i;
  const char *str="The quick brown fox";
  Size size;
  Point p;
  uint32_t start;

  prompt("Stream operators test");

  *tft << Point(0,0) << "Let's see PI:";

  for(i=0;i<=7;i++)
    *tft << Point(0,(1+i)*font->getHeight()) << DoublePrecision(3.1415926535,i);

  delay(5000);

  prompt("Text test");

  size=tft->measureString(*font,str);

  for(start=millis();millis()-start<5000;) {

    p.X=rand() % (tft->getXmax()-size.Width);
    p.Y=rand() % (tft->getYmax()-size.Height);

    tft->setForeground(randomColour());
    tft->writeString(p,*font,str);
  }
}

/*
 * Test the TrueType (LZG compressed) fonts
 */
 
void trueTypeTest() {

  Bitmap bm;
  int fontHeight;

  prompt("TrueType (LZG) font test");
 
  // set up a bitmap data structure

  bm.DataSize=GET_FAR_ADDRESS(LogoPixelsSize);
  bm.Pixels=GET_FAR_ADDRESS(LogoPixels);
  bm.Dimensions.Width=400;
  bm.Dimensions.Height=112;

  // draw the intro bitmap on screen
  
  tft->drawCompressedBitmap(Point((tft->getWidth()-bm.Dimensions.Width)/2,(tft->getHeight()-bm.Dimensions.Height)/3),bm);
  delay(2000);

  // write a TrueType font string below the logo
  
  tft->writeString(Point(120,240),*happyFont,"presents...");
  delay(3000);

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
}


/*
 * Clear down the screen to some fixed colours
 */

void clearTest() {

  uint32_t testColours[]= {
    ColourNames::BLUE,
    ColourNames::GREEN,
    ColourNames::RED,
    ColourNames::BLACK,
    ColourNames::WHITE,
    ColourNames::MAGENTA,
    ColourNames::CYAN,
    ColourNames::YELLOW
  };

  prompt("Clear screen test");

  for(uint16_t i=0;i<sizeof(testColours)/sizeof(testColours[0]);i++) {

    tft->setBackground(testColours[i]);
    tft->clearScreen();
    delay(500);
  }
}


/*
 * Show random rectangles, filled and outlined
 */

void rectTest() {

  int i;
  Rectangle rc;
  uint32_t start;
  
  prompt("Rectangle test");

  for(i=0,start=millis();millis()-start<5000;i++) {

    if(i % 500 ==0)
      tft->clearScreen();

    rc.X=(rand() % tft->getXmax()/2);
    rc.Y=(rand() % tft->getYmax()/2);
    rc.Width=rand() % (tft->getXmax()-rc.X);
    rc.Height=rand() % (tft->getYmax()-rc.Y);

    tft->setForeground(randomColour());
    tft->fillRectangle(rc);
  }

  tft->clearScreen();

  for(i=0,start=millis();millis()-start<5000;i++) {

    rc.X=(rand() % tft->getXmax()/2);
    rc.Y=(rand() % tft->getXmax()/2);
    rc.Width=rand() % (tft->getXmax()-rc.X);
    rc.Height=rand() % (tft->getYmax()-rc.Y);

    tft->setForeground(randomColour());
    tft->drawRectangle(rc);

    if(i % 500 ==0)
      tft->clearScreen();
  }
}


/*
 * Draw random lines in different colours
 */

void lineTest() {

  Point p1,p2;
  int i;
  uint32_t start;

  prompt("Line test");

  for(i=0,start=millis();millis()-start<5000;i++) {

    if(i % 1000==0)
      tft->clearScreen();

    p1.X=rand() % tft->getXmax();
    p1.Y=rand() % tft->getYmax();
    p2.X=rand() % tft->getXmax();
    p2.Y=rand() % tft->getYmax();

    tft->setForeground(randomColour());
    tft->drawLine(p1,p2);
  }
}


/*
 * Show random size filled and outlined ellipses
 */

void ellipseTest() {

  int16_t i;
  Point p;
  Size s;
  uint32_t start;

  prompt("Ellipse test");

  for(i=0,start=millis();millis()-start<5000;i++) {

    p.X=tft->getXmax()/4+(rand() % (tft->getXmax()/2));
    p.Y=tft->getYmax()/4+(rand() % (tft->getYmax()/2));

    if(p.X<tft->getXmax()/2)
      s.Width=rand() % p.X;
    else
      s.Width=rand() % (tft->getXmax()-p.X);

    if(p.Y<tft->getYmax()/2)
      s.Height=rand() % p.Y;
    else
      s.Height=rand() % (tft->getYmax()-p.Y);

    if(s.Height>0 && s.Width>0 && p.X+s.Width<tft->getXmax() && p.Y+s.Height<tft->getYmax()) {
      tft->setForeground(randomColour());
      tft->drawEllipse(p,s);
    }

    if(i % 500==0)
      tft->clearScreen();
  }

  tft->clearScreen();

  for(i=0,start=millis();millis()-start<5000;i++) {

    p.X=tft->getXmax()/4+(rand() % (tft->getXmax()/2));
    p.Y=tft->getYmax()/4+(rand() % (tft->getYmax()/2));

    if(p.X<tft->getXmax()/2)
      s.Width=rand() % p.X;
    else
      s.Width=rand() % (tft->getXmax()-p.X);

    if(p.Y<tft->getYmax()/2)
      s.Height=rand() % p.Y;
    else
      s.Height=rand() % (tft->getYmax()-p.Y);

    tft->setForeground(randomColour());
    tft->fillEllipse(p,s);
  }
}


/*
 * Pick a random 24-bit colour that's not too dark
 */

uint32_t randomColour() {

  return (((uint32_t)rand() << 16 | rand()) & 0xffffff) | 0x404040;
}


/*
 * Clear down the screen and show a prompt for 3 seconds
 */

void prompt(const char *prompt) {

  Size s;
  Point p;
  
  tft->setBackground(ColourNames::BLACK);
  tft->clearScreen();

  s=tft->measureString(*font,prompt);
  p.X=(tft->getWidth()/2)-(s.Width/2);
  p.Y=(tft->getHeight()/2)-(s.Height/2);

  tft->setForeground(ColourNames::WHITE);
  *tft << p << prompt;

  delay(3000);
  tft->clearScreen();
}

