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
    ".global GlobePixels\n\t"
    ".global GlobePixelsSize\n\t"
  
    "GlobePixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/NokiaQVGA/SimpleBitmap/globe64x64.bin\"\n\t"
    "GlobePixelsSize=.-GlobePixels\n\t"

    ".balign 2 \n\t"
  );
}
