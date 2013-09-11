
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
 * @file GpioAccessMode.h
 * @ingroup AccessModes
 * @brief The access mode for 8-bit GPIO access to an 8-bit panel interface.
 */

#pragma once

#include <stdint.h>

#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__)
#undef pgm_read_byte_far
#define pgm_read_byte_far(a) pgm_read_byte_near(a)
#endif


namespace lcd {

  /**
   * @brief Access mode for an LCD that can be addressed over the GPIO interface.
   *
   * The GPIO pins are the same
   * as would be used for XMEM except that we control them using GPIO port access. This is slower
   * than XMEM but free's up all the unused address lines (A9..A15) for program use.
   * @ingroup AccessModes
   */

  class GpioAccessMode {

    public:

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

      enum {


        #if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__)

        IO_PORTB = 0x05,      ///< arduino pins 8,9,10,11,12,13,x,x
        IO_PORTC = 0x08,      ///< arduino pins 0,1,2,3,4,5,x,x (analog pins)
        IO_PORTD = 0x0b,      ///< arduino pins 0,1,2,3,4,5,6,7

        #elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)

        IO_PORTA = 0x02,      ///< arduino pins 22,23,24,25,26,27,28,29
        IO_PORTB = 0x05,      ///< arduino pins 53,52,51,50,10,11,12,13
        IO_PORTC = 0x08,      ///< arduino pins 37,36,35,34,33,32,31,30
        IO_PORTD = 0x0b,      ///< arduino pins 21,20,19,18,x,x,x,x
        IO_PORTE = 0x0e,      ///< arduino pins 0,1,x,5,2,3,x,x
        IO_PORTF = 0x11,      ///< arduino pins 0,1,2,3,4,5,6,7 (analog pins)
        IO_PORTG = 0x14,      ///< arduino pins 41,40,39,x,x,4,x,x

        #else
        #error "Unsupported MCU type (328, 1280 and 2560 are supported)"
        #endif

        /*
         * Here's where you choose the pins for the GPIO interface.
         * Note that on the ATMega328P the data port has to be PORTD
         */

        DATA_PORT = IO_PORTD,   ///< PORT D

        RS_PORT   = IO_PORTB,   ///< PORT B
        RS_PIN    = 1,          ///< port pin #1
        WR_PORT   = IO_PORTB,   ///< PORT B
        WR_PIN    = 0           ///< port pin #0
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
   * @param command The register command index
   */

  inline void GpioAccessMode::writeCommand(uint8_t command) {
    asm volatile( "cbi %0, %1" :: "I" (RS_PORT), "I" (RS_PIN) ); \
    asm volatile( "cbi %0, %1" :: "I" (WR_PORT), "I" (WR_PIN) ); \
    asm volatile( "out %0, %1" :: "I" (DATA_PORT), "r" (command) );  \
    asm volatile( "sbi %0, %1" :: "I" (WR_PORT), "I" (WR_PIN) ); \
    asm volatile( "sbi %0, %1" :: "I" (RS_PORT), "I" (RS_PIN) );
  }


  /**
   * Write a data value to the XMEM interface
   * @data The data value to write
   */

  inline void GpioAccessMode::writeData(uint8_t data) {
    asm volatile( "cbi %0, %1" :: "I" (WR_PORT), "I" (WR_PIN) );  \
    asm volatile( "nop" :: ); \
    asm volatile( "out %0, %1" :: "I" (DATA_PORT), "r" (data) ); \
    asm volatile( "sbi %0, %1" :: "I" (WR_PORT), "I" (WR_PIN) );
  }


  /**
   * This is an 8-bit interface so streamed data is just the same as normal data
   * @param data The data value to write
   */

  inline void GpioAccessMode::writeStreamedData(uint8_t data) {
    asm volatile( "cbi %0, %1" :: "I" (WR_PORT), "I" (WR_PIN) );  \
    asm volatile( "nop" :: ); \
    asm volatile( "out %0, %1" :: "I" (DATA_PORT), "r" (data) ); \
    asm volatile( "sbi %0, %1" :: "I" (WR_PORT), "I" (WR_PIN) );
  }


  /**
   * Setup the pin modes and directions
   */

  inline void GpioAccessMode::initialise() {

    // set the port direction and initialise to zero

    *reinterpret_cast<volatile uint8_t *>(__SFR_OFFSET+DATA_PORT-1)=0xff;
    *reinterpret_cast<volatile uint8_t *>(__SFR_OFFSET+DATA_PORT)=0;

    // control signal pins to output

    asm volatile( "sbi %0, %1" :: "I" (RS_PORT-1), "I" (RS_PIN) );
    asm volatile( "sbi %0, %1" :: "I" (WR_PORT-1), "I" (WR_PIN) );

    // initial states (RS,WR = low - a command is coming first)

    asm volatile( "cbi %0, %1" :: "I" (RS_PORT), "I" (RS_PIN) );
    asm volatile( "cbi %0, %1" :: "I" (WR_PORT), "I" (WR_PIN) );
  }


  /**
   * Perform a hard reset ... except we don't. To save a pin
   * we connect the RESET arduino pin to the LCD RESET input
   */

  inline void GpioAccessMode::hardReset() {
  }
}
