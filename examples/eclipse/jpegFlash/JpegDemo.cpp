/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012,2013 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 *
 * Please respect the rights of the original authors of the weather images
 * used in this demo code:
 *
 * http://en.wikipedia.org/wiki/File:Nuvola_weather_snow.svg
 * http://commons.wikimedia.org/wiki/File:Crystal_Project_kweather.png
 * http://commons.wikimedia.org/wiki/File:Weather-drizzle.svg
 * http://commons.wikimedia.org/wiki/File:Sun.svg
 */


#include "tftlib/Nokia6300.h"
//#include "tftlib/NokiaN95_8Gb.h"
//#include "tftlib/NokiaN93.h"


using namespace lcd;


static void showJpeg(uint32_t pixelData,uint32_t pixelDataSize,bool fade);


// Graphics compiled in to flash

extern const uint32_t Test0Pixels,Test0PixelsSize;
extern const uint32_t Test1Pixels,Test1PixelsSize;
extern const uint32_t Test2Pixels,Test2PixelsSize;
extern const uint32_t Test3Pixels,Test3PixelsSize;
extern const uint32_t Test4Pixels,Test4PixelsSize;

// We'll be working in portrait mode, 262K

typedef Nokia6300_Portrait_262K LcdAccess;
LcdAccess *tft;
DefaultBacklight *backlight;


int main(void) {

	init();
	setup();

	for(;;)
		loop();

	return 0;  // not reached
}


void setup() {

	// create a backlight manager and switch off the backlight
	// so the user doesn't see the random data that can appear
	// during initialisation

	backlight=new DefaultBacklight;
	backlight->setPercentage(0);

	// create and initialise the panel

	tft=new LcdAccess;

	// clear to white

	tft->setBackground(ColourNames::WHITE);
	tft->clearScreen();

	// fade up the backlight to 100% in 4ms steps (400ms total)
	// now that we are in a known good state

	backlight->fadeTo(100,4);
}


void loop() {

	// show the demo with no fade out/in between frames

	showJpeg(GET_FAR_ADDRESS(Test0Pixels),GET_FAR_ADDRESS(Test0PixelsSize),false);
	showJpeg(GET_FAR_ADDRESS(Test1Pixels),GET_FAR_ADDRESS(Test1PixelsSize),false);
	showJpeg(GET_FAR_ADDRESS(Test2Pixels),GET_FAR_ADDRESS(Test2PixelsSize),false);
	showJpeg(GET_FAR_ADDRESS(Test3Pixels),GET_FAR_ADDRESS(Test3PixelsSize),false);
	showJpeg(GET_FAR_ADDRESS(Test4Pixels),GET_FAR_ADDRESS(Test4PixelsSize),false);

	// show the demo with fade out/in between frames

	showJpeg(GET_FAR_ADDRESS(Test0Pixels),GET_FAR_ADDRESS(Test0PixelsSize),true);
	showJpeg(GET_FAR_ADDRESS(Test1Pixels),GET_FAR_ADDRESS(Test1PixelsSize),true);
	showJpeg(GET_FAR_ADDRESS(Test2Pixels),GET_FAR_ADDRESS(Test2PixelsSize),true);
	showJpeg(GET_FAR_ADDRESS(Test3Pixels),GET_FAR_ADDRESS(Test3PixelsSize),true);
	showJpeg(GET_FAR_ADDRESS(Test4Pixels),GET_FAR_ADDRESS(Test4PixelsSize),true);
}


void showJpeg(uint32_t pixelData,uint32_t pixelDataSize,bool fade) {

	// fade down the lights if we're doing that

	if(fade)
		backlight->fadeTo(0,5);

  // draw the image

  JpegFlashDataSource ds(pixelData,pixelDataSize);
  tft->drawJpeg(Point(0,0),ds);

	// fade up the lights

	if(fade)
		backlight->fadeTo(100,5);

	// pause for appreciation :)

	delay(5000);
}
