/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012,2013 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
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

	/*
	 * Base for an LCD that can be addressed over the GPIO interface. The GPIO pins are the same
	 * as would be used for XMEM except that we control them using GPIO port access. This is slower
	 * than XMEM but free's up all the unused address lines (A9..A15) for program use.
	 */

	class AdafruitAccessMode {

		public:

			enum {

				/*
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

#if defined(__AVR_ATmega2560__)

				IO_PORTF = 0x11, // 0,1,2,3,4,5,6,7 (analog pins)

#else

#error "Unsupported MCU type (2560 is supported)"

#endif

				/*
				 * Here's where you choose the pins for the Adafruit interface.
				 */

				RD_PIN=0,
				WR_PIN=1,
				RS_PIN=2,
				CS_PIN=3,
				CARD_CS_PIN=3,
			};

		public:
			static void initialise();
			static void hardReset();
			static void writeCommand(uint8_t command) __attribute((always_inline));
			static void writeData(uint8_t data) __attribute((always_inline));
			static void writeCommandData(uint8_t command,uint16_t data) __attribute((always_inline));
	};

	/**
	 * Write a command to the XMEM interface
	 */

	inline void AdafruitAccessMode::writeCommand(uint8_t command) {

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

		PORTH=(PORTH & B10000111) | (((command) & B11000000) >> 3) | (((command) & B00000011) << 5);
		PORTB=(PORTB & B01001111) | (((command) & B00101100) << 2);
		PORTG=(PORTG & B11011111) | (((command) & B00010000) << 1);

		// toggle the WR line

		PORTF&=~(1 << WR_PIN);
		PORTF|=(1 << WR_PIN);
	}

	/**
	 * Write a data value to the XMEM interface
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
	 * Write a command to the XMEM interface
	 */

	inline void AdafruitAccessMode::writeCommandData(uint8_t command,uint16_t data) {

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

		PORTH=(PORTH & B10000111) | (((command) & B11000000) >> 3) | (((command) & B00000011) << 5);
		PORTB=(PORTB & B01001111) | (((command) & B00101100) << 2);
		PORTG=(PORTG & B11011111) | (((command) & B00010000) << 1);

		// toggle the WR line

		PORTF&=~(1 << WR_PIN);
		PORTF|=(1 << WR_PIN);

		const uint8_t DATA_LOW=static_cast<uint8_t>(data);
		const uint8_t DATA_HIGH=static_cast<uint8_t>(data >> 8);

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

	/*
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
