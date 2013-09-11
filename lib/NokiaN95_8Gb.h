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
 * @file NokiaN95_8Gb.h
 * @brief Typedefs for using the Nokia N95 8Gb panel
 * @ingroup LDS285
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
#include "drv/lds285/panelTraits/NokiaN95_8Gb_TypeA.h"
#include "drv/lds285/panelTraits/NokiaN95_8Gb_TypeB.h"
#include "drv/lds285/LDS285.h"
#include "drv/lds285/LDS285Backlight.h"
#include "GetFarAddress.h"
#include "Font.h"
#include "decoders/PicoJpeg.h"
#include "decoders/LzgFlashDecoder.h"
#include "gl/GraphicsLibrary.h"
#include "terminal/TerminalPortraitImpl.h"
#include "terminal/TerminalLandscapeImpl.h"


namespace lcd {

  #if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)

  /*
   * Nokia N95 8Gb XMEM type A interface: 64K, 262K, 16M colours, portrait and landscape
   */

  typedef GraphicsLibrary<LDS285<PORTRAIT,COLOURS_16BIT,XmemAccessMode,NokiaN95_8Gb_TypeA>,XmemAccessMode> NokiaN95_8Gb_Portrait_64K;
  typedef GraphicsLibrary<LDS285<LANDSCAPE,COLOURS_16BIT,XmemAccessMode,NokiaN95_8Gb_TypeA>,XmemAccessMode> NokiaN95_8Gb_Landscape_64K;

  typedef GraphicsLibrary<LDS285<PORTRAIT,COLOURS_18BIT,XmemAccessMode,NokiaN95_8Gb_TypeA>,XmemAccessMode> NokiaN95_8Gb_Portrait_262K;
  typedef GraphicsLibrary<LDS285<LANDSCAPE,COLOURS_18BIT,XmemAccessMode,NokiaN95_8Gb_TypeA>,XmemAccessMode> NokiaN95_8Gb_Landscape_262K;

  typedef GraphicsLibrary<LDS285<PORTRAIT,COLOURS_24BIT,XmemAccessMode,NokiaN95_8Gb_TypeA>,XmemAccessMode> NokiaN95_8Gb_Portrait_16M;
  typedef GraphicsLibrary<LDS285<LANDSCAPE,COLOURS_24BIT,XmemAccessMode,NokiaN95_8Gb_TypeA>,XmemAccessMode> NokiaN95_8Gb_Landscape_16M;

  typedef TerminalPortraitImpl<NokiaN95_8Gb_Portrait_64K> NokiaN95_8Gb_Terminal_Portrait_64K;
  typedef TerminalLandscapeImpl<NokiaN95_8Gb_Landscape_64K> NokiaN95_8Gb_Terminal_Landscape_64K;

  typedef TerminalPortraitImpl<NokiaN95_8Gb_Portrait_262K> NokiaN95_8Gb_Terminal_Portrait_262K;
  typedef TerminalLandscapeImpl<NokiaN95_8Gb_Landscape_262K> NokiaN95_8Gb_Terminal_Landscape_262K;

  typedef TerminalPortraitImpl<NokiaN95_8Gb_Portrait_16M> NokiaN95_8Gb_Terminal_Portrait_16M;
  typedef TerminalLandscapeImpl<NokiaN95_8Gb_Landscape_16M> NokiaN95_8Gb_Terminal_Landscape_16M;

  /*
   * Nokia N95 8Gb XMEM type B interface: 64K, 262K, 16M colours, portrait and landscape
   */

  typedef GraphicsLibrary<LDS285<PORTRAIT,COLOURS_16BIT,XmemAccessMode,NokiaN95_8Gb_TypeB>,XmemAccessMode> NokiaN95_8Gb_Portrait_64K_TypeB;
  typedef GraphicsLibrary<LDS285<LANDSCAPE,COLOURS_16BIT,XmemAccessMode,NokiaN95_8Gb_TypeB>,XmemAccessMode> NokiaN95_8Gb_Landscape_64K_TypeB;

