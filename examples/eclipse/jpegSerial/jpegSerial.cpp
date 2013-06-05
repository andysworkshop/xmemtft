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


#include "tftlib/NokiaN82.h"
#include "tftlib/ColourNames.h"
#include "tftlib/Font_volter_goldfish_9.h"


using namespace lcd;



// We'll be working in portrait mode, 262K

typedef NokiaN82_Portrait_262K LcdAccess;
LcdAccess *tft;
DefaultBacklight *backlight;
Font *font;


uint32_t readJpegSize();


int main(void) {

	init();
	setup();

	for(;;)
		loop();

	return 0;  // not reached
}


void setup() {

	Serial.begin(1000000);

	// create a backlight manager and switch off the backlight
	// so the user doesn't see the random data that can appear
	// during initialisation

	backlight=new DefaultBacklight;
	backlight->setPercentage(0);

	// create and initialise the panel and font

	tft=new LcdAccess;
	font=new Font_VOLTER__28GOLDFISH_299;

	// clear to black

	tft->setBackground(ColourNames::BLACK);
	tft->setForeground(ColourNames::WHITE);
	tft->clearScreen();

	// fade up the backlight to 100% in 4ms steps (400ms total)
	// now that we are in a known good state

	backlight->fadeTo(100,4);

	// select the font used througout

	(*tft) << *font;
}


void loop() {

	int32_t jpegSize;

	tft->clearScreen();
	*tft << Point(0,tft->getYmax()-font->getHeight()) << "Awaiting jpeg file size";
	jpegSize=readJpegSize();

	tft->clearScreen();
	*tft << Point(0,tft->getYmax()-font->getHeight()) << "Receiving " << jpegSize << " bytes";

	JpegSerialDataSource ds(Serial,jpegSize,63);
	tft->drawJpeg(Point(0,0),ds);

	delay(5000);
}


uint32_t readJpegSize() {

	uint32_t size;

	while(Serial.readBytes(reinterpret_cast<char *>(&size),4)!=4);
	return size;
}
