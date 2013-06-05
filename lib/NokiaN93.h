/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012,2013 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
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
#include "drv/mc2pa8201/panelTraits/NokiaN93_TypeA.h"
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
	 * Nokia N93 XMEM type A interface: 64K, 262K, 16M colours, portrait and landscape
	 */

	typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_16BIT,XmemAccessMode,NokiaN93_TypeA>,XmemAccessMode> NokiaN93_Portrait_64K;
	typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_16BIT,XmemAccessMode,NokiaN93_TypeA>,XmemAccessMode> NokiaN93_Landscape_64K;

	typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_18BIT,XmemAccessMode,NokiaN93_TypeA>,XmemAccessMode> NokiaN93_Portrait_262K;
	typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_18BIT,XmemAccessMode,NokiaN93_TypeA>,XmemAccessMode> NokiaN93_Landscape_262K;

	typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_24BIT,XmemAccessMode,NokiaN93_TypeA>,XmemAccessMode> NokiaN93_Portrait_16M;
	typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_24BIT,XmemAccessMode,NokiaN93_TypeA>,XmemAccessMode> NokiaN93_Landscape_16M;

	typedef TerminalPortraitImpl<NokiaN93_Portrait_64K> NokiaN93_Terminal_Portrait_64K;
	typedef TerminalLandscapeImpl<NokiaN93_Landscape_64K> NokiaN93_Terminal_Landscape_64K;

	typedef TerminalPortraitImpl<NokiaN93_Portrait_262K> NokiaN93_Terminal_Portrait_262K;
	typedef TerminalLandscapeImpl<NokiaN93_Landscape_262K> NokiaN93_Terminal_Landscape_262K;

	typedef TerminalPortraitImpl<NokiaN93_Portrait_16M> NokiaN93_Terminal_Portrait_16M;
	typedef TerminalLandscapeImpl<NokiaN93_Landscape_16M> NokiaN93_Terminal_Landscape_16M;

	/*
	 * The default for most people is a PWM output on pin #2
	 */

	typedef Backlight<2> DefaultBacklight;

	#else			// !mega1280 && !mega2560

	/*
	 * Pins 0..9 are used on the 328P for IO so we'll default the backlight to PWM pin #10
	 */

	typedef Backlight<10> DefaultBacklight;

	#endif		// mega1280/mega2560

	/*
	 * Nokia N93 GPIO type A interface: 64K, 262K, 16M colours, portrait and landscape
	 */

	typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_16BIT,GpioAccessMode,NokiaN93_TypeA>,GpioAccessMode> NokiaN93_Portrait_64K_Gpio;
	typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_16BIT,GpioAccessMode,NokiaN93_TypeA>,GpioAccessMode> NokiaN93_Landscape_64K_Gpio;

	typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_18BIT,GpioAccessMode,NokiaN93_TypeA>,GpioAccessMode> NokiaN93_Portrait_262K_Gpio;
	typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_18BIT,GpioAccessMode,NokiaN93_TypeA>,GpioAccessMode> NokiaN93_Landscape_262K_Gpio;

	typedef GraphicsLibrary<MC2PA8201<PORTRAIT,COLOURS_24BIT,GpioAccessMode,NokiaN93_TypeA>,GpioAccessMode> NokiaN93_Portrait_16M_Gpio;
	typedef GraphicsLibrary<MC2PA8201<LANDSCAPE,COLOURS_24BIT,GpioAccessMode,NokiaN93_TypeA>,GpioAccessMode> NokiaN93_Landscape_16M_Gpio;

	typedef TerminalPortraitImpl<NokiaN93_Portrait_64K_Gpio> NokiaN93_Terminal_Portrait_64K_Gpio;
	typedef TerminalLandscapeImpl<NokiaN93_Landscape_64K_Gpio> NokiaN93_Terminal_Landscape_64K_Gpio;

	typedef TerminalPortraitImpl<NokiaN93_Portrait_262K_Gpio> NokiaN93_Terminal_Portrait_262K_Gpio;
	typedef TerminalLandscapeImpl<NokiaN93_Landscape_262K_Gpio> NokiaN93_Terminal_Landscape_262K_Gpio;

	typedef TerminalPortraitImpl<NokiaN93_Portrait_16M_Gpio> NokiaN93_Terminal_Portrait_16M_Gpio;
	typedef TerminalLandscapeImpl<NokiaN93_Landscape_16M_Gpio> NokiaN93_Terminal_Landscape_16M_Gpio;
}


