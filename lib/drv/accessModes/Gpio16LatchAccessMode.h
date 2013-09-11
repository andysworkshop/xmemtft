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
 * @defgroup AccessModes
 * @brief Interface between the MCU and the panel.
 *
 * An access mode takes care of transferring data from the MCU to the panel. The access mode must
 * be capable of resetting the panel as well as writing data and commands.
 */

/**
 * @file Gpio16LatchAccessMode.h
 * @ingroup AccessModes
 * @brief The access mode for 8-bit GPIO access to a 16-bit panel using a latch.
 */

#pragma once

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)


namespace lcd {


  /**
   * @brief Access mode for optimised 16-bit I/O through a latch.
   *
   * Pin and port mappings for using the Gpio16LatchAccessMode against the same pins that
   * XMEM on the Arduino Mega would use. Here they are:
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
   *  | 39      | PG2  | ALE      |
   *  | 41      | PG0  | /WR      |
   *  +---------+------+----------+
   *  @ingroup AccessModes
   */

  struct Gpio16LatchAccessModeXmemMapping {
    enum {

      // ports are the I/O index, not the physical address

      PORT_DATA  = 0x02,    ///< PORTA
      PORT_WR    = 0x14,    ///< PORTG
      PORT_RS    = 0x08,    ///< PORTC
      PORT_ALE   = 0x14,    ///< PORTG
      PORT_RESET = 0x08,    ///< PORTC

      // pins are the 0..7 port index, not the arduino numbers

      PIN_WR    = PIN0,     ///< The write pin
      PIN_RS    = PIN0,     ///< The RS pin
      PIN_ALE   = PIN2,     ///< The ALE pin
      PIN_RESET = PIN2      ///< The RESET pin
    };
  };


  /**
   * Access mode template for a GPIO-based LCD interface that uses an external latch to reduce
   * the number of required pins by 7. An entire 8-bit port is eliminated at the expense
   * of one additional pin for enabling the latch (ALE). See my website for full details
   * and a write-up of how this interface works. 12 pins are required, of which 8 of them must
   * be a full port for the data.
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
  class Gpio16LatchAccessMode {

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
  uint8_t Gpio16LatchAccessMode<TPinMappings>::_streamIndex=0;


  /**
   * Shortcut to write an 8-bit command and a data parameter. This is a common scenario
   * in programming the registers
   * @param cmd The command register number
   * @param lo8 The low 8 bits of the command to write
   * @param hi8 The high 8 bits of the command to write. Many commands are 8-bits so this parameters defaults to zero.
   */

  template<class TPinMappings>
  __attribute__((always_inline))
  inline void Gpio16LatchAccessMode<TPinMappings>::writeCommandData(uint8_t cmd,uint8_t lo8,uint8_t hi8) {

    writeCommand(cmd,0);
    writeData(lo8,hi8);
  }


  /**
   * Write a command to the GPIO interface. This is implemented in assembly language.
   * @param lo8 The low 8 bits of the command to write
   * @param hi8 The high 8 bits of the command to write. Many commands are 8-bits so this parameters defaults to zero.
   */

