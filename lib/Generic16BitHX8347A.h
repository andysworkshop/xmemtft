/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012,2013 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
 */

/**
 * @file Generic16BitHX8347A.h
 * @brief Typedefs for using an HX8347A in 16-bit mode
 * @ingroup HX8347A
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
#include "drv/hx8347a/HX8347A.h"
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
	 * Generic HX8347A XMEM16 interface: 64K colours, portrait and landscape
	 */

	typedef GraphicsLibrary<HX8347A<PORTRAIT,COLOURS_16BIT,Xmem16AccessMode>,Xmem16AccessMode> HX8347A_Portrait_64K_Xmem16;
	typedef GraphicsLibrary<HX8347A<LANDSCAPE,COLOURS_16BIT,Xmem16AccessMode>,Xmem16AccessMode> HX8347A_Landscape_64K_Xmem16;

	typedef TerminalPortraitImpl<HX8347A_Portrait_64K_Xmem16> HX8347A_Terminal_Portrait_64K_Xmem16;
	typedef TerminalLandscapeImpl<HX8347A_Landscape_64K_Xmem16> HX8347A_Terminal_Landscape_64K_Xmem16;

	/*
	 * Generic HX8347A GPIO16 latched interface: 64K colours, portrait and landscape
	 */

	typedef GraphicsLibrary<HX8347A<PORTRAIT,COLOURS_16BIT,DefaultMegaGpio16LatchAccessMode>,DefaultMegaGpio16LatchAccessMode> HX8347A_Portrait_64K_Gpio16Latch;
	typedef GraphicsLibrary<HX8347A<LANDSCAPE,COLOURS_16BIT,DefaultMegaGpio16LatchAccessMode>,DefaultMegaGpio16LatchAccessMode> HX8347A_Landscape_64K_Gpio16Latch;

	typedef TerminalPortraitImpl<HX8347A_Portrait_64K_Gpio16Latch> HX8347A_Terminal_Portrait_64K_Gpio16Latch;
	typedef TerminalLandscapeImpl<HX8347A_Landscape_64K_Gpio16Latch> HX8347A_Terminal_Landscape_64K_Gpio16Latch;

	/*
	 * The default for most people is a PWM output on pin #2
	 */

	typedef Backlight<2> DefaultBacklight;

#endif
}
