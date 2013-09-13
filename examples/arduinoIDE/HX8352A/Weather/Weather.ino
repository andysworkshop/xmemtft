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
  Please respect the rights of the original authors of the weather images
  used in this demo code:
 
  http://en.wikipedia.org/wiki/File:Nuvola_weather_snow.svg
  http://commons.wikimedia.org/wiki/File:Crystal_Project_kweather.png
  http://commons.wikimedia.org/wiki/File:Weather-drizzle.svg
  http://commons.wikimedia.org/wiki/File:Sun.svg
 */

#include "Generic16BitHX8352A.h"

using namespace lcd;

// declare an indexable structure of important bitmap data

static struct BitmapInfo {
  uint8_t width;
  uint32_t pixels;
  uint32_t pixelsSize;
} bitmapInfo[12];


// Arduino IDE bug workaround for any function that takes a namespaced parameter.
// The broken auto-prototype generator will stuff its "output" directly after includes
// and before you can get a "using namespace" statement in then goes and stupidly
// fails to do anything if the parameter list contains an explicit namespace.
// <sigh>. Again.

void showSummary(uint32_t pixelData,uint32_t pixelDataSize,const lcd::Size& size);
void writeBitmap(const BitmapInfo *bmInfo,const lcd::Point& position);
void weather(uint32_t pixelData,uint32_t pixelDataSize,const lcd::Size& size,uint16_t startingTemp);


// Graphics compiled in to flash

extern const uint32_t RainPixels,RainPixelsSize;
extern const uint32_t SunPixels,SunPixelsSize;
extern const uint32_t PartlyCloudyPixels,PartlyCloudyPixelsSize;
extern const uint32_t SnowPixels,SnowPixelsSize;
extern const uint32_t PointPixels,PointPixelsSize;
extern const uint32_t DegreePixels,DegreePixelsSize;
extern const uint32_t OnePixels,OnePixelsSize;
extern const uint32_t TwoPixels,TwoPixelsSize;
extern const uint32_t ThreePixels,ThreePixelsSize;
extern const uint32_t FourPixels,FourPixelsSize;
extern const uint32_t FivePixels,FivePixelsSize;
extern const uint32_t SixPixels,SixPixelsSize;
extern const uint32_t SevenPixels,SevenPixelsSize;
extern const uint32_t EightPixels,EightPixelsSize;
extern const uint32_t NinePixels,NinePixelsSize;
extern const uint32_t ZeroPixels,ZeroPixelsSize;

enum {
  POINT_INDEX = 10,
  DEGREE_INDEX = 11,

  TEMPERATURE_Y = 256,
  TEMPERATURE_HEIGHT = 48,
  DIGIT_SPACING = 3
};


// We'll be working in portrait mode, 64K

typedef LG_KF700_Portrait_64K_Gpio16Latch LcdAccess;
LcdAccess *tft;
DefaultBacklight *backlight;


