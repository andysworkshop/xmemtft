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
 * @file GetFarAddress.h
 * @brief Provide access to large binaries compiled into flash.
 */

#pragma once


#ifndef GET_FAR_ADDRESS

/**
 * All credit to Carlos Lamas for this patch:
 * https://savannah.nongnu.org/patch/?6352
 *
 * GET_FAR_ADDRESS allows us to export a 24-bit flash address into our
 * code (as a 32-bit variable) which means we can seamlessly address
 * large binaries stored in flash without having to fix their address.
 */

#define GET_FAR_ADDRESS(var)                  \
({                                            \
  uint32_t tmp;                               \
                                              \
  __asm__ __volatile__(                       \
                                              \
      "ldi  %A0, lo8(%1)"           "\n\t"    \
      "ldi  %B0, hi8(%1)"           "\n\t"    \
      "ldi  %C0, hh8(%1)"           "\n\t"    \
      "clr  %D0"                    "\n\t"    \
    :                                         \
      "=d" (tmp)                              \
    :                                         \
      "p"  (&(var))                           \
  );                                          \
  tmp;                                        \
})


#endif
