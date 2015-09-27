/**
 * (c) 2015 Alexandro Sanchez Bach. All rights reserved.
 * Released under GPL v2 license. Read LICENSE for more details.
 */

#include "util.h"
#include "nucleus/emulator.h"
#include "nucleus/cpu/frontend/ppu/ppu_decoder.h"

namespace cpu {

void nucleusTranslate(void* guestFunc, U64 guestAddr) {
    auto* function = static_cast<frontend::ppu::Function*>(guestFunc);

    // Frontend tasks
    function->analyze_cfg();
    function->recompile();

    // Backend tasks
    nucleus.cell.compiler->compile(function->hirFunction);
}

}  // namespace cpu