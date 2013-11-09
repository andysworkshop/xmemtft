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
 * @file Generic16BitHX8352A.h
 * @brief Typedefs for using an HX8352A in 16-bit mode
 * @ingroup HX8352A
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
#include "Font.h"
#include "drv/accessModes/Xmem16AccessMode.h"
#include "drv/accessModes/Gpio16LatchAccessMode.h"
#include "drv/accessModes/Gpio16AccessMode.h"
#include "drv/hx8352a/HX8352A.h"
#include "drv/hx8352a/panelTraits/LG_KF700PanelTraits.h"
#include "GetFarAddress.h"
#include "decoders/PicoJpeg.h"
#include "decoders/LzgFlashDecoder.h"
#include "gl/GraphicsLibrary.h"
#include "Backlight.h"
#include "terminal/TerminalPortraitImpl.h"
#include "terminal/TerminalLandscapeImpl.h"


namespace lcd {

#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)

	/*
	 * LG KF700 HX8352A XMEM16 interface: 64K colours, portrait and landscape
	 */

	typedef GraphicsLibrary<HX8352A<PORTRAIT,COLOURS_16BIT,Xmem16AccessMode,LG_KF700PanelTraits>,Xmem16AccessMode> LG_KF700_Portrait_64K_Xmem16;
	typedef GraphicsLibrary<HX8352A<LANDSCAPE,COLOURS_16BIT,Xmem16AccessMode,LG_KF700PanelTraits>,Xmem16AccessMode> LG_KF700_Landscape_64K_Xmem16;

	typedef TerminalPortraitImpl<LG_KF700_Portrait_64K_Xmem16> LG_KF700_Terminal_Portrait_64K_Xmem16;
	typedef TerminalLandscapeImpl<LG_KF700_Landscape_64K_Xmem16> LG_KF700_Terminal_Landscape_64K_Xmem16;

	/*
	 * Generic HX8352A GPIO16 latched interface: 64K colours, portrait and landscape
	 */

	typedef GraphicsLibrary<HX8352A<PORTRAIT,COLOURS_16BIT,DefaultMegaGpio16LatchAccessMode,LG_KF700PanelTraits>,DefaultMegaGpio16LatchAccessMode> LG_KF700_Portrait_64K_Gpio16Latch;
	typedef GraphicsLibrary<HX8352A<LANDSCAPE,COLOURS_16BIT,DefaultMegaGpio16LatchAccessMode,LG_KF700PanelTraits>,DefaultMegaGpio16LatchAccessMode> LG_KF700_Landscape_64K_Gpio16Latch;

	typedef TerminalPortraitImpl<LG_KF700_Portrait_64K_Gpio16Latch> LG_KF700_Terminal_Portrait_64K_Gpio16Latch;
	typedef TerminalLandscapeImpl<LG_KF700_Landscape_64K_Gpio16Latch> LG_KF700_Terminal_Landscape_64K_Gpio16Latch;

  /*
   * Generic HX8352A GPIO16 interface: 64K colours, portrait and landscape
   */

  typedef GraphicsLibrary<HX8352A<PORTRAIT,COLOURS_16BIT,DefaultMegaGpio16AccessMode,LG_KF700PanelTraits>,DefaultMegaGpio16AccessMode> LG_KF700_Portrait_64K_Gpio16;
  typedef GraphicsLibrary<HX8352A<LANDSCAPE,COLOURS_16BIT,DefaultMegaGpio16AccessMode,LG_KF700PanelTraits>,DefaultMegaGpio16AccessMode> LG_KF700_Landscape_64K_Gpio16;

  typedef TerminalPortraitImpl<LG_KF700_Portrait_64K_Gpio16> LG_KF700_Terminal_Portrait_64K_Gpio16;
  typedef TerminalLandscapeImpl<LG_KF700_Landscape_64K_Gpio16> LG_KF700_Terminal_Landscape_64K_Gpio16;

	/*
	 * The default for most people is a PWM output on pin #2
	 */

	typedef Backlight<2> DefaultBacklight;

#endif
}
