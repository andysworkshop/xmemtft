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
 * @file R61523Orientation.h
 * @brief Generic template definition.
 * @ingroup R61523
 */

#pragma once


namespace lcd {


  /**
   * @brief Forward declaration of the R61523Orientation template
   * Empty generic class definition for R61523 orientation-dependent operations
   * Everything is provided in the specialisations.
   * @ingroup R61523
   */

  template<Orientation TOrientation,class TAccessMode>
  class R61523Orientation {
  };
}


/*
 * Now include the specialisations
 */

#include "R61523PortraitSpecialisation.h"
#include "R61523LandscapeSpecialisation.h"
