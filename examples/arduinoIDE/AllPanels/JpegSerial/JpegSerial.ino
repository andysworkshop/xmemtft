/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

#include "NokiaN82.h"
#include "Font_volter_goldfish_9.h"

using namespace lcd;

// We'll be working in portrait mode, 262K

typedef NokiaN82_Portrait_262K LcdAccess;
LcdAccess *tft;
DefaultBacklight *backlight;
Font *font;


void setup() {

  // 1Mb/s serial rate
  
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

  *tft << *font;
}


void loop() {

  int32_t jpegSize;

  // show a prompt and wait for the file size to arrive

  tft->clearScreen();
  *tft << Point(0,tft->getYmax()-font->getHeight())
       << "Awaiting jpeg file size";

  jpegSize=readJpegSize();

  // show a new prompt and receive the jpeg data

  tft->clearScreen();
  *tft << Point(0,tft->getYmax()-font->getHeight()) 
       << "Receiving " << jpegSize << " bytes";

  // 63 is the size of each data chunk that we receive
  // before sending an ack back to the sender. The
  // size should be less than the receive ring buffer
  // capacity (64 on the mega, 16 on the standard)

  JpegSerialDataSource ds(Serial,jpegSize,63);
  tft->drawJpeg(Point(0,0),ds);

  // wait 5 seconds and then go around and read
  // another file

  delay(5000);
}


uint32_t readJpegSize() {

  uint32_t size;

  // read directly on to the 4-byte size. that implies
  // that the data must be sent little-endian (LSB first)

  while(Serial.readBytes(reinterpret_cast<char *>(&size),4)!=4);
  return size;
}

