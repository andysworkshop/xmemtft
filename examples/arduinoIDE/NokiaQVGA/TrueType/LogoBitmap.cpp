/*
 * Include the large bitmap binary directly into
 * flash, the location of which is at the discretion
 * of the linker. We export the address and the calculated
 * size to the C++ demo code with the .global directive
 */

void _asmStub() {

  __asm volatile(
    ".global LogoPixels\n\t"
    ".global LogoPixelsSize\n\t"
  
    "LogoPixels:\n\t"
    ".incbin \"libraries/xmemtft/examples/NokiaQVGA/TrueType/logo.lzg\"\n\t"
    "LogoPixelsSize=.-LogoPixels\n\t"

    ".balign 2 \n\t"
  );
}
