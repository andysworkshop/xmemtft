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

/**
 * @file Font.cpp
 * @brief FontBase implementation.
 * @ingroup Fonts
 */

#include <avr/pgmspace.h>
#include <stdlib.h>
#include <stddef.h>
#include "Font.h"


namespace lcd {

  /**
   * Get the font character definition in progmem space
   * @param character The character code.
   * @param fc The strucutre to fill in.
   */

  void FontBase::getCharacter(uint8_t character,FontChar& fc) const {

    const FontChar *ptr;
    uint8_t c;
    int16_t i;

    // the bulk of the characters are in sequential order, see if we can
    // index directly into the character array to find it

    if(character>=_firstCharacter && character<_lastCharacter) {

      // the character is in range and indexable, is it in sequential place?

      if(character-_firstCharacter<_characterCount && _characters[character-_firstCharacter].Code==character) {

        ptr=&_characters[character-_firstCharacter];
        c=pgm_read_byte(reinterpret_cast<const uint8_t *>(ptr)+offsetof(FontChar,Code));

        // ...ok you can start looking again

        if(c==character) {
          memcpy_P(&fc,ptr,sizeof(FontChar));
          return;
        }
      }
    }

    // did't find it, search for it going backwards because the likelihood is that
    // it's towards the end of the array

    for(i=_characterCount-1;i>=0;i--) {

      // this is the stuff that gives C a bad name...

      ptr=&_characters[i];
      c=pgm_read_byte(reinterpret_cast<const uint8_t *>(ptr)+offsetof(FontChar,Code));

      // ...ok you can start looking again

      if(c==character) {
        memcpy_P(&fc,ptr,sizeof(FontChar));
        return;
      }
    }

    ptr=&_characters[1];    // default to first char if not found
    memcpy_P(&fc,ptr,sizeof(fc));
  }
}
