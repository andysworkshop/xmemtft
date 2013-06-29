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
#include "drv/accessModes/Xmem16AccessMode.h"
#include "drv/accessModes/Gpio16LatchAccessMode.h"
#include "drv/ili9327/ILI9327.h"
#include "drv/ili9327/panelTraits/ILI9327400x240PanelTraits.h"
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
	 * Generic ILI9327 XMEM16 interface: 64K colours, portrait and landscape
	 */

	typedef GraphicsLibrary<ILI9327<PORTRAIT,COLOURS_16BIT,Xmem16AccessMode,ILI9327400x240PanelTraits>,Xmem16AccessMode> ILI9327_400x240_Portrait_64K_Xmem16;
	typedef GraphicsLibrary<ILI9327<LANDSCAPE,COLOURS_16BIT,Xmem16AccessMode,ILI9327400x240PanelTraits>,Xmem16AccessMode> ILI9327_400x240_Landscape_64K_Xmem16;

	typedef TerminalPortraitImpl<ILI9327_400x240_Portrait_64K_Xmem16> ILI9327_400x240_Terminal_Portrait_64K_Xmem16;
	typedef TerminalLandscapeImpl<ILI9327_400x240_Landscape_64K_Xmem16> ILI9327_400x240_Terminal_Landscape_64K_Xmem16;

	/*
	 * Generic ILI9327 GPIO16 latched interface: 64K colours, portrait and landscape
	 */

	typedef GraphicsLibrary<ILI9327<PORTRAIT,COLOURS_16BIT,DefaultMegaGpio16LatchAccessMode,ILI9327400x240PanelTraits>,DefaultMegaGpio16LatchAccessMode> ILI9327_400x240_Portrait_64K_Gpio16Latch;
	typedef GraphicsLibrary<ILI9327<LANDSCAPE,COLOURS_16BIT,DefaultMegaGpio16LatchAccessMode,ILI9327400x240PanelTraits>,DefaultMegaGpio16LatchAccessMode> ILI9327_400x240_Landscape_64K_Gpio16Latch;

	typedef TerminalPortraitImpl<ILI9327_400x240_Portrait_64K_Gpio16Latch> ILI9327_400x240_Terminal_Portrait_64K_Gpio16Latch;
	typedef TerminalLandscapeImpl<ILI9327_400x240_Landscape_64K_Gpio16Latch> ILI9327_400x240_Terminal_Landscape_64K_Gpio16Latch;

	/*
	 * The default for most people is a PWM output on pin #2
	 */

	typedef Backlight<2> DefaultBacklight;

#endif
}
