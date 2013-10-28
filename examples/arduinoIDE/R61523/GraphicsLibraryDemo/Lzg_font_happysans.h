#pragma once

#include "Font.h"

namespace lcd {

  // helper so the user can just do 'new fontname' without having to know the parameters

  extern const struct FontChar FDEF_HAPPY_SANS_CHAR[];

  class Font_HAPPY_SANS_32 : public LzgFont {
    public:
      Font_HAPPY_SANS_32()
        : LzgFont(32,56,37,0,FDEF_HAPPY_SANS_CHAR) {
      }
  };
}
