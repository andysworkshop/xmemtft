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

    "Test0Pixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/ILI9481/JpegFlash/test0.jpg\"\n\t"
    "Test0PixelsSize=.-Test0Pixels\n\t"

    ".balign 2\n\t"

    "Test1Pixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/ILI9481/JpegFlash/test1.jpg\"\n\t"
    "Test1PixelsSize=.-Test1Pixels\n\t"

    ".balign 2\n\t"
  );
}

