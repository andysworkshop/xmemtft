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
 * @file R61523Colour.h
 * @brief Generic template definition.
 * @ingroup R61523
 */

#pragma once


namespace lcd {

  /**
   * @brief Forward declaration of the R61523Colour template
   *
   * Empty generic class definition for R61523 colour-dependent operations
   * Everything is provided in the specialisations.
   *
   * @ingroup R61523
   */

  template<ColourDepth TColour,class TAccessMode>
  class R61523Colour;
}


/*
 * Now include the specialisations
 */

#include "R61523Colour16Specialisation.h"
#include "R61523Colour18Specialisation.h"
#include "R61523Colour24Specialisation.h"
