/**
 * (c) 2015 Alexandro Sanchez Bach. All rights reserved.
 * Released under GPL v2 license. Read LICENSE for more details.
 */

#include "compiler.h"

namespace cpu {
namespace backend {

using namespace cpu::hir;

void Compiler::addPass(std::unique_ptr<Pass> pass) {
    passes.push_back(std::move(pass));
}

bool Compiler::optimize(Function* function) {
    for (auto& pass : passes) {
        pass->run(function);
    }
}

}  // namespace backend
}  // namespace cpu