  typedef GraphicsLibrary<LDS285<PORTRAIT,COLOURS_18BIT,XmemAccessMode,NokiaN95_8Gb_TypeB>,XmemAccessMode> NokiaN95_8Gb_Portrait_262K_TypeB;
  typedef GraphicsLibrary<LDS285<LANDSCAPE,COLOURS_18BIT,XmemAccessMode,NokiaN95_8Gb_TypeB>,XmemAccessMode> NokiaN95_8Gb_Landscape_262K_TypeB;

  typedef GraphicsLibrary<LDS285<PORTRAIT,COLOURS_24BIT,XmemAccessMode,NokiaN95_8Gb_TypeB>,XmemAccessMode> NokiaN95_8Gb_Portrait_16M_TypeB;
  typedef GraphicsLibrary<LDS285<LANDSCAPE,COLOURS_24BIT,XmemAccessMode,NokiaN95_8Gb_TypeB>,XmemAccessMode> NokiaN95_8Gb_Landscape_16M_TypeB;

  typedef TerminalPortraitImpl<NokiaN95_8Gb_Portrait_64K_TypeB> NokiaN95_8Gb_Terminal_Portrait_64K_TypeB;
  typedef TerminalLandscapeImpl<NokiaN95_8Gb_Landscape_64K_TypeB> NokiaN95_8Gb_Terminal_Landscape_64K_TypeB;

  typedef TerminalPortraitImpl<NokiaN95_8Gb_Portrait_262K_TypeB> NokiaN95_8Gb_Terminal_Portrait_262K_TypeB;
  typedef TerminalLandscapeImpl<NokiaN95_8Gb_Landscape_262K_TypeB> NokiaN95_8Gb_Terminal_Landscape_262K_TypeB;

  typedef TerminalPortraitImpl<NokiaN95_8Gb_Portrait_16M_TypeB> NokiaN95_8Gb_Terminal_Portrait_16M_TypeB;
  typedef TerminalLandscapeImpl<NokiaN95_8Gb_Landscape_16M_TypeB> NokiaN95_8Gb_Terminal_Landscape_16M_TypeB;

  /*
   * The default backlight control when XMEM is available. If you're using GPIO on a Mega1280 or Mega2560
   * Then declare your backlight as "LDS285Backlight<GpioAccessMode> myBacklight;"
   */

  typedef LDS285Backlight<XmemAccessMode> DefaultBacklight;

  #else     // !mega1280 && !mega2560

  /*
   * The default backlight when XMEM is not available is GPIO
   */

  typedef LDS285Backlight<GpioAccessMode> DefaultBacklight;

  #endif    // mega1280/mega2560

  /*
   * Nokia N95 8Gb GPIO type A interface: 64K, 262K, 16M colours, portrait and landscape
   */

  typedef GraphicsLibrary<LDS285<PORTRAIT,COLOURS_16BIT,GpioAccessMode,NokiaN95_8Gb_TypeA>,GpioAccessMode> NokiaN95_8Gb_Portrait_64K_Gpio;
  typedef GraphicsLibrary<LDS285<LANDSCAPE,COLOURS_16BIT,GpioAccessMode,NokiaN95_8Gb_TypeA>,GpioAccessMode> NokiaN95_8Gb_Landscape_64K_Gpio;

  typedef GraphicsLibrary<LDS285<PORTRAIT,COLOURS_18BIT,GpioAccessMode,NokiaN95_8Gb_TypeA>,GpioAccessMode> NokiaN95_8Gb_Portrait_262K_Gpio;
  typedef GraphicsLibrary<LDS285<LANDSCAPE,COLOURS_18BIT,GpioAccessMode,NokiaN95_8Gb_TypeA>,GpioAccessMode> NokiaN95_8Gb_Landscape_262K_Gpio;

  typedef GraphicsLibrary<LDS285<PORTRAIT,COLOURS_24BIT,GpioAccessMode,NokiaN95_8Gb_TypeA>,GpioAccessMode> NokiaN95_8Gb_Portrait_16M_Gpio;
  typedef GraphicsLibrary<LDS285<LANDSCAPE,COLOURS_24BIT,GpioAccessMode,NokiaN95_8Gb_TypeA>,GpioAccessMode> NokiaN95_8Gb_Landscape_16M_Gpio;

