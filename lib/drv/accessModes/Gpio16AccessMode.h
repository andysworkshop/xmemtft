/*
  XMEM LCD Library for the Arduino

  Copyright 2012,2013 Andrew Brown.
  This access mode was contributed by Colin Rose.

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
 * @defgroup AccessModes
 * @brief Interface between the MCU and the panel.
 *
 * An access mode takes care of transferring data from the MCU to the panel. The access mode must
 * be capable of resetting the panel as well as writing data and commands.
 */

/**
 * @file Gpio16AccessMode.h
 * @ingroup AccessModes
 * @brief The access mode for 16-bit GPIO access to a 16-bit panel (no latch).
 */

#pragma once

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)


namespace lcd {

  /**
   *  I/O port numbers and address. We'll use the single-cycle OUT asm instruction
   *  to write data and we'll use the 2-cycle SBI and CBI instructions to set and
   *  clear bits in the registers used for the control lines. That means that we
   *  are restricted to ports with I/O addresses of 0x1f and below. Not a problem
   *  for the 3280 but some 1280/2560 ports are out of range - but for the Mega
   *  you really should find a way to use the xmem interface instead.
   *
   *  Arduino pin numbers for the port pin numbers [0..7] are show in the comment.
   *  "x" means that the Arduino does not expose the pin in that position.
   *
   *  IO_PORTA = 0x02,      ///< arduino pins 22,23,24,25,26,27,28,29
   *  IO_PORTB = 0x05,      ///< arduino pins 53,52,51,50,10,11,12,13
   *  IO_PORTC = 0x08,      ///< arduino pins 37,36,35,34,33,32,31,30
   *  IO_PORTD = 0x0b,      ///< arduino pins 21,20,19,18, x, x, x, x
   *  IO_PORTE = 0x0e,      ///< arduino pins  0, 1, x, 5, 2, 3, x, x
   *  IO_PORTF = 0x11,      ///< arduino pins  0, 1, 2, 3, 4, 5, 6, 7 (analog pins)
   *  IO_PORTG = 0x14,      ///< arduino pins 41,40,39, x, x, 4, x, x
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
   *  | 37      | PC0  | D8       |
   *  | 36      | PC1  | D9       |
   *  | 35      | PC2  | D10      |
   *  | 34      | PC3  | D11      |
   *  | 33      | PC4  | D12      |
   *  | 32      | PC5  | D13      |
   *  | 31      | PC6  | D14      |
   *  | 30      | PC7  | D15      |
   *  | 39      | PG2  | /RESET   |
   *  | 40      | PG1  | RS       |
   *  | 41      | PG0  | /WR      |
   *  +---------+------+----------+
   *  @ingroup AccessModes
   */

  struct Gpio16AccessModeMapping {
    enum {
    
      // ports are the I/O index, not the physical address

      PORT_DATA_L = 0x02,   ///< PORTA
      PORT_DATA_H = 0x08,   ///< PORTC
      PORT_WR   = 0x14,     ///< PORTG
      PORT_RS   = 0x14,     ///< PORTG
      PORT_RESET  = 0x14,   ///< PORTG

      // pins are the 0..7 port index, not the arduino numbers

      PIN_WR    = PIN2,   ///< The write pin
      PIN_RS    = PIN1,   ///< The RS pin
      PIN_RESET = PIN0    ///< The RESET pin
    };
  };


  /**
   * Access mode template for a GPIO-based LCD interface using two 8 bit wide ports.
   *
   * This template includes a highly optimised assembly language multiple-pixel writer that can
   * be used in 16-bit colour mode to push same-colour pixels out to the LCD at close to 8Mhz on
   * a 16Mhz Arduino. When clearing a QVGA display the optimised version achieves 10.8ms whereas
   * a tight loop around the single pixel writer achieves 100ms.
   *
   * I include driver typedefs that use the same pins as the XMEM interface for controlling the
   * LCD. It should be trivial for you to work out how to supply your own pin mappings if your
   * project has pin limitations.
   *
   * Finally, note that the optimised pixel-pusher ensures that global interrupts are off while
   * it's running because it cannot have an IRQ handler modify any pin on the port where /WR lives
   * while it's running. If you know this will never happen then you can remove that part of the
   * assembly language to increase concurrency at the expense of worse pixel throughput if an
   * IRQ goes off while it's running.
   *
   * @tparam TPinMappings A type that contains the constants that define the pins and ports,
   * usually in the form of an enum, that represents your physical setup.
   * @ingroup AccessModes
   */

