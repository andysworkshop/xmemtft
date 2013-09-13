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
 *
 */

#pragma once

#include <Arduino.h>
#include <avr/pgmspace.h>
#include "PanelConfiguration.h"
#include "gl/Point.h"
#include "gl/Rectangle.h"
#include "gl/Size.h"
#include "gl/Bitmap.h"
#include "gl/DoublePrecision.h"
#include "gl/ColourNames.h"
#include "drv/accessModes/AdafruitAccessMode.h"
#include "drv/ili9325/ILI9325.h"
#include "GetFarAddress.h"
#include "Font.h"
#include "decoders/PicoJpeg.h"
#include "decoders/LzgFlashDecoder.h"
#include "gl/GraphicsLibrary.h"
#include "Backlight.h"
#include "terminal/TerminalPortraitImpl.h"
#include "terminal/TerminalLandscapeImpl.h"

namespace lcd {

  /*
   * Backlight PWM control is available for the Adafruit LCD on pin #3
   */

  typedef Backlight<3> DefaultBacklight;

  /*
   * Adafruit GPIO interface: 65K colours, portrait and landscape
   */

  typedef GraphicsLibrary<ILI9325<PORTRAIT,COLOURS_16BIT,AdafruitAccessMode>,AdafruitAccessMode> Adafruit_Portrait_65K_Gpio;
  typedef GraphicsLibrary<ILI9325<LANDSCAPE,COLOURS_16BIT,AdafruitAccessMode>,AdafruitAccessMode> Adafruit_Landscape_65K_Gpio;

  typedef TerminalPortraitImpl<Adafruit_Portrait_65K_Gpio> Adafruit_Terminal_Portrait_65K_Gpio;
  typedef TerminalLandscapeImpl<Adafruit_Landscape_65K_Gpio> Adafruit_Terminal_Landscape_65K_Gpio;

  /*
   * Adafruit GPIO interface: 262K colours, portrait and landscape
   */

  typedef GraphicsLibrary<ILI9325<PORTRAIT,COLOURS_18BIT,AdafruitAccessMode>,AdafruitAccessMode> Adafruit_Portrait_262K_Gpio;
  typedef GraphicsLibrary<ILI9325<LANDSCAPE,COLOURS_18BIT,AdafruitAccessMode>,AdafruitAccessMode> Adafruit_Landscape_262K_Gpio;

  typedef TerminalPortraitImpl<Adafruit_Portrait_262K_Gpio> Adafruit_Terminal_Portrait_262K_Gpio;
  typedef TerminalLandscapeImpl<Adafruit_Landscape_262K_Gpio> Adafruit_Terminal_Landscape_262K_Gpio;
}
