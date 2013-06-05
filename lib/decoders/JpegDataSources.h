/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012,2013 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

#pragma once


namespace lcd {

	/*
	 * Base class for Jpeg data sources
	 */

	class JpegDataSource {
		public:
			virtual void readNextBytes(uint8_t *pBuf,uint8_t bufsize,uint8_t *actuallyRead)=0;
			virtual ~JpegDataSource() {}
	};


	/*
	 * Data source for reading from flash
	 */

	class JpegFlashDataSource : public JpegDataSource {

		protected:
			uint32_t _memptr;
			uint32_t _memsize;

		public:

			JpegFlashDataSource(uint32_t memptr,uint32_t memsize)
			  : _memptr(memptr),
			    _memsize(memsize) {
			}

			virtual ~JpegFlashDataSource() {}

			/*
			 * Get more bytes for the JPEG decoder
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


	/*
	 * Data source for reading from the Arduino serial port
	 */

	class JpegSerialDataSource : public JpegDataSource {

		protected:
			Stream *_serial;
			uint32_t _available;
			uint16_t _chunkSize;
			uint16_t _chunkAvailable;

		public:
			JpegSerialDataSource(Stream& serial,uint32_t jpegSize,uint16_t chunkSize)
			  : _serial(&serial),
			    _available(jpegSize),
			    _chunkSize(chunkSize),
			    _chunkAvailable(chunkSize) {
			}

			virtual ~JpegSerialDataSource() {}

			/*
			 * Get more bytes for the JPEG decoder
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