  template<typename TPinMappings>
  class Gpio16AccessMode {

    protected:
      static uint8_t _streamIndex;
      static void initOutputHigh(uint8_t port,uint8_t pin);

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
   * Initialise the static member
   */

  template <typename TPinMappings>
  uint8_t Gpio16AccessMode<TPinMappings>::_streamIndex=0;


  /**
   * Shortcut to write an 8-bit command and a data parameter. This is a common scenario
   * in programming the registers
   * @param cmd The command register number
   * @param lo8 The low 8 bits of the command to write
   * @param hi8 The high 8 bits of the command to write. Many commands are 8-bits so this parameters defaults to zero.
   */

  template<class TPinMappings>
  __attribute__((always_inline))
  inline void Gpio16AccessMode<TPinMappings>::writeCommandData(uint8_t cmd,uint8_t lo8,uint8_t hi8) {

    writeCommand(cmd,0);
    writeData(lo8,hi8);
  }


  /**
   * Write a command to the GPIO interface. This is implemented in assembly language.
   * @param lo8 The low 8 bits of the command to write
   * @param hi8 The high 8 bits of the command to write. Many commands are 8-bits so this parameters defaults to zero.
   */

  template<class TPinMappings>
  inline void Gpio16AccessMode<TPinMappings>::writeCommand(uint8_t lo8,uint8_t hi8) {
  
    __asm volatile(
      "  cbi %1, %5 \n\t"     // RS    = LOW
      "  out %2, %6 \n\t"     // PORTA = lo8
      "  out %3, %7 \n\t"     // PORTC = hi8
      "  cbi %0, %4 \n\t"     // nWR   = LOW
      "  sbi %0, %4 \n\t"     // nWR   = HIGH

      :: "I" (TPinMappings::PORT_WR),       // %0
         "I" (TPinMappings::PORT_RS),       // %1
         "I" (TPinMappings::PORT_DATA_L),   // %2
         "I" (TPinMappings::PORT_DATA_H),   // %3
         "I" (TPinMappings::PIN_WR),        // %4
         "I" (TPinMappings::PIN_RS),        // %5
         "d" (lo8),                         // %6
         "d" (hi8)                          // %7
      );
  }


  /**
   * This is used by the LZG decompressor. Since the output is a byte stream and the decompressor doesn't
   * know the colour depth of the target panel we use this 'stream' call that buffers incoming data until
   * it's got a complete 'unit' to write to the interface. In this case we do half a transaction when the
   * first byte arrives and finish it off when the second one shows up
   * @param data The 8-bits
   */

  template<class TPinMappings>
  inline void Gpio16AccessMode<TPinMappings>::writeStreamedData(uint8_t data) {

    if(_streamIndex==0) {

      __asm volatile(
        "  out %1, %3 \n\t"     // PORTA = data
        "  sbi %0, %2 \n\t"     // RS    = HIGH

        :: "I" (TPinMappings::PORT_RS),       // %0
           "I" (TPinMappings::PORT_DATA_L),   // %1
           "I" (TPinMappings::PIN_RS),        // %2
           "d" (data)                         // %3
        );
    }
    else {
      __asm volatile(
        "  out %1, %3 \n\t"     // PORTC = data
        "  cbi %0, %2 \n\t"     // nWR   = LOW
        "  sbi %0, %2 \n\t"     // nWR   = HIGH

        :: "I" (TPinMappings::PORT_WR),       // %0
           "I" (TPinMappings::PORT_DATA_H),   // %1
           "I" (TPinMappings::PIN_WR),        // %2
           "d" (data)                         // %3
        );
    }

    // flip the position indicator
    _streamIndex^=1;
  }


  /**
   * Write a data value to the GPIO interface. This is implemented in AVR assembly language.
   * @param lo8 The low 8 bits of the value to write
   * @param hi8 The high 8 bits of the value to write. Many parameter values are 8-bits so this parameters defaults to zero.
   */