  template<class TPinMappings>
  inline void Gpio16LatchAccessMode<TPinMappings>::writeCommand(uint8_t lo8,uint8_t hi8) {

    __asm volatile(
        "  sbi %1, %5   \n\t"     // ALE   = HIGH
        "  out %3, %7   \n\t"     // PORTA = lo8
        "  cbi %2, %6   \n\t"     // RS    = LOW
        "  cbi %1, %5   \n\t"     // ALE   = LOW
        "  out %3, %8   \n\t"     // PORTA = hi8
        "  cbi %0, %4   \n\t"     // /WR   = LOW
        "  sbi %0, %4   \n\t"     // /WR   = HIGH

        :: "I" (TPinMappings::PORT_WR),     // %0
           "I" (TPinMappings::PORT_ALE),    // %1
           "I" (TPinMappings::PORT_RS),     // %2
           "I" (TPinMappings::PORT_DATA),   // %3
           "I" (TPinMappings::PIN_WR),      // %4
           "I" (TPinMappings::PIN_ALE),     // %5
           "I" (TPinMappings::PIN_RS),      // %6
           "d" (lo8),                       // %7
           "d" (hi8)                        // %8
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
  inline void Gpio16LatchAccessMode<TPinMappings>::writeStreamedData(uint8_t data) {

    if(_streamIndex==0) {

      __asm volatile(
        "  sbi %0, %3   \n\t"     // ALE   = HIGH
        "  out %2, %5   \n\t"     // PORTA = data
        "  sbi %1, %4   \n\t"     // RS    = HIGH

        :: "I" (TPinMappings::PORT_ALE),    // %0
           "I" (TPinMappings::PORT_RS),     // %1
           "I" (TPinMappings::PORT_DATA),   // %2
           "I" (TPinMappings::PIN_ALE),     // %3
           "I" (TPinMappings::PIN_RS),      // %4
           "d" (data)                       // %5
          );
    }
    else {
      __asm volatile(
        "  cbi %1, %4   \n\t"     // ALE   = LOW
        "  out %2, %5   \n\t"     // PORTA = data
        "  cbi %0, %3   \n\t"     // /WR   = LOW
        "  sbi %0, %3   \n\t"     // /WR   = HIGH

        :: "I" (TPinMappings::PORT_WR),     // %0
           "I" (TPinMappings::PORT_ALE),    // %1
           "I" (TPinMappings::PORT_DATA),   // %2
           "I" (TPinMappings::PIN_WR),      // %3
           "I" (TPinMappings::PIN_ALE),     // %4
           "d" (data)                       // %5
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
  inline void Gpio16LatchAccessMode<TPinMappings>::writeData(uint8_t lo8,uint8_t hi8) {

    __asm volatile(
        "  sbi %1, %5   \n\t"     // ALE   = HIGH
        "  out %3, %7   \n\t"     // PORTA = lo8
        "  sbi %2, %6   \n\t"     // RS    = HIGH
        "  cbi %1, %5   \n\t"     // ALE   = LOW
        "  out %3, %8   \n\t"     // PORTA = hi8
        "  cbi %0, %4   \n\t"     // /WR   = LOW
        "  sbi %0, %4   \n\t"     // /WR   = HIGH

        :: "I" (TPinMappings::PORT_WR),     // %0
           "I" (TPinMappings::PORT_ALE),    // %1
           "I" (TPinMappings::PORT_RS),     // %2
           "I" (TPinMappings::PORT_DATA),   // %3
           "I" (TPinMappings::PIN_WR),      // %4
           "I" (TPinMappings::PIN_ALE),     // %5
           "I" (TPinMappings::PIN_RS),      // %6
           "d" (lo8),                       // %7
           "d" (hi8)                        // %8
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
  inline void Gpio16LatchAccessMode<TPinMappings>::writeDataAgain(uint8_t /* lo8 */,uint8_t /* hi8 */) {

    __asm volatile(
        "  cbi %0, %1   \n\t"     // /WR   = LOW
        "  sbi %0, %1   \n\t"     // /WR   = HIGH

        :: "I" (TPinMappings::PORT_WR),     // %0
           "I" (TPinMappings::PIN_WR)       // %1
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
  inline void Gpio16LatchAccessMode<TPinMappings>::writeMultiData(uint32_t howMuch,uint8_t lo8,uint8_t hi8) {

    __asm volatile(
        "    sbi  %9, %7       \n\t"      // ALE   = HIGH
        "    out  %1, %2       \n\t"      // PORTA = lo8
        "    sbi  %3, %8       \n\t"      // RS    = HIGH
        "    cbi  %9, %7       \n\t"      // ALE   = LOW
        "    out  %1, %4       \n\t"      // PORTA = hi8

        "    clr  r20          \n\t"      // r20 = global interrupt status
        "    brid intdis%=     \n\t"      // branch if global interrupts are off
        "    cli               \n\t"      // disable global interrupts (because we cannot let PORTG get modified by an IRQ)
        "    inc  r20          \n\t"      // r20 (global interrupts disabled) = 1
        "intdis%=:             \n\t"
        "    in   r18, %0      \n\t"      // get PORT_WR to r18 and r19
        "    mov  r19, r18     \n\t"
        "    cbr  r18, %6      \n\t"      // clear WR in r18
        "    sbr  r19, %6      \n\t"      // set WR in r19
        "    cpi  %A5, 40      \n\t"      // if howMuch<40 then jump to lastlot
        "    cpc  %B5, r1      \n\t"
        "    cpc  %C5, r1      \n\t"
        "    brsh batchloop%=  \n\t"
        "    rjmp lastlot%=    \n\t"
        "batchloop%=:          \n\t"
        "    out  %0,  r18     \n\t"      // toggle /WR 40 times
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    subi %A5, 40      \n\t"        // subtract 40 from howMuch
        "    sbci %B5, 0       \n\t"
        "    sbci %C5, 0       \n\t"
        "    cpi  %A5, 40      \n\t"        // if howMuch >= 40 then go back for another batch
        "    cpc  %B5, r1      \n\t"
        "    cpc  %C5, r1      \n\t"
        "    brlo lastlot%=    \n\t"
        "    rjmp batchloop%=  \n\t"
        "lastlot%=:            \n\t"        // load index Z with the address of the end
        "    ldi  r31, pm_hi8(finished%=)   \n\t"
        "    ldi  r30, pm_lo8(finished%=)   \n\t"
        "    lsl  %A5          \n\t"        // multiply remaining by 2
        "    sub  r30, %A5     \n\t"        // subtract remaining*2 from Z
        "    sbci r31, 0       \n\t"
        "    ijmp              \n\t"        // jump to Z to finish off the writing
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "    out  %0,  r18     \n\t"
        "    out  %0,  r19     \n\t"
        "finished%=:           \n\t"
        "    cpi  r20, 0       \n\t"          // if global interrupts were enabled when we came in, restore them now
        "    breq skipinten%=  \n\t"
        "    sei               \n\t"
        "skipinten%=:          \n\t"

        :: "I" (TPinMappings::PORT_WR),     // %0
           "I" (TPinMappings::PORT_DATA),   // %1
           "d" (lo8),                       // %2
           "I" (TPinMappings::PORT_RS),     // %3
           "d" (hi8),                       // %4
           "d" (howMuch),                   // %C5,%B5,%A5
           "I" (_BV(TPinMappings::PIN_WR)), // %6
           "I" (TPinMappings::PIN_ALE),     // %7
           "I" (TPinMappings::PIN_RS),      // %8
           "I" (TPinMappings::PORT_ALE)     // %9
        : "r18", "r19", "r20", "r30", "r31"
    );
  }


  /**
   * Set up the pins for GPIO. RESET, RS, ALE and WR are set to output mode and
   * initialised to a HIGH state. The data port is initialised to output and we
   * don't care for its initial state.
   */

  template<class TPinMappings>
  inline void Gpio16LatchAccessMode<TPinMappings>::initialise() {

    // reset pin

    initOutputHigh(TPinMappings::PORT_RESET,TPinMappings::PIN_RESET);

    // control pins

    initOutputHigh(TPinMappings::PORT_RS,TPinMappings::PIN_RS);
    initOutputHigh(TPinMappings::PORT_ALE,TPinMappings::PIN_ALE);
    initOutputHigh(TPinMappings::PORT_WR,TPinMappings::PIN_WR);

    // data port

    *reinterpret_cast<volatile uint8_t *>(__SFR_OFFSET+TPinMappings::PORT_DATA-1)=0xff;
  }


  /**
   * Initialise a pin to output and set it high
   * @param port port I/O index
   * @param pin pin 0..7 number in the port
   */

  template<class TPinMappings>
  inline void Gpio16LatchAccessMode<TPinMappings>::initOutputHigh(uint8_t port,uint8_t pin) {

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
  inline void Gpio16LatchAccessMode<TPinMappings>::hardReset() {

    // pull reset low for 10ms

    *reinterpret_cast<volatile uint8_t *>(__SFR_OFFSET+TPinMappings::PORT_RESET)&=~_BV(TPinMappings::PIN_RESET);
    delay(10);
    *reinterpret_cast<volatile uint8_t *>(__SFR_OFFSET+TPinMappings::PORT_RESET)|=_BV(TPinMappings::PIN_RESET);
    delay(130);
  }


  /**
   * Typedefs for easier access
   */

  typedef Gpio16LatchAccessMode<Gpio16LatchAccessModeXmemMapping> DefaultMegaGpio16LatchAccessMode;
}


#endif
