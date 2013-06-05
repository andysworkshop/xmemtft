/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012,2013 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

#include "HardwareSerial.h"
#include "tftlib/Nokia6300.h"
#include "fft.h"

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

extern const uint32_t mp3PlayerOrigin;
extern const uint32_t mp3PlayerSize;
extern const uint32_t screenStripOrigin;
extern const uint32_t screenStripSize;

void plotSamples(uint8_t *currentChannels,uint8_t *lastChannels);
void getSamples(uint8_t *channels);

lcd::Bitmap bmBackground;


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

typedef lcd::Nokia6300_Landscape_262K LcdAccess;
LcdAccess *panel;

enum {
	CHANNELS=16
};


/*
 * Globals for the backlight
 */

DefaultBacklight *backlight;


void setup() {

	lcd::Bitmap bm;

	Serial.begin(9600);

	// create a backlight manager and switch off the backlight
	// so the user doesn't see the random data that can appear
	// during initialisation

	backlight=new DefaultBacklight;
	backlight->setPercentage(0);

	// create and initialise the panel and font

	panel=new LcdAccess;

	// clear down to white

	panel->setBackground(lcd::ColourNames::WHITE);
	panel->clearScreen();

	// the background gradient

  bmBackground.Dimensions.Width=10;
  bmBackground.Dimensions.Height=78;
  bmBackground.Pixels=GET_FAR_ADDRESS(screenStripOrigin);
  bmBackground.DataSize=GET_FAR_ADDRESS(screenStripSize);

  // the bar colour

  panel->setForeground(0x38808a);

	// load the bitmap

	bm.Dimensions.Width=316;
	bm.Dimensions.Height=200;
	bm.Pixels=GET_FAR_ADDRESS(mp3PlayerOrigin);
	bm.DataSize=GET_FAR_ADDRESS(mp3PlayerSize);

	panel->drawCompressedBitmap(lcd::Point(2,20),bm);

	// fade up the backlight to 100% in 4ms steps (400ms total)
	// now that we are in a known good state

	backlight->fadeTo(100,4);
}


void loop() {

	uint8_t channels1[CHANNELS],channels2[CHANNELS];

	memset(channels2,0,sizeof(channels2));

	for(;;) {

		getSamples(channels1);
		plotSamples(channels1,channels2);

		getSamples(channels2);
		plotSamples(channels2,channels1);
	}
}


void getSamples(uint8_t *channels) {

  int i,val;
  uint32_t now,last;
  char data[128],im[128];
  uint16_t newvalue;

  // capture 128 samples

  last=0;
  i=0;

  while(i<128) {

  	// get a sample (at best) each millisecond

  	if((now=millis())!=last) {

  		val=analogRead(0);
  		//val=rand() % 1000;

  		data[i]=val/4-128;
  		im[i]=0;

  		last=now;
  		i++;
  	}
  }

	// do the fft

	fix_fft(data,im,7,0);

	for(i=0;i<64;i++)
		data[i]=sqrt(data[i]*data[i]+im[i]*im[i]);

	// average down to 16 channels

	for(i=0;i<64;i+=4) {
		newvalue=((uint16_t)data[i]+(uint16_t)data[i+1]+(uint16_t)data[i+2]+(uint16_t)data[i+3])/4;
		channels[i/4]=min(78,newvalue*4);
	}
}


void plotSamples(uint8_t *channels,uint8_t *previous) {

	int16_t i;
	lcd::Rectangle rc;
	lcd::Bitmap bm;
	lcd::Point bmPoint(26,58);

	rc.X=26;
	rc.Width=10;

	for(i=0;i<CHANNELS;i++) {

		if(channels[i]!=previous[i]) {

			if(channels[i]<previous[i]) {

				panel->drawUncompressedBitmap(bmPoint,bmBackground);
				rc.Height=channels[i];
			}
			else {
				rc.Height=channels[i]-previous[i];
			}

			rc.Y=136-channels[i];
			panel->fillRectangle(rc);
		}

		rc.X+=11;
		bmPoint.X+=11;
	}
}