  template<class TPinMappings>
  inline void Gpio16AccessMode<TPinMappings>::writeData(uint8_t lo8,uint8_t hi8) {

    __asm volatile(
      "  sbi %1, %5 \n\t"     // RS    = HIGH
      "  out %2, %6 \n\t"     // PORTA = lo8
      "  out %3, %7 \n\t"     // PORTC = hi8
      "  cbi %0, %4 \n\t"     // nWR   = LOW
      "  sbi %0, %4 \n\t"     // nWR   = HIGH

      ::  "I" (TPinMappings::PORT_WR),      // %0
        "I" (TPinMappings::PORT_RS),        // %1
        "I" (TPinMappings::PORT_DATA_L),    // %2
          "I" (TPinMappings::PORT_DATA_H),  // %3
        "I" (TPinMappings::PIN_WR),         // %4
        "I" (TPinMappings::PIN_RS),         // %5
        "d" (lo8),                          // %6
        "d" (hi8)                           // %7
      );
  }


  /**
   * Write the same data as the previous call to a writeData() command. This allows a sequence of the
   * same data values to be output with some calculations performed between. e.g. the optimised
   * bresenham line drawing algorithm. The parameters are present for access modes that cannot do this
   * optimisation and must fall back to writeData().
   * @param lo8 The low 8 bits of the value to write
   * @param hi8 The high 8 bits of the value to write. Many parameter values are 8-bits so this parameters defaults to zero.
   */

  template<class TPinMappings>
  inline void Gpio16AccessMode<TPinMappings>::writeDataAgain(uint8_t /* lo8 */,uint8_t /* hi8 */) {

    __asm volatile(
      "  cbi %0, %1 \n\t"     // nWR   = LOW
      "  sbi %0, %1 \n\t"     // nWR   = HIGH

      ::  "I" (TPinMappings::PORT_WR),    // %0
        "I" (TPinMappings::PIN_WR)        // %1
    );
  }


  /**
   * Write a batch of the same data values to the XMEM interface using GPIO. The values are written out in a
   * highly optimised loop in bursts of 40 at a time. This value seems a good trade off between flash usage
   * and speed. The turnaround time between batches has been measured at around 1 microsecond. Note the use
   * of %= labels so that inlining doesn't produce duplicate names.
   * @param howMuch The number of 16-bit values to write
   * @param lo8 The low 8 bits of the value to write
   * @param hi8 The high 8 bits of the value to write. Many parameter values are 8-bits so this parameters defaults to zero.
   */

  template<class TPinMappings>
  inline void Gpio16AccessMode<TPinMappings>::writeMultiData(uint32_t howMuch,uint8_t lo8,uint8_t hi8) {

    __asm volatile(
      "  sbi  %1, %8    \n\t"     // RS    = HIGH
      "  out  %2, %4    \n\t"     // PORTA = lo8
      "  out  %3, %5    \n\t"     // PORTC = hi8

      "  clr  r20     \n\t"       // r20 = global interrupt status
      "  brid intdis%=  \n\t"     // branch if global interrupts are off
      "  cli        \n\t"         // disable global interrupts (because we cannot let PORTG get modified by an IRQ)
      "  inc  r20     \n\t"       // r20 (global interrupts disabled) = 1

      "intdis%=:      \n\t"
      "  in   r18, %0   \n\t"     // get PORT_WR to r18 and r19
      "  mov  r19, r18  \n\t"
      "  cbr  r18, %7   \n\t"     // clear WR in r18 using a constant mask
      "  sbr  r19, %7   \n\t"     // set WR in r19 using a constant mask
      "  cpi  %A6, 40   \n\t"     // if howMuch<40 then jump to lastlot
      "  cpc  %B6, r1   \n\t"     // r1 is the zero register: always zero
      "  cpc  %C6, r1   \n\t"     // r1 is the zero register: always zero
      "  brsh batchloop%= \n\t"
      "  rjmp lastlot%= \n\t"

      "batchloop%=:   \n\t"
      "  out  %0,  r18  \n\t"     // toggle nWR 40 times
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 2
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 3
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 4
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 5
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 6
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 7
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 8
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 9
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 10
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 11
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 12
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 13
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 14
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 15
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 16
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 17
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 18
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 19
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 20
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 21
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 22
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 23
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 24
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 25
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 26
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 27
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 28
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 29
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 30
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 31
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 32
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 33
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 34
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 35
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 36
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 37
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 38
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 39
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 40
      "  out  %0,  r19  \n\t"

      "  subi %A6, 40   \n\t"     // subtract 40 from howMuch
      "  sbci %B6, 0    \n\t"
      "  sbci %C6, 0    \n\t"
      "  cpi  %A6, 40   \n\t"     // if howMuch >= 40 then go back for another batch
      "  cpc  %B6, r1   \n\t"     // r1 is the zero register: always zero
      "  cpc  %C6, r1   \n\t"     // r1 is the zero register: always zero
      "  brlo lastlot%= \n\t"
      "  rjmp batchloop%= \n\t"
      
      "lastlot%=:     \n\t"       // load index Z with the address of the end
      "  ldi  r31, pm_hi8(finished%=) \n\t"
      "  ldi  r30, pm_lo8(finished%=) \n\t"
      "  lsl  %A6          \n\t"        // multiply remaining by 2
      "  sub  r30, %A6     \n\t"        // subtract remaining*2 from Z
      "  sbci r31, 0       \n\t"
      "  ijmp              \n\t"        // jump to Z to finish off the writing
      "  out  %0,  r18  \n\t"     // 1
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 2
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 3
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 4
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 5
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 6
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 7
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 8
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 9
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 10
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 11
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 12
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 13
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 14
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 15
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 16
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 17
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 18
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 19
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 20
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 21
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 22
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 23
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 24
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 25
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 26
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 27
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 28
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 29
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 30
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 31
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 32
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 33
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 34
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 35
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 36
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 37
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 38
      "  out  %0,  r19  \n\t"
      "  out  %0,  r18  \n\t"     // 39
      "  out  %0,  r19  \n\t"
      
      "finished%=:           \n\t"
      "    cpi  r20, 0       \n\t"          // if global interrupts were enabled when we came in, restore them now
      "    breq skipinten%=  \n\t"
      "    sei               \n\t"
      
      "skipinten%=:          \n\t"

      ::  "I" (TPinMappings::PORT_WR),      // %0
        "I" (TPinMappings::PORT_RS),        // %1
        "I" (TPinMappings::PORT_DATA_L),    // %2
        "I" (TPinMappings::PORT_DATA_H),    // %3
        "d" (lo8),                          // %4
        "d" (hi8),                          // %5
        "d" (howMuch),                      // %C6,%B6,%A6
        "I" (_BV(TPinMappings::PIN_WR)),    // %7
        "I" (TPinMappings::PIN_RS)          // %8
         
      : "r18", "r19", "r20", "r30", "r31"
    );
  }


