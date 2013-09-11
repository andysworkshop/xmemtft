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
 * @file Xmem16AccessMode.h
 * @ingroup AccessModes
 * @brief The access mode for 8-bit XMEM access to a 16-bit panel using a latch.
 */


#pragma once

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)


namespace lcd {

  /**
   * @brief Access mode for a 16-bit LCD that can be addressed over the XMEM interface using a latch.
   *
   * A latch is used to multiplex the 8 available AVR lines up to the 16 lines required by the LCD.
   * LCD D0..7 are driven first from the AVR A0..7 address bits. The latch is then locked and D8..15
   * are driven from the AVR D0..7 lines.
   *
   * The pin mappings below reflect that design and include the additional control lines and others
   * provided by my adaptor board (http://www.andybrown.me.uk)
   *
   *  +---------+------+----------+
   *  | Arduino | Port | Function |
   *  +---------+------+----------+
   *  | 22      | PA0  | D0/D8    |
   *  | 23      | PA1  | D1/D9    |
   *  | 24      | PA2  | D2/D10   |
   *  | 25      | PA3  | D3/D11   |
   *  | 26      | PA4  | D4/D12   |
   *  | 27      | PA5  | D5/D13   |
   *  | 28      | PA6  | D6/D14   |
   *  | 29      | PA7  | D7/D15   |
   *  | 35      | PC2  | /RESET   |
   *  | 37      | PC0  | RS       |
   *  | 39      | PG2  | /CS      |
   *  | 41      | PG0  | /WR      |
   *  +---------+------+----------+
   *
   *  XMEM pins free'd for GPIO: 30,31,32,33,34 (PC3..PC7)
   *
   *  (1) A9 (pin 36) is not used but cannot be released for GPIO.
   *  (2) /RD (pin 40) is not used but cannot be released for GPIO
   *
   *  Performance is critical here so the important parts are written in assembly language and the
   *  compiler is given every encouragement to place the instructions inline and use the most
   *  efficient calling conventions.
   *
   *  @ingroup AccessModes
   */

  class Xmem16AccessMode {

    public:

      /**
       * Define the non-XMEM pins that we'll need to use
       */

      enum {
        RESET_PIN = 35        ///< reset is on pin #35
      };

    protected:
      static uint8_t _streamIndex;
      static uint8_t _streamByte;

    public:
      static void initialise();
      static void hardReset();

      static void writeCommand(uint8_t lo8,uint8_t hi8=0);
      static void writeCommandData(uint8_t cmd,uint8_t lo8,uint8_t hi8=0);
      static void writeData(uint8_t lo8,uint8_t hi8=0);
      static void writeDataAgain(uint8_t lo8,uint8_t hi8=0);
      static void writeMultiData(uint32_t howMuch,uint8_t lo8,uint8_t hi8=0);
      static void writeStreamedData(uint8_t data);
  };


  /**
   * Shortcut to write an 8-bit command and an 8-bit data parameter. This is a common scenario
   * in programming the registers
   * @param cmd The 8-bit command to write.
   * @param lo8 The low 8 bits of the command to write.
   * @param hi8 The high 8 bits of the command to write. Many commands are 8-bits so this parameters defaults to zero.
   */

  inline void Xmem16AccessMode::writeCommandData(uint8_t cmd,uint8_t lo8,uint8_t hi8) {

    writeCommand(cmd,0);
    writeData(lo8,hi8);
  }


  /**
   * Write a command to the XMEM interface
   * @param lo8 The low 8 bits of the command to write
   * @param hi8 The high 8 bits of the command to write. Many commands are 8-bits so this parameters defaults to zero.
   */

  inline void Xmem16AccessMode::writeCommand(uint8_t lo8,uint8_t hi8) {

    // this is equivalent to: *reinterpret_cast<volatile uint8_t *>(0x8000 | lo8)=hi8;
    // this method costs 5 clock cycles

    __asm volatile("  ldi r27,0x80  \n\t"
                   "  mov r26,%0    \n\t"
                   "  st  X,%1      \n\t"
                   :: "r" (lo8), "r" (hi8)
                   : "r26", "r27");
  }


  /**
   * This is used by the LZG decompressor. Since the output is a byte stream and the decompressor doesn't
   * know the colour depth of the target panel we use this 'stream' call that buffers incoming data until
   * it's got a complete 'unit' to write to the interface.
   * @param data The 8-bits
   */

  inline void Xmem16AccessMode::writeStreamedData(uint8_t data) {

    if(_streamIndex==0) {
      _streamByte=data;
      _streamIndex=1;
    }
    else {
      writeData(_streamByte,data);
      _streamIndex=0;
    }
  }


  /**
   * Write a data value to the XMEM interface.
   * @param lo8 The low 8 bits of the value to write.
   * @param hi8 The high 8 bits of the value to write. Many parameter values are 8-bits so this parameters defaults to zero.
   */

  inline void Xmem16AccessMode::writeData(uint8_t lo8,uint8_t hi8) {

    // this is equivalent to: *reinterpret_cast<volatile uint8_t *>(0x8100 | lo8)=hi8;
    // this method costs 5 clock cycles

    __asm volatile("  ldi r27,0x81  \n\t"
                   "  mov r26,%0    \n\t"
                   "  st  X,%1      \n\t"
                   :: "r" (lo8), "r" (hi8)
                   : "r26", "r27");
  }


  /**
   * Write the same data as the previous call to a writeData() command. This allows a sequence of the
   * same data values to be output with some calculations performed between. e.g. the optimised
   * bresenham line drawing algorithm. This access mode cannot do the optimisation so it falls back
   * to writeData()
   * @param lo8 The low 8 bits of the value to write
   * @param hi8 The high 8 bits of the value to write. Many parameter values are 8-bits so this parameters defaults to zero.
   */

  inline void Xmem16AccessMode::writeDataAgain(uint8_t lo8,uint8_t hi8) {
    writeData(lo8,hi8);
  }


  /**
   * Write a batch of the same data values to the XMEM interface
   * @param howMuch The number of 16-bit values to write
   * @param lo8 The low 8 bits of the value to write
   * @param hi8 The high 8 bits of the value to write. Many parameter values are 8-bits so this parameters defaults to zero.
   */

  inline void Xmem16AccessMode::writeMultiData(uint32_t howMuch,uint8_t lo8,uint8_t hi8) {

    while(howMuch--)
      writeData(lo8,hi8);
  }


  /**
   * Enable the XMEM interface so we can talk to the panel through direct memory addressing.
   * Pins PC3..PC7 are freed up for GPIO. The XMEM interface is configured with zero wait
   * states.
   */

  inline void Xmem16AccessMode::initialise() {

    // set up the reset pin

    pinMode(RESET_PIN,OUTPUT);
    digitalWrite(RESET_PIN,HIGH);

    // set up the xmem registers

    XMCRB=_BV(XMM1) | _BV(XMM2);    // free PC3..PC7 for user GPIO
    XMCRA=_BV(SRE);                 // enable xmem, no wait states
  }


  /**
   * Perform a hard reset. RESET is held low for 10ms.
   */

  inline void Xmem16AccessMode::hardReset() {

    // pull reset low for 10ms

    digitalWrite(RESET_PIN,LOW);
    delay(10);
    digitalWrite(RESET_PIN,HIGH);
    delay(130);
  }
};


#endif
