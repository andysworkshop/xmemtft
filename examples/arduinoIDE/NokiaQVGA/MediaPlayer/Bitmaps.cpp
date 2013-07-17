/*
  XMEM LCD Library for the Arduino

  Copyright 2012,2013 Andrew Brown

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This notice may not be removed or altered from any source distribution.
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

