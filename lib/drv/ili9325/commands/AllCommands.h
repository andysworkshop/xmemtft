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
 * @file AllCommands.h
 * @brief Commands for the ILI9325 that we use
 * @ingroup ILI9325
 */

#pragma once

namespace lcd {
  namespace ili9325 {

    enum {
      ILI932X_START_OSC          =0x00,
      ILI932X_DRIV_OUT_CTRL      =0x01,
      ILI932X_DRIV_WAV_CTRL      =0x02,
      ILI932X_ENTRY_MOD          =0x03,
      ILI932X_RESIZE_CTRL        =0x04,
      ILI932X_DISP_CTRL1         =0x07,
      ILI932X_DISP_CTRL2         =0x08,
      ILI932X_DISP_CTRL3         =0x09,
      ILI932X_DISP_CTRL4         =0x0A,
      ILI932X_RGB_DISP_IF_CTRL1  =0x0C,
      ILI932X_FRM_MARKER_POS     =0x0D,
      ILI932X_RGB_DISP_IF_CTRL2  =0x0F,
      ILI932X_POW_CTRL1          =0x10,
      ILI932X_POW_CTRL2          =0x11,
      ILI932X_POW_CTRL3          =0x12,
      ILI932X_POW_CTRL4          =0x13,
      ILI932X_GRAM_HOR_AD        =0x20,
      ILI932X_GRAM_VER_AD        =0x21,
      ILI932X_RW_GRAM            =0x22,
      ILI932X_POW_CTRL7          =0x29,
      ILI932X_FRM_RATE_COL_CTRL  =0x2B,
      ILI932X_GAMMA_CTRL1        =0x30,
      ILI932X_GAMMA_CTRL2        =0x31,
      ILI932X_GAMMA_CTRL3        =0x32,
      ILI932X_GAMMA_CTRL4        =0x35,
      ILI932X_GAMMA_CTRL5        =0x36,
      ILI932X_GAMMA_CTRL6        =0x37,
      ILI932X_GAMMA_CTRL7        =0x38,
      ILI932X_GAMMA_CTRL8        =0x39,
      ILI932X_GAMMA_CTRL9        =0x3C,
      ILI932X_GAMMA_CTRL10       =0x3D,
      ILI932X_HOR_START_AD       =0x50,
      ILI932X_HOR_END_AD         =0x51,
      ILI932X_VER_START_AD       =0x52,
      ILI932X_VER_END_AD         =0x53,
      ILI932X_GATE_SCAN_CTRL1    =0x60,
      ILI932X_GATE_SCAN_CTRL2    =0x61,
      ILI932X_GATE_SCAN_CTRL3    =0x6A,
      ILI932X_PART_IMG1_DISP_POS =0x80,
      ILI932X_PART_IMG1_START_AD =0x81,
      ILI932X_PART_IMG1_END_AD   =0x82,
      ILI932X_PART_IMG2_DISP_POS =0x83,
      ILI932X_PART_IMG2_START_AD =0x84,
      ILI932X_PART_IMG2_END_AD   =0x85,
      ILI932X_PANEL_IF_CTRL1     =0x90,
      ILI932X_PANEL_IF_CTRL2     =0x92,
      ILI932X_PANEL_IF_CTRL3     =0x93,
      ILI932X_PANEL_IF_CTRL4     =0x95,
      ILI932X_PANEL_IF_CTRL5     =0x97,
      ILI932X_PANEL_IF_CTRL6     =0x98
    };
  }
}

