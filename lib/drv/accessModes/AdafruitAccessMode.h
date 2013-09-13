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

/*
 * Implementation for Adafruit TFT LCD copyright (c) 2013 Colin Irwin, see
 * http://aethersdr.org/ for details. Provided under original terms and
 * conditions.
 *
 */

#pragma once

#include <stdint.h>

namespace lcd {


  /**
   * This class provides an access mode for the Adafruit 2.8" ILI9325 shield
   * running in 18-bit (262K colour) mode
   */

  class AdafruitAccessMode {

    public:

      enum {

        /**
         * I/O port numbers and address. We'll use the single-cycle OUT asm instruction
         * to write data and we'll use the 2-cycle SBI and CBI instructions to set and
         * clear bits in the registers used for the control lines. That means that we
         * are restricted to ports with I/O addresses of 0x1f and below. Not a problem
         * for the 3280 but some 1280/2560 ports are out of range - but for the Mega
         * you really should find a way to use the xmem interface instead.
         *
         * Arduino pin numbers for the port pin numbers [0..7] are show in the comment.
         * "x" means that the Arduino does not expose the pin in that position.
         */

#if defined(__AVR_ATmega2560__) || defined(__AVR_ATmega1280__)

        IO_PORTF = 0x11, // 0,1,2,3,4,5,6,7 (analog pins)

#else

#error "Unsupported MCU type (2560 and 1280 are supported)"

#endif

        /**
         * Here's where you choose the pins for the Adafruit interface.
         */

        RD_PIN=0,         ///< read
        WR_PIN=1,         ///< write
        RS_PIN=2,         ///< register/data select
        CS_PIN=3,         ///< chip-select
        CARD_CS_PIN=3,    ///< sd-card chip-select
      };

    public:
      static void initialise();
      static void hardReset();

      static void writeCommand(uint8_t lo8);
      static void writeData(uint8_t data);
      static void writeData(uint8_t lo8,uint8_t hi8);
      static void writeCommandData(uint8_t cmd,uint8_t lo8,uint8_t hi8=0);
      static void writeDataAgain(uint8_t lo8,uint8_t hi8=0);
      static void writeMultiData(uint32_t howMuch,uint8_t lo8,uint8_t hi8=0);
      static void writeStreamedData(uint8_t data);
  };


  /**
   * Write a command byte
   */

  inline void AdafruitAccessMode::writeCommand(uint8_t lo8) {

    // set the RS line

    PORTF&=~(1 << RS_PIN);

    // write the value 0x00

    PORTH=(PORTH & B10000111);
    PORTB=(PORTB & B01001111);
    PORTG=(PORTG & B11011111);

    // toggle the WR line

    PORTF&=~(1 << WR_PIN);
    PORTF|=(1 << WR_PIN);

    // write the specified command value

    PORTH=(PORTH & B10000111) | (((lo8) & B11000000) >> 3) | (((lo8) & B00000011) << 5);
    PORTB=(PORTB & B01001111) | (((lo8) & B00101100) << 2);
    PORTG=(PORTG & B11011111) | (((lo8) & B00010000) << 1);

    // toggle the WR line

    PORTF&=~(1 << WR_PIN);
    PORTF|=(1 << WR_PIN);
  }


  /**
   * Write an 8-bit data value
   * @param data The 8-bit data value
   */

  inline void AdafruitAccessMode::writeData(uint8_t data) {

    // reset the RS line

    PORTF|=(1 << RS_PIN);

    // write the specified data value

    PORTH=(PORTH & B10000111) | (((data) & B11000000) >> 3) | (((data) & B00000011) << 5);
    PORTB=(PORTB & B01001111) | (((data) & B00101100) << 2);
    PORTG=(PORTG & B11011111) | (((data) & B00010000) << 1);

    // toggle the WR line

    PORTF&=~(1 << WR_PIN);
    PORTF|=(1 << WR_PIN);
  }


  /**
   * Write 16-bits of data
   * @param lo8 The low 8 bits
   * @param hi8 The high 8-bits
   */

  inline void AdafruitAccessMode::writeData(uint8_t lo8,uint8_t hi8) {
    writeData(lo8);
    writeData(hi8);
  }


  /**
   * Write the same 16-bits of data as was last written with writeData(lo,hi). Those
   * bytes are presented again here for drivers where no optimisation is possible,
   * such as this one.
   * @param lo8 The low 8 bits
   * @param hi8 The high 8-bits
   */

  inline void AdafruitAccessMode::writeDataAgain(uint8_t lo8,uint8_t hi8) {
    writeData(lo8,hi8);
  }


