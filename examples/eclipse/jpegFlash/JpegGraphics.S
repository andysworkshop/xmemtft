/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

.global Test0Pixels
.global Test0PixelsSize

.global Test1Pixels
.global Test1PixelsSize

.global Test2Pixels
.global Test2PixelsSize

.global Test3Pixels
.global Test3PixelsSize

.global Test4Pixels
.global Test4PixelsSize


Test0Pixels:
.incbin "p:/docs/source/arduino6300/jpegImages/test0.jpg"
Test0PixelsSize=.-Test0Pixels

.balign 2

Test1Pixels:
.incbin "p:/docs/source/arduino6300/jpegImages/test1.jpg"
Test1PixelsSize=.-Test1Pixels

.balign 2

Test2Pixels:
.incbin "p:/docs/source/arduino6300/jpegImages/test2.jpg"
Test2PixelsSize=.-Test2Pixels

.balign 2

Test3Pixels:
.incbin "p:/docs/source/arduino6300/jpegImages/test3.jpg"
Test3PixelsSize=.-Test3Pixels

.balign 2

Test4Pixels:
.incbin "p:/docs/source/arduino6300/jpegImages/test4.jpg"
Test4PixelsSize=.-Test4Pixels

.balign 2
