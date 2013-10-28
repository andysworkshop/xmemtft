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
 * @file Nokia6300.h
 * @brief Typedefs for using the Nokia 6300 panel
 * @ingroup MC2PA8201
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
#include "drv/accessModes/XmemAccessMode.h"
#include "drv/accessModes/GpioAccessMode.h"
#include "drv/mc2pa8201/panelTraits/Nokia6300_TypeA.h"
#include "drv/mc2pa8201/panelTraits/Nokia6300_TypeB.h"
#include "drv/mc2pa8201/panelTraits/Nokia6300_TypeC.h"
#include "drv/mc2pa8201/MC2PA8201.h"
#include "GetFarAddress.h"
#include "Font.h"
#include "decoders/PicoJpeg.h"
#include "decoders/LzgFlashDecoder.h"
#include "gl/GraphicsLibrary.h"
#include "Backlight.h"
#include "terminal/TerminalPortraitImpl.h"
#include "terminal/TerminalLandscapeImpl.h"


namespace lcd {

  #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)

  /*
   * Nokia 6300 XMEM type A interface: 64K, 262K, 16M colours, portrait and landscape
   */

  typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_16BIT,XmemAccessMode,Nokia6300_TypeA>,XmemAccessMode> Nokia6300_Portrait_64K;
  typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_16BIT,XmemAccessMode,Nokia6300_TypeA>,XmemAccessMode> Nokia6300_Landscape_64K;

  typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_18BIT,XmemAccessMode,Nokia6300_TypeA>,XmemAccessMode> Nokia6300_Portrait_262K;
  typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_18BIT,XmemAccessMode,Nokia6300_TypeA>,XmemAccessMode> Nokia6300_Landscape_262K;

  typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_24BIT,XmemAccessMode,Nokia6300_TypeA>,XmemAccessMode> Nokia6300_Portrait_16M;
  typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_24BIT,XmemAccessMode,Nokia6300_TypeA>,XmemAccessMode> Nokia6300_Landscape_16M;

  typedef TerminalPortraitImpl<Nokia6300_Portrait_64K> Nokia6300_Terminal_Portrait_64K;
  typedef TerminalLandscapeImpl<Nokia6300_Landscape_64K> Nokia6300_Terminal_Landscape_64K;

  typedef TerminalPortraitImpl<Nokia6300_Portrait_262K> Nokia6300_Terminal_Portrait_262K;
  typedef TerminalLandscapeImpl<Nokia6300_Landscape_262K> Nokia6300_Terminal_Landscape_262K;

  typedef TerminalPortraitImpl<Nokia6300_Portrait_16M> Nokia6300_Terminal_Portrait_16M;
  typedef TerminalLandscapeImpl<Nokia6300_Landscape_16M> Nokia6300_Terminal_Landscape_16M;

  /*
   * Nokia 6300 XMEM type B interface: 64K, 262K, 16M colours, portrait and landscape
   */

  typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_16BIT,XmemAccessMode,Nokia6300_TypeB>,XmemAccessMode> Nokia6300_Portrait_64K_TypeB;
  typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_16BIT,XmemAccessMode,Nokia6300_TypeB>,XmemAccessMode> Nokia6300_Landscape_64K_TypeB;

  typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_18BIT,XmemAccessMode,Nokia6300_TypeB>,XmemAccessMode> Nokia6300_Portrait_262K_TypeB;
  typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_18BIT,XmemAccessMode,Nokia6300_TypeB>,XmemAccessMode> Nokia6300_Landscape_262K_TypeB;

  typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_24BIT,XmemAccessMode,Nokia6300_TypeB>,XmemAccessMode> Nokia6300_Portrait_16M_TypeB;
  typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_24BIT,XmemAccessMode,Nokia6300_TypeB>,XmemAccessMode> Nokia6300_Landscape_16M_TypeB;

  typedef TerminalPortraitImpl<Nokia6300_Portrait_64K_TypeB> Nokia6300_Terminal_Portrait_64K_TypeB;
  typedef TerminalLandscapeImpl<Nokia6300_Landscape_64K_TypeB> Nokia6300_Terminal_Landscape_64K_TypeB;

  typedef TerminalPortraitImpl<Nokia6300_Portrait_262K_TypeB> Nokia6300_Terminal_Portrait_262K_TypeB;
  typedef TerminalLandscapeImpl<Nokia6300_Landscape_262K_TypeB> Nokia6300_Terminal_Landscape_262K_TypeB;