  typedef TerminalPortraitImpl<NokiaN95_8Gb_Portrait_64K_Gpio> NokiaN95_8Gb_Terminal_Portrait_64K_Gpio;
  typedef TerminalLandscapeImpl<NokiaN95_8Gb_Landscape_64K_Gpio> NokiaN95_8Gb_Terminal_Landscape_64K_Gpio;

  typedef TerminalPortraitImpl<NokiaN95_8Gb_Portrait_262K_Gpio> NokiaN95_8Gb_Terminal_Portrait_262K_Gpio;
  typedef TerminalLandscapeImpl<NokiaN95_8Gb_Landscape_262K_Gpio> NokiaN95_8Gb_Terminal_Landscape_262K_Gpio;

  typedef TerminalPortraitImpl<NokiaN95_8Gb_Portrait_16M_Gpio> NokiaN95_8Gb_Terminal_Portrait_16M_Gpio;
  typedef TerminalLandscapeImpl<NokiaN95_8Gb_Landscape_16M_Gpio> NokiaN95_8Gb_Terminal_Landscape_16M_Gpio;

  /*
   * Nokia N95 8Gb GPIO type B interface: 64K, 262K, 16M colours, portrait and landscape
   */

  typedef GraphicsLibrary<LDS285<PORTRAIT,COLOURS_16BIT,GpioAccessMode,NokiaN95_8Gb_TypeB>,GpioAccessMode> NokiaN95_8Gb_Portrait_64K_Gpio_TypeB;
  typedef GraphicsLibrary<LDS285<LANDSCAPE,COLOURS_16BIT,GpioAccessMode,NokiaN95_8Gb_TypeB>,GpioAccessMode> NokiaN95_8Gb_Landscape_64K_Gpio_TypeB;

  typedef GraphicsLibrary<LDS285<PORTRAIT,COLOURS_18BIT,GpioAccessMode,NokiaN95_8Gb_TypeB>,GpioAccessMode> NokiaN95_8Gb_Portrait_262K_Gpio_TypeB;
  typedef GraphicsLibrary<LDS285<LANDSCAPE,COLOURS_18BIT,GpioAccessMode,NokiaN95_8Gb_TypeB>,GpioAccessMode> NokiaN95_8Gb_Landscape_262K_Gpio_TypeB;

  typedef GraphicsLibrary<LDS285<PORTRAIT,COLOURS_24BIT,GpioAccessMode,NokiaN95_8Gb_TypeB>,GpioAccessMode> NokiaN95_8Gb_Portrait_16M_Gpio_TypeB;
  typedef GraphicsLibrary<LDS285<LANDSCAPE,COLOURS_24BIT,GpioAccessMode,NokiaN95_8Gb_TypeB>,GpioAccessMode> NokiaN95_8Gb_Landscape_16M_Gpio_TypeB;

  typedef TerminalPortraitImpl<NokiaN95_8Gb_Portrait_64K_Gpio_TypeB> NokiaN95_8Gb_Terminal_Portrait_64K_Gpio_TypeB;
  typedef TerminalLandscapeImpl<NokiaN95_8Gb_Landscape_64K_Gpio_TypeB> NokiaN95_8Gb_Terminal_Landscape_64K_Gpio_TypeB;

  typedef TerminalPortraitImpl<NokiaN95_8Gb_Portrait_262K_Gpio_TypeB> NokiaN95_8Gb_Terminal_Portrait_262K_Gpio_TypeB;
  typedef TerminalLandscapeImpl<NokiaN95_8Gb_Landscape_262K_Gpio_TypeB> NokiaN95_8Gb_Terminal_Landscape_262K_Gpio_TypeB;

  typedef TerminalPortraitImpl<NokiaN95_8Gb_Portrait_16M_Gpio_TypeB> NokiaN95_8Gb_Terminal_Portrait_16M_Gpio_TypeB;
  typedef TerminalLandscapeImpl<NokiaN95_8Gb_Landscape_16M_Gpio_TypeB> NokiaN95_8Gb_Terminal_Landscape_16M_Gpio_TypeB;
}
