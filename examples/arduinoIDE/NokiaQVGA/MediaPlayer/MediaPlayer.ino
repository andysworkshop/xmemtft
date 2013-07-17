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

#include "Nokia6300.h"

using namespace lcd;
 
// the bitmaps we'll use

extern const uint32_t mediaPlayerOrigin;
extern const uint32_t mediaPlayerSize;
extern const uint32_t screenStripOrigin;
extern const uint32_t screenStripSize;

// set up in Landscape mode 
 
typedef Nokia6300_Landscape_262K TftPanel;
 
TftPanel *tft;
DefaultBacklight *backlight;
Bitmap bmBack;

// the FFT funciton

extern int fix_fft(char fr[],char fi[],int m,int inverse);

// constants used here

enum {
  CHANNELS=16
};


void setup() {
  
  Bitmap bm;

  // create a backlight manager and switch off the backlight
  // so the user doesn't see the random data that can appear
  // during initialisation

  // create a backlight controller and use it
  // to switch the backlight off
 
  backlight=new DefaultBacklight;
  backlight->setPercentage(0);
 
  // reset and initialise the panel
 
  tft=new TftPanel;
 
  // clear to black
 
  tft->setBackground(ColourNames::WHITE);
  tft->clearScreen();
 
  // the background gradient

  bmBack.Dimensions.Width=10;
  bmBack.Dimensions.Height=78;
  bmBack.Pixels=GET_FAR_ADDRESS(screenStripOrigin);
  bmBack.DataSize=GET_FAR_ADDRESS(screenStripSize);

  // the bar colour
  
  tft->setForeground(0x38808a);

 // load the media player background

  bm.Dimensions.Width=316;
  bm.Dimensions.Height=200;
  bm.Pixels=GET_FAR_ADDRESS(mediaPlayerOrigin);
  bm.DataSize=GET_FAR_ADDRESS(mediaPlayerSize);
  
  tft->drawCompressedBitmap(Point(2,20),bm);

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
      
      data[i]=(val/4)-128;
      im[i]=0;

      last=now;
      i++;
    }
  }

  // do the fft

  fix_fft(data,im,7,0);

  // compute the amplitude
  
  for(i=0;i<64;i++)
    data[i]=sqrt(data[i]*data[i]+im[i]*im[i]);

  // average down to 16 channels and scale the amplitude

  for(i=0;i<64;i+=4) {

    newvalue=((uint16_t)data[i]+
              (uint16_t)data[i+1]+
              (uint16_t)data[i+2]+
              (uint16_t)data[i+3])/4;

    channels[i/4]=min(78,newvalue*4);
  }
}


void plotSamples(uint8_t *channels,uint8_t *previous) {

  int16_t i;
  Rectangle rc;
  Point bmPoint(26,58);

  rc.X=26;
  rc.Width=10;

  for(i=0;i<CHANNELS;i++) {
    if(channels[i]!=previous[i]) {
      if(channels[i]<previous[i]) {

        // replace the gradient background behind the bar
        // because we need to show a shorter bar
        
        tft->drawUncompressedBitmap(bmPoint,bmBack);

        // the new bar will be this tall

        rc.Height=channels[i];
      }
      else {
        
        // the new bar is taller, we fill up from the
        // previous to the new height
        
        rc.Y=136-channels[i];
        rc.Height=channels[i]-previous[i];
      }
      
      // draw the new bar
      
      rc.Y=136-channels[i];
      tft->fillRectangle(rc);
    }

    rc.X+=11;
    bmPoint.X+=11;
  }
}

