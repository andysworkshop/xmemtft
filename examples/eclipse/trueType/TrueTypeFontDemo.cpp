/*
 * main.cpp
 *
 *  Created on: 8 Apr 2012
 *      Author: Andy
 */

#include "HardwareSerial.h"
#include "tftlib/NokiaN95_8Gb.h"
//#include "tftlib/Nokia6300.h"
//#include "tftlib/NokiaN82.h"
#include "ttgraphics/Lzg_font_happysans.h"
#include "ttgraphics/Lzg_font_applegaramond.h"

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

extern const uint32_t LogoPixels;
extern const uint32_t LogoPixelsSize;


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

//typedef Nokia6300_Landscape_262K_Gpio LcdAccess;
typedef NokiaN95_8Gb_Landscape_262K LcdAccess;
//typedef NokiaN82_Portrait_262K LcdAccess;

DefaultBacklight *backlight;
LcdAccess *tft;
LzgFont *happyFont;
LzgFont *garamondFont;


void setup() {

  // create a backlight controller and use it
  // to switch the backlight off

  backlight=new DefaultBacklight;
  backlight->setPercentage(0);

  // reset and initialise the panel

  tft=new LcdAccess;

  // clear the screen to white

  tft->setBackground(ColourNames::WHITE);
  tft->clearScreen();

  // create a terminal implementation

  happyFont=new Font_HAPPY_SANS_32;
  garamondFont=new Font_APPLE_GARAMOND_28;

  // fade up the backlight to 100% in 4ms steps (400ms total)

  backlight->fadeTo(100,4);
}



void intro() {

	Bitmap bm;

	bm.DataSize=GET_FAR_ADDRESS(LogoPixelsSize);
	bm.Pixels=GET_FAR_ADDRESS(LogoPixels);
	bm.Dimensions.Width=200;
	bm.Dimensions.Height=56;

	tft->drawCompressedBitmap(Point((tft->getWidth()-bm.Dimensions.Width)/2,(tft->getHeight()-bm.Dimensions.Height)/3),bm);
	delay(2000);

	tft->writeString(Point(160,145),*happyFont,"presents...");
	delay(3000);
}


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

	for(;;);
}


void loop() {

	intro();
	ttfonts();

	for(;;);
}