  typedef TerminalPortraitImpl<Nokia6300_Portrait_16M_TypeB> Nokia6300_Terminal_Portrait_16M_TypeB;
  typedef TerminalLandscapeImpl<Nokia6300_Landscape_16M_TypeB> Nokia6300_Terminal_Landscape_16M_TypeB;

  /*
   * Nokia 6300 XMEM type C interface: 64K, 262K, 16M colours, portrait and landscape
   */

  typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_16BIT,XmemAccessMode,Nokia6300_TypeC>,XmemAccessMode> Nokia6300_Portrait_64K_TypeC;
  typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_16BIT,XmemAccessMode,Nokia6300_TypeC>,XmemAccessMode> Nokia6300_Landscape_64K_TypeC;

  typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_18BIT,XmemAccessMode,Nokia6300_TypeC>,XmemAccessMode> Nokia6300_Portrait_262K_TypeC;
  typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_18BIT,XmemAccessMode,Nokia6300_TypeC>,XmemAccessMode> Nokia6300_Landscape_262K_TypeC;

  typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_24BIT,XmemAccessMode,Nokia6300_TypeC>,XmemAccessMode> Nokia6300_Portrait_16M_TypeC;
  typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_24BIT,XmemAccessMode,Nokia6300_TypeC>,XmemAccessMode> Nokia6300_Landscape_16M_TypeC;

  typedef TerminalPortraitImpl<Nokia6300_Portrait_64K_TypeC> Nokia6300_Terminal_Portrait_64K_TypeC;
  typedef TerminalLandscapeImpl<Nokia6300_Landscape_64K_TypeC> Nokia6300_Terminal_Landscape_64K_TypeC;

  typedef TerminalPortraitImpl<Nokia6300_Portrait_262K_TypeC> Nokia6300_Terminal_Portrait_262K_TypeC;
  typedef TerminalLandscapeImpl<Nokia6300_Landscape_262K_TypeC> Nokia6300_Terminal_Landscape_262K_TypeC;

  typedef TerminalPortraitImpl<Nokia6300_Portrait_16M_TypeC> Nokia6300_Terminal_Portrait_16M_TypeC;
  typedef TerminalLandscapeImpl<Nokia6300_Landscape_16M_TypeC> Nokia6300_Terminal_Landscape_16M_TypeC;

  /*
   * The default for most people is a PWM output on pin #2
   */

  typedef Backlight<2> DefaultBacklight;

  #else     // !mega1280 && !mega2560

  /*
   * Pins 0..9 are used on the 328P for IO so we'll default the backlight to PWM pin #10
   */

  typedef Backlight<10> DefaultBacklight;

  #endif    // mega1280/mega2560

  /*
   * Nokia 6300 GPIO type A interface: 64K, 262K, 16M colours, portrait and landscape
   */

  typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_16BIT,GpioAccessMode,Nokia6300_TypeA>,GpioAccessMode> Nokia6300_Portrait_64K_Gpio;
  typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_16BIT,GpioAccessMode,Nokia6300_TypeA>,GpioAccessMode> Nokia6300_Landscape_64K_Gpio;

  typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_18BIT,GpioAccessMode,Nokia6300_TypeA>,GpioAccessMode> Nokia6300_Portrait_262K_Gpio;
  typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_18BIT,GpioAccessMode,Nokia6300_TypeA>,GpioAccessMode> Nokia6300_Landscape_262K_Gpio;

  typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_24BIT,GpioAccessMode,Nokia6300_TypeA>,GpioAccessMode> Nokia6300_Portrait_16M_Gpio;
  typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_24BIT,GpioAccessMode,Nokia6300_TypeA>,GpioAccessMode> Nokia6300_Landscape_16M_Gpio;

  typedef TerminalPortraitImpl<Nokia6300_Portrait_64K_Gpio> Nokia6300_Terminal_Portrait_64K_Gpio;
  typedef TerminalLandscapeImpl<Nokia6300_Landscape_64K_Gpio> Nokia6300_Terminal_Landscape_64K_Gpio;

  typedef TerminalPortraitImpl<Nokia6300_Portrait_262K_Gpio> Nokia6300_Terminal_Portrait_262K_Gpio;
  typedef TerminalLandscapeImpl<Nokia6300_Landscape_262K_Gpio> Nokia6300_Terminal_Landscape_262K_Gpio;

  typedef TerminalPortraitImpl<Nokia6300_Portrait_16M_Gpio> Nokia6300_Terminal_Portrait_16M_Gpio;
  typedef TerminalLandscapeImpl<Nokia6300_Landscape_16M_Gpio> Nokia6300_Terminal_Landscape_16M_Gpio;

