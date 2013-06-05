/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

.global mp3PlayerOrigin
.global mp3PlayerSize

.global screenStripOrigin
.global screenStripSize

mp3PlayerOrigin:
.incbin "p:/docs/source/arduino6300/MediaPlayer.bin"
mp3PlayerSize=.-mp3PlayerOrigin

screenStripOrigin:
.incbin "p:/docs/source/arduino6300/ScreenStrip.bin"
screenStripSize=.-screenStripOrigin

.balign 2
