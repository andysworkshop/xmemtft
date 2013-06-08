/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012,2013 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

void _asmStub() {
 
  __asm volatile(

    ".global mediaPlayerOrigin             \n\t"
    ".global mediaPlayerSize               \n\t"
  
    ".global screenStripOrigin             \n\t"
    ".global screenStripSize               \n\t"
  
    "mediaPlayerOrigin:                    \n\t"
    ".incbin \"libraries/xmemtft/examples/NokiaQVGA/MediaPlayer/MediaPlayer.bin\"\n\t"
    "mediaPlayerSize=.-mediaPlayerOrigin   \n\t"
  
    "screenStripOrigin:                    \n\t"
    ".incbin \"libraries/xmemtft/examples/NokiaQVGA/MediaPlayer/ScreenStrip.bin\"\n\t"
    "screenStripSize=.-screenStripOrigin   \n\t"
    
    ".balign 2 \n\t"
  );
}

