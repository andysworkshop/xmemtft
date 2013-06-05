/*
 * XMEM LCD Library for the Arduino
 * Copyright (c) 2012,2013 Andy Brown. All rights reserved.
 * This is open source software. Please see website for terms and conditions:
 *
 * http://andybrown.me.uk
 *
 * This notice may not be removed or altered from any source distribution.
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
