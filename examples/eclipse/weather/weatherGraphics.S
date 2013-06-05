/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

.global RainPixels
.global RainPixelsSize

.global SunPixels
.global SunPixelsSize

.global PartlyCloudyPixels
.global PartlyCloudyPixelsSize

.global SnowPixels
.global SnowPixelsSize

.global PointPixels
.global PointPixelsSize

.global DegreePixels
.global DegreePixelsSize

.global ZeroPixels
.global ZeroPixelsSize

.global OnePixels
.global OnePixelsSize

.global TwoPixels
.global TwoPixelsSize

.global ThreePixels
.global ThreePixelsSize

.global FourPixels
.global FourPixelsSize

.global FivePixels
.global FivePixelsSize

.global SixPixels
.global SixPixelsSize

.global SevenPixels
.global SevenPixelsSize

.global EightPixels
.global EightPixelsSize

.global NinePixels
.global NinePixelsSize


RainPixels:
.incbin "p:/docs/source/arduino6300/weatherImages/rain.lzg"
RainPixelsSize=.-RainPixels

.balign 2

SunPixels:
.incbin "p:/docs/source/arduino6300/weatherImages/sun.lzg"
SunPixelsSize=.-SunPixels

.balign 2

PartlyCloudyPixels:
.incbin "p:/docs/source/arduino6300/weatherImages/partlyCloudy.lzg"
PartlyCloudyPixelsSize=.-PartlyCloudyPixels

.balign 2

SnowPixels:
.incbin "p:/docs/source/arduino6300/weatherImages/snow.lzg"
SnowPixelsSize=.-SnowPixels

.balign 2

DegreePixels:
.incbin "p:/docs/source/arduino6300/weatherImages/degree.lzg"
DegreePixelsSize=.-DegreePixels

.balign 2

PointPixels:
.incbin "p:/docs/source/arduino6300/weatherImages/point.lzg"
PointPixelsSize=.-PointPixels

.balign 2

ZeroPixels:
.incbin "p:/docs/source/arduino6300/weatherImages/0.lzg"
ZeroPixelsSize=.-ZeroPixels

.balign 2

OnePixels:
.incbin "p:/docs/source/arduino6300/weatherImages/1.lzg"
OnePixelsSize=.-OnePixels

.balign 2

TwoPixels:
.incbin "p:/docs/source/arduino6300/weatherImages/2.lzg"
TwoPixelsSize=.-TwoPixels

.balign 2

ThreePixels:
.incbin "p:/docs/source/arduino6300/weatherImages/3.lzg"
ThreePixelsSize=.-ThreePixels

.balign 2

FourPixels:
.incbin "p:/docs/source/arduino6300/weatherImages/4.lzg"
FourPixelsSize=.-FourPixels

.balign 2

FivePixels:
.incbin "p:/docs/source/arduino6300/weatherImages/5.lzg"
FivePixelsSize=.-FivePixels

.balign 2

SixPixels:
.incbin "p:/docs/source/arduino6300/weatherImages/6.lzg"
SixPixelsSize=.-SixPixels

.balign 2

SevenPixels:
.incbin "p:/docs/source/arduino6300/weatherImages/7.lzg"
SevenPixelsSize=.-SevenPixels

.balign 2

EightPixels:
.incbin "p:/docs/source/arduino6300/weatherImages/8.lzg"
EightPixelsSize=.-EightPixels

.balign 2

NinePixels:
.incbin "p:/docs/source/arduino6300/weatherImages/9.lzg"
NinePixelsSize=.-NinePixels

.balign 2