  /*
   * Nokia 6300 GPIO type B interface: 64K, 262K, 16M colours, portrait and landscape
   */

  typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_16BIT,GpioAccessMode,Nokia6300_TypeB>,GpioAccessMode> Nokia6300_Portrait_64K_TypeB_Gpio;
  typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_16BIT,GpioAccessMode,Nokia6300_TypeB>,GpioAccessMode> Nokia6300_Landscape_64K_TypeB_Gpio;

  typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_18BIT,GpioAccessMode,Nokia6300_TypeB>,GpioAccessMode> Nokia6300_Portrait_262K_TypeB_Gpio;
  typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_18BIT,GpioAccessMode,Nokia6300_TypeB>,GpioAccessMode> Nokia6300_Landscape_262K_TypeB_Gpio;

  typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_24BIT,GpioAccessMode,Nokia6300_TypeB>,GpioAccessMode> Nokia6300_Portrait_16M_TypeB_Gpio;
  typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_24BIT,GpioAccessMode,Nokia6300_TypeB>,GpioAccessMode> Nokia6300_Landscape_16M_TypeB_Gpio;

  typedef TerminalPortraitImpl<Nokia6300_Portrait_64K_TypeB_Gpio> Nokia6300_Terminal_Portrait_64K_TypeB_Gpio;
  typedef TerminalLandscapeImpl<Nokia6300_Landscape_64K_TypeB_Gpio> Nokia6300_Terminal_Landscape_64K_TypeB_Gpio;

  typedef TerminalPortraitImpl<Nokia6300_Portrait_262K_TypeB_Gpio> Nokia6300_Terminal_Portrait_262K_TypeB_Gpio;
  typedef TerminalLandscapeImpl<Nokia6300_Landscape_262K_TypeB_Gpio> Nokia6300_Terminal_Landscape_262K_TypeB_Gpio;

  typedef TerminalPortraitImpl<Nokia6300_Portrait_16M_TypeB_Gpio> Nokia6300_Terminal_Portrait_16M_TypeB_Gpio;
  typedef TerminalLandscapeImpl<Nokia6300_Landscape_16M_TypeB_Gpio> Nokia6300_Terminal_Landscape_16M_TypeB_Gpio;

  /*
   * Nokia 6300 GPIO type C interface: 64K, 262K, 16M colours, portrait and landscape
   */

  typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_16BIT,GpioAccessMode,Nokia6300_TypeC>,GpioAccessMode> Nokia6300_Portrait_64K_TypeC_Gpio;
  typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_16BIT,GpioAccessMode,Nokia6300_TypeC>,GpioAccessMode> Nokia6300_Landscape_64K_TypeC_Gpio;

  typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_18BIT,GpioAccessMode,Nokia6300_TypeC>,GpioAccessMode> Nokia6300_Portrait_262K_TypeC_Gpio;
  typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_18BIT,GpioAccessMode,Nokia6300_TypeC>,GpioAccessMode> Nokia6300_Landscape_262K_TypeC_Gpio;

  typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_24BIT,GpioAccessMode,Nokia6300_TypeC>,GpioAccessMode> Nokia6300_Portrait_16M_TypeC_Gpio;
  typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_24BIT,GpioAccessMode,Nokia6300_TypeC>,GpioAccessMode> Nokia6300_Landscape_16M_TypeC_Gpio;

  typedef TerminalPortraitImpl<Nokia6300_Portrait_64K_TypeC_Gpio> Nokia6300_Terminal_Portrait_64K_TypeC_Gpio;
  typedef TerminalLandscapeImpl<Nokia6300_Landscape_64K_TypeC_Gpio> Nokia6300_Terminal_Landscape_64K_TypeC_Gpio;

  typedef TerminalPortraitImpl<Nokia6300_Portrait_262K_TypeC_Gpio> Nokia6300_Terminal_Portrait_262K_TypeC_Gpio;
  typedef TerminalLandscapeImpl<Nokia6300_Landscape_262K_TypeC_Gpio> Nokia6300_Terminal_Landscape_262K_TypeC_Gpio;

  typedef TerminalPortraitImpl<Nokia6300_Portrait_16M_TypeC_Gpio> Nokia6300_Terminal_Portrait_16M_TypeC_Gpio;
  typedef TerminalLandscapeImpl<Nokia6300_Landscape_16M_TypeC_Gpio> Nokia6300_Terminal_Landscape_16M_TypeC_Gpio;
}


