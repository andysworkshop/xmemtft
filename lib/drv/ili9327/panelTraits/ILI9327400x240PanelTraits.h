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
 * @file ILI9327400x240PanelTraits.h
 * @brief Panel traits for a 400x240 ILI9327 panel
 * @ingroup ILI9327
 */


#pragma once


namespace lcd {


  /**
   * Traits class for the ILI9327 that declares a "short" panel
   * of 400x240, less than the driver maximum of 432x240
   * @ingroup ILI9327
   */

  class ILI9327400x240PanelTraits {

    public:
      enum {
        LONG_SIDE = 400,            ///< this panel is 400 on the long side
        SHORT_SIDE = 240            ///< this panel is 240 on the short side
      };
  };
}