  /**
   * Set up the pins for GPIO. RESET, RS, ALE and WR are set to output mode and
   * initialised to a HIGH state. The data port is initialised to output and we
   * don't care for its initial state.
   */

  template<class TPinMappings>
  inline void Gpio16AccessMode<TPinMappings>::initialise() {

    // reset pin

    initOutputHigh(TPinMappings::PORT_RESET,TPinMappings::PIN_RESET);

    // control pins

    initOutputHigh(TPinMappings::PORT_RS,TPinMappings::PIN_RS);
    initOutputHigh(TPinMappings::PORT_WR,TPinMappings::PIN_WR);

    // data ports

    *reinterpret_cast<volatile uint8_t *>(__SFR_OFFSET+TPinMappings::PORT_DATA_L-1)=0xff;
    *reinterpret_cast<volatile uint8_t *>(__SFR_OFFSET+TPinMappings::PORT_DATA_H-1)=0xff;
  }


  /**
   * Initialise a pin to output and set it high
   * @param port port I/O index
   * @param pin pin 0..7 number in the port
   */

  template<class TPinMappings>
  inline void Gpio16AccessMode<TPinMappings>::initOutputHigh(uint8_t port,uint8_t pin) {

    // DDR is always at port address-1

    *reinterpret_cast<volatile uint8_t *>(__SFR_OFFSET+port-1)|=_BV(pin);

    // set the pin high on the port

    *reinterpret_cast<volatile uint8_t *>(__SFR_OFFSET+port)|=_BV(pin);
  }



  /**
   * Perform a hard reset. RESET is set low for 10ms. I've never seen a panel that needs reset
   * low for anywhere close to that long.
   */

  template<class TPinMappings>
  inline void Gpio16AccessMode<TPinMappings>::hardReset() {

    // pull reset low for 10ms

    *reinterpret_cast<volatile uint8_t *>(__SFR_OFFSET+TPinMappings::PORT_RESET)&=~_BV(TPinMappings::PIN_RESET);
    delay(10);
    *reinterpret_cast<volatile uint8_t *>(__SFR_OFFSET+TPinMappings::PORT_RESET)|=_BV(TPinMappings::PIN_RESET);
    delay(130);
  }


  /**
   * Typedefs for easier access
   */

  typedef Gpio16AccessMode<Gpio16AccessModeMapping> DefaultMegaGpio16AccessMode;
}


#endif
