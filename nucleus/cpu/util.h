/**
 * (c) 2015 Alexandro Sanchez Bach. All rights reserved.
 * Released under GPL v2 license. Read LICENSE for more details.
 */

#pragma once

#include "nucleus/common.h"

namespace cpu {

/**
 * Function placeholders in JIT-translated modules call this function to initialize
 * the translation and compilation process. This function will never return.
 * Instead, it will directly jump to the recompiled function's entry point.
 * @param[in]  guestFunc  Host address to the guest function object
 * @param[in]  guestAddr  Guest address where the function to be translated begins
 */
void nucleusTranslate(void* guestFunc, U64 guestAddr);

}  // namespace cpu