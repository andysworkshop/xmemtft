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
 * @file PanelConfiguration.h
 * @brief Enumerations for panel configuration.
 */

#pragma once


namespace lcd {

  /**
   * Possible locations for data
   */

  enum MemoryLocation {
    FLASH_UNCOMPRESSED,     ///< it's in flash (program) memory
    FLASH_COMPRESSED,       ///< it's in flash, and it's compressed
    SRAM                    ///< it's in the SRAM address space
  };


  /**
   * Possible display orientations
   */

  enum Orientation {
    PORTRAIT,               ///< long side up
    LANDSCAPE               ///< short side up
  };


  /**
   * Possible colour depths. Not every colour depth is guaranteed to be
   * supported by the driver embedded in the panel.
   */

  enum ColourDepth {
    COLOURS_16BIT,          ///< 64K colours
    COLOURS_18BIT,          ///< 262K colours
    COLOURS_24BIT           ///< 16M colours
  };


  /**
   * Possible directions (used by gradient fill)
   */

  enum Direction {
    HORIZONTAL,           ///< going horizontally
    VERTICAL              ///< going vertically
  };
}
