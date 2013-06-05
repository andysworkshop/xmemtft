/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

	.global LogoPixels
	.global LogoPixelsSize

LogoPixels:
	.incbin "p:/docs/source/arduino6300/ttgraphics/logo.lzg"
	LogoPixelsSize=.-LogoPixels
