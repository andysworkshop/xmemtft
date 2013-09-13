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

/*
 * Implementation for Adafruit TFT LCD copyright (c) 2013 Colin Irwin, see
 * http://aethersdr.org/ for details. Provided under original terms and
 * conditions.
 */

/**
 * @file ILI9325Orientation.h
 * @brief Generic template definition.
 * @ingroup ILI9325
 */

#pragma once

namespace lcd {

  /**
   * @brief Forward declaration of the ILI9325Orientation template
   * Empty generic class definition for ILI9325 orientation-dependent operations
   * Everything is provided in the specialisations.
   * @ingroup ILI9325
   */

  template<Orientation TOrientation,class TAccessMode>
  class ILI9325Orientation {
  };
}

/*
 * Now include the specialisations
 */

#include "ILI9325PortraitSpecialisation.h"
#include "ILI9325LandscapeSpecialisation.h"
