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

    ".global Test0Pixels\n\t"
    ".global Test0PixelsSize\n\t"

    ".global Test1Pixels\n\t"
    ".global Test1PixelsSize\n\t"

    ".global Test2Pixels\n\t"
    ".global Test2PixelsSize\n\t"

    ".global Test3Pixels\n\t"
    ".global Test3PixelsSize\n\t"

    ".global Test4Pixels\n\t"
    ".global Test4PixelsSize\n\t"


    "Test0Pixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/HX8347A/JpegFlash/test0.jpg\"\n\t"
    "Test0PixelsSize=.-Test0Pixels\n\t"

    ".balign 2\n\t"

    "Test1Pixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/HX8347A/JpegFlash/test1.jpg\"\n\t"
    "Test1PixelsSize=.-Test1Pixels\n\t"

    ".balign 2\n\t"

    "Test2Pixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/HX8347A/JpegFlash/test2.jpg\"\n\t"
    "Test2PixelsSize=.-Test2Pixels\n\t"

    ".balign 2\n\t"

    "Test3Pixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/HX8347A/JpegFlash/test3.jpg\"\n\t"
    "Test3PixelsSize=.-Test3Pixels\n\t"

    ".balign 2\n\t"

    "Test4Pixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/HX8347A/JpegFlash/test4.jpg\"\n\t"
    "Test4PixelsSize=.-Test4Pixels\n\t"

    ".balign 2\n\t"
  );
}

