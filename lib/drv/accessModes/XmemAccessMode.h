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

/**
 * @file XmemAccessMode.h
 * @ingroup AccessModes
 * @brief The access mode for 8-bit XMEM access to an 8-bit panel.
 */

#pragma once

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)


namespace lcd {

  /**
   * @brief Access mode LCD that can be addressed over the XMEM interface.
   *
   * Here's the port mapping:
   *
   *  +---------+------+----------+
   *  | Arduino | Port | Function |
   *  +---------+------+----------+
   *  | 22      | PA0  | D0       |
   *  | 23      | PA1  | D1       |
   *  | 24      | PA2  | D2       |
   *  | 25      | PA3  | D3       |
   *  | 26      | PA4  | D4       |
   *  | 27      | PA5  | D5       |
   *  | 28      | PA6  | D6       |
   *  | 29      | PA7  | D7       |
   *  | 34      | PC3  | VIO      |  (not used in new designs)
   *  | 35      | PC2  | VDD      |  (not used in new designs)
   *  | 36      | PC1  | A9 (1)   |
   *  | 37      | PC0  | RS       |
   *  | 38      | PD7  | /RESET   |
   *  | 39      | PG2  | /CS      |
   *  | 40      | PG1  | /RD (2)  |
   *  | 41      | PG0  | /WR      |
   *  +---------+------+----------+
   *
   *  XMEM pins free'd for GPIO: 30,31,32,33,34,35 (PC2..PC7)
   *
   *  (1) A9 is not used but cannot be released for GPIO.
   *  (2) /RD is not used but cannot be released for GPIO and is pulled up to VIO.
   *
   *  Note: From experience VIO/VDD do not need to be brought up in order. It has proved
   *  safe to wire them direct to 3.3V.
   *  @ingroup AccessModes
   */

  class XmemAccessMode {

    public:

      /**
       * Define the non-XMEM pins that we'll need to use
       */

      enum {
        RESET_PIN = 38,         ///< RESET GPIO pin
        VIO_PIN = 34,           ///< not used in new designs
        VDD_PIN = 35            ///< not used in new designs
      };

    public:
      static void initialise();
      static void hardReset();

      static void writeCommand(uint8_t command) __attribute((always_inline));
      static void writeData(uint8_t data) __attribute((always_inline));
      static void writeStreamedData(uint8_t data) __attribute((always_inline));
  };


  /**
   * Write a command to the XMEM interface
   * @param command The 8-bit command to write
   */

  inline void XmemAccessMode::writeCommand(uint8_t command) {
    *reinterpret_cast<volatile uint8_t *>(0x8000)=command;
  }


  /**
   * Write a data value to the XMEM interface
   * @param data The 8-bit data value to write
   */

  inline void XmemAccessMode::writeData(uint8_t data) {
    *reinterpret_cast<volatile uint8_t *>(0x8100)=data;
  }


  /**
   * Streamed data is exactly the same as single data because this is an
   * 8-bit interface. Just write it out.
   * @param data The data value to write
   */

  inline void XmemAccessMode::writeStreamedData(uint8_t data) {
    *reinterpret_cast<volatile uint8_t *>(0x8100)=data;
  }


  /**
   * Enable the XMEM interface so we can talk to the panel through
   * direct memory addressing. data off the Arduino Mega.
   */

  inline void XmemAccessMode::initialise() {

    // set up the reset pin

    pinMode(RESET_PIN,OUTPUT);
    digitalWrite(RESET_PIN,HIGH);

    // set up the supply pins

    pinMode(VIO_PIN,OUTPUT);
    pinMode(VDD_PIN,OUTPUT);

    // power off

    digitalWrite(VDD_PIN,LOW);
    digitalWrite(VIO_PIN,LOW);

    // set up the xmem registers

    XMCRB=_BV(XMM2) | _BV(XMM1);    // free PC2..PC7 for GPIO
    XMCRA=_BV(SRE);                 // enable xmem, no wait states

    // power on, VIO first

    delay(100);
    digitalWrite(VIO_PIN,HIGH);
    delay(50);
    digitalWrite(VDD_PIN,HIGH);
    delay(50);
  }


  /**
   * Perform a hard reset. RESET is held low for 10 ms.
   */

  inline void XmemAccessMode::hardReset() {

    // pull reset low for 10ms

    digitalWrite(RESET_PIN,LOW);
    delay(10);
    digitalWrite(RESET_PIN,HIGH);
    delay(130);
  }
};


#endif