void setup() {

  // the bitmap info structure for the digits have to be set
  // manually in code because of the GET_FAR_ADDRESS calls

  bitmapInfo[0].width=31;
  bitmapInfo[0].pixels=GET_FAR_ADDRESS(ZeroPixels);
  bitmapInfo[0].pixelsSize=GET_FAR_ADDRESS(ZeroPixelsSize);

  bitmapInfo[1].width=19;
  bitmapInfo[1].pixels=GET_FAR_ADDRESS(OnePixels);
  bitmapInfo[1].pixelsSize=GET_FAR_ADDRESS(OnePixelsSize);

  bitmapInfo[2].width=29;
  bitmapInfo[2].pixels=GET_FAR_ADDRESS(TwoPixels);
  bitmapInfo[2].pixelsSize=GET_FAR_ADDRESS(TwoPixelsSize);

  bitmapInfo[3].width=28;
  bitmapInfo[3].pixels=GET_FAR_ADDRESS(ThreePixels);
  bitmapInfo[3].pixelsSize=GET_FAR_ADDRESS(ThreePixelsSize);

  bitmapInfo[4].width=29;
  bitmapInfo[4].pixels=GET_FAR_ADDRESS(FourPixels);
  bitmapInfo[4].pixelsSize=GET_FAR_ADDRESS(FourPixelsSize);

  bitmapInfo[5].width=27;
  bitmapInfo[5].pixels=GET_FAR_ADDRESS(FivePixels);
  bitmapInfo[5].pixelsSize=GET_FAR_ADDRESS(FivePixelsSize);

  bitmapInfo[6].width=29;
  bitmapInfo[6].pixels=GET_FAR_ADDRESS(SixPixels);
  bitmapInfo[6].pixelsSize=GET_FAR_ADDRESS(SixPixelsSize);

  bitmapInfo[7].width=29;
  bitmapInfo[7].pixels=GET_FAR_ADDRESS(SevenPixels);
  bitmapInfo[7].pixelsSize=GET_FAR_ADDRESS(SevenPixelsSize);

  bitmapInfo[8].width=30;
  bitmapInfo[8].pixels=GET_FAR_ADDRESS(EightPixels);
  bitmapInfo[8].pixelsSize=GET_FAR_ADDRESS(EightPixelsSize);

  bitmapInfo[9].width=30;
  bitmapInfo[9].pixels=GET_FAR_ADDRESS(NinePixels);
  bitmapInfo[9].pixelsSize=GET_FAR_ADDRESS(NinePixelsSize);

  bitmapInfo[10].width=8;
  bitmapInfo[10].pixels=GET_FAR_ADDRESS(PointPixels);
  bitmapInfo[10].pixelsSize=GET_FAR_ADDRESS(PointPixelsSize);

  bitmapInfo[11].width=14;
  bitmapInfo[11].pixels=GET_FAR_ADDRESS(DegreePixels);
  bitmapInfo[11].pixelsSize=GET_FAR_ADDRESS(DegreePixelsSize);

  // seed the PRNG

  randomSeed(analogRead(0));

  // create a backlight manager and switch off the backlight
  // so the user doesn't see the random data that can appear
  // during initialisation

  backlight=new DefaultBacklight;
  backlight->setPercentage(0);

  // create and initialise the panel

  tft=new LcdAccess;

  // clear to white

  tft->setBackground(ColourNames::WHITE);
  tft->setForeground(ColourNames::WHITE);

  tft->clearScreen();

  // fade up the backlight to 100% in 4ms steps (400ms total)
  // now that we are in a known good state

  backlight->fadeTo(100,4);
}


void loop() {

  weather(GET_FAR_ADDRESS(SunPixels),GET_FAR_ADDRESS(SunPixelsSize),Size(185,184),320);
  weather(GET_FAR_ADDRESS(PartlyCloudyPixels),GET_FAR_ADDRESS(PartlyCloudyPixelsSize),Size(200,200),235);
  weather(GET_FAR_ADDRESS(RainPixels),GET_FAR_ADDRESS(RainPixelsSize),Size(200,196),143);
  weather(GET_FAR_ADDRESS(SnowPixels),GET_FAR_ADDRESS(SnowPixelsSize),Size(175,188),15);
}


void weather(uint32_t pixelData,uint32_t pixelDataSize,const lcd::Size& size,uint16_t startingTemp) {

  int i;

  // show a summary of the weather conditions

  showSummary(pixelData,pixelDataSize,size);

  // show a ticking temperature readout for 10 secs

  for(i=0;i<10;i++) {

    showTemperature(startingTemp);
    adjustTemperature(startingTemp);

    delay(1000);
  }
}


void showSummary(uint32_t pixelData,uint32_t pixelDataSize,const lcd::Size& size) {

  static Rectangle lastSummaryRect=Rectangle();
  Bitmap bm;

  // if this is not the first time through, erase the previous summary

  if(lastSummaryRect.X!=0)
    tft->fillRectangle(lastSummaryRect);

  // position the bitmap horizontally in the center and show it

  lastSummaryRect.X=(tft->getWidth()-size.Width)/2;
  lastSummaryRect.Y=20;
  lastSummaryRect.Width=size.Width;
  lastSummaryRect.Height=size.Height;

  bm.DataSize=pixelDataSize;
  bm.Pixels=pixelData;
  bm.Dimensions=size;

  tft->drawCompressedBitmap(lastSummaryRect.getTopLeft(),bm);
}