  /**
   * Repeatedly write out 16-bits of data.
   * @param howMuch The repeat count.
   * @param lo8 The low 8 bits
   * @param hi8 The high 8-bits
   */

  inline void AdafruitAccessMode::writeMultiData(uint32_t howMuch,uint8_t lo8,uint8_t hi8) {

    // no optimisation is possible

    while(howMuch--)
      writeData(lo8,hi8);
  }


  /**
   * Write a single byte out from a stream of colour values. This is used when streaming
   * data to the display from a decompression routine. This interface is 8-bit so we don't
   * need to buffer the byte, it can go straight out.
   * @param data The next byte in the stream
   */

  inline void AdafruitAccessMode::writeStreamedData(uint8_t data) {
    writeData(data);
  }


  /**
   * Write a command and 16-bits of data
   * @param cmd The command to write
   * @param lo8 The low 8-bits
   * @param hi8 The high 8-bits
   */

  inline void AdafruitAccessMode::writeCommandData(uint8_t cmd,uint8_t lo8,uint8_t hi8) {

    // set the RS line

    PORTF&=~(1 << RS_PIN);

    // write the value 0x00

    PORTH=(PORTH & B10000111);
    PORTB=(PORTB & B01001111);
    PORTG=(PORTG & B11011111);

    // toggle the WR line

    PORTF&=~(1 << WR_PIN);
    PORTF|=(1 << WR_PIN);

    // write the specified command value

    PORTH=(PORTH & B10000111) | (((cmd) & B11000000) >> 3) | (((cmd) & B00000011) << 5);
    PORTB=(PORTB & B01001111) | (((cmd) & B00101100) << 2);
    PORTG=(PORTG & B11011111) | (((cmd) & B00010000) << 1);

    // toggle the WR line

    PORTF&=~(1 << WR_PIN);
    PORTF|=(1 << WR_PIN);

    const uint8_t DATA_LOW=static_cast<uint8_t>(lo8);
    const uint8_t DATA_HIGH=static_cast<uint8_t>(hi8);

    // reset the RS line

    PORTF|=(1 << RS_PIN);

    // write the high byte of the specified data value

    PORTH=(PORTH & B10000111) | (((DATA_HIGH) & B11000000) >> 3) | (((DATA_HIGH) & B00000011) << 5);
    PORTB=(PORTB & B01001111) | (((DATA_HIGH) & B00101100) << 2);
    PORTG=(PORTG & B11011111) | (((DATA_HIGH) & B00010000) << 1);

    // toggle the WR line

    PORTF&=~(1 << WR_PIN);
    PORTF|=(1 << WR_PIN);

    // write the low byte of the specified data value

    PORTH=(PORTH & B10000111) | (((DATA_LOW) & B11000000) >> 3) | (((DATA_LOW) & B00000011) << 5);
    PORTB=(PORTB & B01001111) | (((DATA_LOW) & B00101100) << 2);
    PORTG=(PORTG & B11011111) | (((DATA_LOW) & B00010000) << 1);

    // toggle the WR line

    PORTF&=~(1 << WR_PIN);
    PORTF|=(1 << WR_PIN);
  }


  /**
   * Setup the pin modes and directions
   */

  inline void AdafruitAccessMode::initialise() {

    // reset all control lines

    PORTF|=(1 << CS_PIN);
    PORTF|=(1 << RS_PIN);
    PORTF|=(1 << WR_PIN);
    PORTF|=(1 << RD_PIN);

    // reset card CS line

    PORTE|=(1 << CARD_CS_PIN);

    // set the LCD and card control lines as outputs

    DDRE|=B00100000;
    DDRF|=B00001111;

    // set the LCD data lines as outputs

    DDRH|=B01111000;
    DDRB|=B10110000;
    DDRG|=B00100000;
  }


  /**
   * Perform a hard reset
   */

  inline void AdafruitAccessMode::hardReset() {

    // reset all control lines

    PORTF|=(1 << CS_PIN);
    PORTF|=(1 << RS_PIN);
    PORTF|=(1 << WR_PIN);
    PORTF|=(1 << RD_PIN);

    // toggle the card CS line

    PORTE&=~(1 << CARD_CS_PIN);
    delay(2);
    PORTE|=(1 << CARD_CS_PIN);

    // set the CS line

    PORTF&=~(1 << CS_PIN);

    // ?? - not sure why six zero's have to be written out

    for(uint8_t i=0;i < 7;i++) {
      writeData(0x00);
    }

    delay(100);
  }
}
