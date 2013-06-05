/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

	.global CloudPixels
	.global CloudPixelsSize

/* ensure that this large data section is located at the end of .text so the code for
   the demo is located in lower memory */

	.section .fini1

CloudPixels:
	.incbin "generic565/cloud100x100.bin"
	CloudPixelsSize=.-CloudPixels
