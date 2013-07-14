# A C++ graphics library for the Arduino #

xmemtft is a modular, optimised, object oriented graphics library for driving TFT panels on the Arduino. It is primarily targeted at the Arduino Mega but most of its functionality is available on the standard Arduino.

Features include:

* Graphics primitives: lines, ellipse, rectangles, gradients etc.
* TrueType proportionally-spaced fonts.
* Compressed PNG-style graphics.
* JPEG decompression and display.
* External memory (XMEM) and [highly optimised](http://andybrown.me.uk/wk/2013/06/08/a-generic-16-bit-lcd-adaptor-for-the-arduino) GPIO interfaces.

The main documentation for this library can be found at my website in a number of articles supported by demo code and videos on YouTube:

[Nokia QVGA TFT LCD Graphics Library](http://andybrown.me.uk/wk/2012/06/04/nokia-qvga-tft-lcd-for-the-arduino-mega-graphics-library-part-2-of-2/)
<br/>
[Interfacing the Nokia 6300 QVGA to the standard Arduino](http://andybrown.me.uk/wk/2012/07/28/interfacing-the-nokia-6300-qvga-tft-to-the-standard-arduino/)
<br/>
[Nokia N82 2.4" QVGA TFT on the Arduino](http://andybrown.me.uk/wk/2012/08/19/nokia-n82-arduino/)
<br/>
[Reverse engineering the Nokia N95 8Gb QVGA LCD](http://andybrown.me.uk/wk/2012/11/03/nokia-n95-8gb-lcd/)
<br/>
[Reverse engineering the Nokia N93 QVGA LCD](http://andybrown.me.uk/wk/2013/01/26/nokia-n93-lcd/)
<br/>
[Reverse engineering the Nokia E73 QVGA LCD](http://andybrown.me.uk/wk/2013/05/29/nokia-e73-qvga-lcd/)
<br/>
[A generic 16-bit LCD adaptor for the Arduino](http://andybrown.me.uk/wk/2013/06/08/a-generic-16-bit-lcd-adaptor-for-the-arduino)

# Installation #

Visit my [downloads page](http://andybrown.me.uk/wk/downloads) to download a package that you can just unzip into your Arduino IDE's `libraries` subdirectory. The next time you restart the Arduino IDE you will see that all the examples are available via the IDE menu.

# Supported panels

The following are supported using the external memory (XMEM) access mode:

* Nokia 6300
* Nokia N82
* Nokia N95 8Gb
* Nokia N93
* Nokia E73

The following are supported using my [generic 16-bit LCD adaptor](http://andybrown.me.uk/wk/2013/06/08/a-generic-16-bit-lcd-adaptor-for-the-arduino) running the highly optimised GPIO driver. Additionally, the Adafruit ILI9325 shield is supported via a driver contributed by [Colin Irwin](http://www.lagrangianpoint.net).

* ILI9325
* ILI9327
* ILI9481
* HX8347A

# Contributing

Contributions to xmemtft are welcome. Please follow these steps to ensure a smooth workflow:

* Clone the main xmemtft repo into your personal account and create a branch off `master` for your work. Give it a short meaningful name that allows people to get a good idea _at-a-glance_ of what you've done.

* Write your contribution while trying to stay within the coding style evident within the library.

* When you're happy with your code, first do a merge back from the current master to ensure you're still compatible and then send me a pull request. I will code-review the pull-request and when we're all happy I will accept it and do the merge back into `master`.

From time to time I will take the current master branch, tag it with a version number and create a zip package on my website's [downloads page](http://andybrown.me.uk/wk/downloads) that people can use to install the driver into the Arduino IDE.