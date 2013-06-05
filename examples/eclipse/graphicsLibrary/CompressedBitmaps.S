/*
 * This file is a part of the open source stm32plus library.
 * Copyright (c) 2011,2012 Andy Brown <www.andybrown.me.uk>
 * Please see website for licensing terms.
 */

	.global GlobePixels
	.global GlobePixelsSize

/* ensure that this large data section is located at the end of .text so the code for
   the demo is located in lower memory */

	.section .fini1

GlobePixels:
	.incbin "generic565/globe.lzg"
	GlobePixelsSize=.-GlobePixels
