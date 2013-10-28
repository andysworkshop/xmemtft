/*
 * Include the large bitmap binary directly into
 * flash, the location of which is at the discretion
 * of the linker. We export the address and the calculated
 * size to the C++ demo code with the .global directive
 *
 * YOU MUST REPLACE THE PATHNAME IN THE .incbin EXPRESSION
 * WITH THE CORRECT LOCATION ON YOUR SYSTEM. Either a
 * hardcoded pathname or anywhere on the -I search path
 * is good.
 */

void _asmStub() {

  __asm volatile(
    ".global RainPixels\n\t"
    ".global RainPixelsSize\n\t"

    ".global SunPixels\n\t"
    ".global SunPixelsSize\n\t"

    ".global PartlyCloudyPixels\n\t"
    ".global PartlyCloudyPixelsSize\n\t"

    ".global SnowPixels\n\t"
    ".global SnowPixelsSize\n\t"

    ".global PointPixels\n\t"
    ".global PointPixelsSize\n\t"

    ".global DegreePixels\n\t"
    ".global DegreePixelsSize\n\t"

    ".global ZeroPixels\n\t"
    ".global ZeroPixelsSize\n\t"

    ".global OnePixels\n\t"
    ".global OnePixelsSize\n\t"

    ".global TwoPixels\n\t"
    ".global TwoPixelsSize\n\t"

    ".global ThreePixels\n\t"
    ".global ThreePixelsSize\n\t"

    ".global FourPixels\n\t"
    ".global FourPixelsSize\n\t"

    ".global FivePixels\n\t"
    ".global FivePixelsSize\n\t"

    ".global SixPixels\n\t"
    ".global SixPixelsSize\n\t"

    ".global SevenPixels\n\t"
    ".global SevenPixelsSize\n\t"

    ".global EightPixels\n\t"
    ".global EightPixelsSize\n\t"

    ".global NinePixels\n\t"
    ".global NinePixelsSize\n\t"


    "RainPixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/R61523/Weather/rain.lzg\"\n\t"
    "RainPixelsSize=.-RainPixels\n\t"

    ".balign 2\n\t"

    "SunPixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/R61523/Weather/sun.lzg\"\n\t"
    "SunPixelsSize=.-SunPixels\n\t"

    ".balign 2\n\t"

    "PartlyCloudyPixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/R61523/Weather/partlyCloudy.lzg\"\n\t"
    "PartlyCloudyPixelsSize=.-PartlyCloudyPixels\n\t"

    ".balign 2\n\t"

    "SnowPixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/R61523/Weather/snow.lzg\"\n\t"
    "SnowPixelsSize=.-SnowPixels\n\t"

    ".balign 2\n\t"

    "DegreePixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/R61523/Weather/degree.lzg\"\n\t"
    "DegreePixelsSize=.-DegreePixels\n\t"

    ".balign 2\n\t"

    "PointPixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/R61523/Weather/point.lzg\"\n\t"
    "PointPixelsSize=.-PointPixels\n\t"

    ".balign 2\n\t"

    "ZeroPixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/R61523/Weather/0.lzg\"\n\t"
    "ZeroPixelsSize=.-ZeroPixels\n\t"

    ".balign 2\n\t"

    "OnePixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/R61523/Weather/1.lzg\"\n\t"
    "OnePixelsSize=.-OnePixels\n\t"

    ".balign 2\n\t"

    "TwoPixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/R61523/Weather/2.lzg\"\n\t"
    "TwoPixelsSize=.-TwoPixels\n\t"

    ".balign 2\n\t"

    "ThreePixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/R61523/Weather/3.lzg\"\n\t"
    "ThreePixelsSize=.-ThreePixels\n\t"

    ".balign 2\n\t"

    "FourPixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/R61523/Weather/4.lzg\"\n\t"
    "FourPixelsSize=.-FourPixels\n\t"

    ".balign 2\n\t"

    "FivePixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/R61523/Weather/5.lzg\"\n\t"
    "FivePixelsSize=.-FivePixels\n\t"

    ".balign 2\n\t"

    "SixPixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/R61523/Weather/6.lzg\"\n\t"
    "SixPixelsSize=.-SixPixels\n\t"

    ".balign 2\n\t"

    "SevenPixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/R61523/Weather/7.lzg\"\n\t"
    "SevenPixelsSize=.-SevenPixels\n\t"

    ".balign 2\n\t"

    "EightPixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/R61523/Weather/8.lzg\"\n\t"
    "EightPixelsSize=.-EightPixels\n\t"

    ".balign 2\n\t"

    "NinePixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/R61523/Weather/9.lzg\"\n\t"
    "NinePixelsSize=.-NinePixels\n\t"

    ".balign 2\n\t"
  );
}



