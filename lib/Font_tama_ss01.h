#pragma once

#include "Font.h"

namespace lcd {

  // helper so the user can just do 'new fontname' without having to know the parameters

  extern const struct FontChar FDEF_TAMA_SS01_CHAR[];

  class Font_TAMA_SS0117 : public Font {
    public:
      Font_TAMA_SS0117()
        : Font(32,95,13,2,FDEF_TAMA_SS01_CHAR) {
      }
  };
}
