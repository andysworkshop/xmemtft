/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012,2013 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

/**
 * @defgroup Decoders
 * @brief JPEG and LZG display functionality
 *
 * The graphics library provides functionality to display JPEG files from data sources such
 * as flash memory and serial interface. An Arduino Mega is required to use these functions.
 */

/**
 * @file JpegDataSources.h
 * @brief Serial and flash implementations.
 * @ingroup Decoders
 */

#pragma once


namespace lcd {

	/**
	 * @brief Base class for Jpeg data sources
	 * @ingroup Decoders
	 */

	class JpegDataSource {
		public:
			virtual void readNextBytes(uint8_t *pBuf,uint8_t bufsize,uint8_t *actuallyRead)=0;
			virtual ~JpegDataSource() {}
	};


	/**
	 * @brief Data source for reading from flash
	 * @ingroup Decoders
	 */

	class JpegFlashDataSource : public JpegDataSource {

		protected:
			uint32_t _memptr;
			uint32_t _memsize;

		public:

			/**
			 * Constructor
			 * @param memptr 32-bit address of the JPEG in flash.
			 * @param memsize The size of the JPEG file.
			 */

			JpegFlashDataSource(uint32_t memptr,uint32_t memsize)
			  : _memptr(memptr),
			    _memsize(memsize) {
			}


			/**
			 * Virtual destructor
			 */

			virtual ~JpegFlashDataSource() {}


			/**
			 * Get more bytes for the JPEG decoder. The full range of flash memory is supported.
			 * @param pBuf Where to store the bytes.
			 * @param bufsize How many bytes to try to read.
			 * @param[out] The number of bytes that we actually read.
			 */

			virtual void readNextBytes(uint8_t *pBuf,uint8_t bufsize,uint8_t *actuallyRead) {

				uint8_t count;

				count=_memsize<bufsize ? _memsize : bufsize;
				*actuallyRead=count;
				_memsize-=count;

				while(count--) {

					if(_memptr<=0xffff)
						*pBuf++=pgm_read_byte_near(_memptr++);
					else
						*pBuf++=pgm_read_byte_far(_memptr++);
				}
			}
	};


	/**
	 * @brief Data source for reading from the Arduino serial port
	 * @ingroup Decoders
	 */

	class JpegSerialDataSource : public JpegDataSource {

		protected:
			Stream *_serial;
			uint32_t _available;
			uint16_t _chunkSize;
			uint16_t _chunkAvailable;

		public:

			/**
			 * Constructor
			 * @param serial The Arduino serial port implementation
			 * @param jpegSize The size of the JPEG file
			 * @param chunkSize How much to read in a batch from the serial port before ACK'ing it.
			 */

			JpegSerialDataSource(Stream& serial,uint32_t jpegSize,uint16_t chunkSize)
			  : _serial(&serial),
			    _available(jpegSize),
			    _chunkSize(chunkSize),
			    _chunkAvailable(chunkSize) {
			}


			/**
			 * Virtual destructor
			 */

			virtual ~JpegSerialDataSource() {}


			/**
			 * Get more bytes for the JPEG decoder. The full range of flash memory is supported.
			 * @param pBuf Where to store the bytes.
			 * @param bufsize How many bytes to try to read.
			 * @param[out] The number of bytes that we actually read.
			 */

			virtual void readNextBytes(uint8_t *pBuf,uint8_t bufsize,uint8_t *actuallyRead) {

				uint8_t count;

				// will read up to the amount specified

				count=_available<bufsize ? _available : bufsize;
				*actuallyRead=count;
				_available-=count;

				// read each byte

				while(count--) {

					// read the next byte

					while(_serial->available()==0);
					*pBuf++=_serial->read();

					// software flow control - if we are at the end of a chunk then the sender
					// is waiting for us to write back 0xaa as a signal that it can send more data

					if(--_chunkAvailable==0) {
						_serial->write(0xaa);
						_chunkAvailable=_chunkSize;
					}

				}
			}
	};
}