void showTemperature(uint16_t temperature) {

  // use this to erase the used area next time through

  static Rectangle lastReadoutRect=Rectangle();

  const BitmapInfo *first,*second,*third;
  Rectangle readoutRect;

  // we will show the temperature as 3 digits (2.1 format)
  // eg 312 = 31.2
  // a zero in the first digit (10's) is not displayed

  if(temperature<100)
    first=NULL;
  else
    first=&bitmapInfo[temperature/100];

  temperature-=(temperature/100)*100;

  second=&bitmapInfo[temperature/10];
  temperature-=(temperature/10)*10;

  third=&bitmapInfo[temperature];

  // now we know what the size is going to be
  // the height is always 48
  // the inter-character space is 3

  readoutRect.Width=(first==NULL ? 0 : first->width+DIGIT_SPACING)+    // first digit, if any
                     second->width+DIGIT_SPACING+                      // second digit
                     bitmapInfo[POINT_INDEX].width+DIGIT_SPACING+      // decimal point
                     third->width+DIGIT_SPACING+                       // third digit
                     bitmapInfo[DEGREE_INDEX].width;                   // degree symbol

  readoutRect.Height=TEMPERATURE_HEIGHT;

  // now we know the size, we can also calculate the position
  // we'll place the temperature readout in the center of
  // the display area below the summary image

  readoutRect.X=(240-readoutRect.Width)/2;
  readoutRect.Y=TEMPERATURE_Y;                                // summary height = 200, margin = 26

  // as an optimisation, we don't white-out the drawing area completely to avoid
  // a tiny but noticeable flash. We clear only what's needed and overwrite the
  // remainder with the new pixels.

  // this will clear any strip to the left of where we're about to draw

  if(lastReadoutRect.X>0 && readoutRect.Width<lastReadoutRect.Width)
    tft->fillRectangle(Rectangle(lastReadoutRect.X,TEMPERATURE_Y,readoutRect.X-lastReadoutRect.X,TEMPERATURE_HEIGHT));

  // blit out the bitmaps

  Point position(readoutRect.getTopLeft());

  if(first!=NULL) {
    writeBitmap(first,position);
    position.X+=first->width+DIGIT_SPACING;
  }

  writeBitmap(second,position);
  position.X+=second->width+DIGIT_SPACING;

  writeBitmap(&bitmapInfo[POINT_INDEX],position);
  position.X+=bitmapInfo[POINT_INDEX].width+DIGIT_SPACING;

  writeBitmap(third,position);
  position.X+=third->width+DIGIT_SPACING;

  writeBitmap(&bitmapInfo[DEGREE_INDEX],position);
  position.X+=bitmapInfo[DEGREE_INDEX].width;

  // if we've stopped short of where the previous run finished drawing then
  // we need to clear that strip down to white

  if(lastReadoutRect.X>0 && readoutRect.Width<lastReadoutRect.Width)
    tft->fillRectangle(Rectangle(position.X,TEMPERATURE_Y,lastReadoutRect.Right()-readoutRect.Right(),TEMPERATURE_HEIGHT));

  // now we're all set for the next run through this function

  lastReadoutRect=readoutRect;
}


void writeBitmap(const BitmapInfo *bmInfo,const lcd::Point& position) {

  Bitmap bm;

  bm.Pixels=bmInfo->pixels;
  bm.DataSize=bmInfo->pixelsSize;
  bm.Dimensions=Size(bmInfo->width,TEMPERATURE_HEIGHT);

  tft->drawCompressedBitmap(position,bm);

  // clear the inter-character margin

  tft->fillRectangle(Rectangle(position.X+bmInfo->width,TEMPERATURE_Y,DIGIT_SPACING,TEMPERATURE_HEIGHT));
}


void adjustTemperature(uint16_t& temperature) {

  int16_t step;
  
  while((step=(int16_t)random(4)-2)==0);
  temperature+=step;
}

