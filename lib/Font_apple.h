#pragma once

#include "Font.h"

namespace lcd {

  // helper so the user can just do 'new fontname' without having to know the parameters

  extern const struct FontChar FDEF_APPLE_CHAR[];

  class Font_APPLE8 : public Font {
    public:
      Font_APPLE8()
        : Font(32,95,8,0,FDEF_APPLE_CHAR) {
      }
  };
}
