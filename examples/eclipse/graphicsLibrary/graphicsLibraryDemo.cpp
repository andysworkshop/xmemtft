/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012,2013 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

#include "Arduino.h"
#include "Generic16BitILI481.h"
#include "Font_volter_goldfish_9.h"

using namespace lcd;

extern "C" void __cxa_pure_virtual() { for(;;); }


void *operator new(size_t size_,void *ptr_) {
	return ptr_;
}
void *operator new(size_t size_) {
	return malloc(size_);
}
void operator delete(void *ptr_) {
	free(ptr_);
}


extern void rectTest();
extern void lineTest();

void clearTest();
void gradientTest();
void sleepTest();
void clearTest();
void ellipseTest();
void textTest();
void scrollTest();
void bmTest();
void lzgTest();
void drawCompressedBitmap(uint32_t pixels,uint32_t size,uint16_t width,uint16_t height);
void prompt(const char *prompt);
void doGradientFills(bool horizontal);

uint32_t randomColour();

extern const uint32_t CloudPixels;
extern const uint32_t CloudPixelsSize;
extern const uint32_t GlobePixelsSize,GlobePixels;


int main(void) {

	init();
  setup();

  for(;;)
    loop();

  return 0; // not reached
}


/*
 * The orientation and colour depth that we will use
 */

typedef ILI9481_Portrait_64K_Gpio TftPanel;
TftPanel *tft;

/*
 * Globals for the backlight and the font
 */

DefaultBacklight *backlight;
Font *font;


void setup() {

  // create a backlight manager and switch off the backlight
  // so the user doesn't see the random data that can appear
  // during initialisation

  backlight=new DefaultBacklight;
  backlight->setPercentage(0);

  // create and initialise the panel and font

  tft=new TftPanel;
  font=new Font_VOLTER__28GOLDFISH_299;

  // clear to black

  tft->setBackground(ColourNames::BLACK);
  tft->clearScreen();

  // fade up the backlight to 100% in 4ms steps (400ms total)
  // now that we are in a known good state

  backlight->fadeTo(100,4);

  // select the font for the stream ops

  *tft << *font;
}


void loop() {

	tft->setForeground(ColourNames::WHITE);

	// looping demo of the graphics library
#if 1
	Point c(120,160);

	tft->drawLine(c,Point(0,0));
	tft->drawLine(c,Point(tft->getWidth()/2,0));
	tft->drawLine(c,Point(tft->getXmax(),0));
	tft->drawLine(c,Point(tft->getXmax(),tft->getHeight()/2));
	tft->drawLine(c,Point(tft->getXmax(),tft->getYmax()));
	tft->drawLine(c,Point(tft->getWidth()/2,tft->getYmax()));
	tft->drawLine(c,Point(0,tft->getYmax()));
	for(;;);

#endif


	//lineTest();
	lzgTest();
	for(;;);
//	bmTest();
//	rectTest();
//	scrollTest();
//	gradientTest();
//	clearTest();
//	textTest();
//	sleepTest();
//	ellipseTest();
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

    delay(1000);
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
    rc.Y=(rand() % tft->getXmax()/2);
    rc.Width=rand() % (tft->getXmax()-rc.X);
    rc.Height=rand() % (tft->getYmax()-rc.Y);

    if(rc.Height && rc.Width) {
    	tft->setForeground(randomColour());
    	tft->fillRectangle(rc);
    }
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

  srand(0);
  for(i=0,start=millis();millis()-start<5000;i++) {

    p1.X=rand() % tft->getXmax();
    p1.Y=rand() % tft->getYmax();
    p2.X=rand() % tft->getXmax();
    p2.Y=rand() % tft->getYmax();

    tft->setForeground(randomColour());
    tft->drawLine(p1,p2);
  }

  tft->setForeground(ColourNames::WHITE);
  tft->clearScreen();
  *tft << Point::Origin << i << " lines in 5 seconds";
  delay(3000);
}


/*
 * Show random size filled and outlined ellipses
 */

void ellipseTest() {

  int16_t i;
  Point p;
  uint32_t start;
  Size s;

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

  for(i=0;i<1000;i++) {

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
 * Use the hardware scrolling to show some text moving
 * up and down
 */

void scrollTest() {

  int i,j,numRows;
  Point p;

  prompt("Hardware scrolling test");

  numRows=((tft->getYmax() + 1) / font->getHeight()) / 3;
  p.X=0;

  for(i=0;i < numRows;i++) {
    p.Y=(numRows+i)*font->getHeight();
    tft->writeString(p,*font,"Test text row");
  }

  for(j=0;j<15;j++) {

    numRows=(tft->getYmax()+1)/4;

    for(i=0;i<numRows;i++) {
      tft->setScrollPosition(i);
      delay(5);
    }

    for(i=0;i<numRows;i++) {
      tft->setScrollPosition(numRows-i);
      delay(5);
    }
  }

  // reset for the next demo

  tft->setScrollPosition(0);
}


/*
 * Pick a random 24-bit colour
 */

uint32_t randomColour() {

  return ((uint32_t)rand() << 16 | rand()) & 0xffffff;
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
