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
    ".global CloudPixels       \n\t"
    ".global CloudPixelsSize   \n\t"

    ".global FlagPixels        \n\t"
    ".global FlagPixelsSize    \n\t"

    ".global DocPixels         \n\t"
    ".global DocPixelsSize     \n\t"

    ".global GlobePixels       \n\t"
    ".global GlobePixelsSize   \n\t"

    ".global LogoPixels        \n\t"
    ".global LogoPixelsSize    \n\t"
 
    "CloudPixels:              \n\t"
    ".incbin \"libraries/xmemtft/examples/ILI9325/GraphicsLibraryDemo/cloud100x100.bin\" \n\t"
    "CloudPixelsSize=.-CloudPixels  \n\t"
    
    ".balign 2 \n\t"

    "LogoPixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/ILI9325/TrueType/logo.lzg\"\n\t"
    "LogoPixelsSize=.-LogoPixels\n\t"

    ".balign 2 \n\t"

    "GlobePixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/ILI9325/GraphicsLibraryDemo/globe.lzg\" \n\t"
    "GlobePixelsSize=.-GlobePixels \n\t"
 );
}
