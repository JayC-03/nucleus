/**
 * (c) 2014-2016 Alexandro Sanchez Bach. All rights reserved.
 * Released under GPL v2 license. Read LICENSE for more details.
 */

#pragma once

#include "nucleus/graphics/graphics.h"
#include "nucleus/graphics/backend/direct3d12/direct3d12.h"

namespace gfx {
namespace direct3d12 {

class Direct3D12CommandQueue : public CommandQueue {
private:
    ID3D12CommandQueue* queue;

public:
    Direct3D12CommandQueue();
    ~Direct3D12CommandQueue();

    bool initialize(ID3D12Device* device);
    bool initialize(ID3D12CommandQueue* newQueue);

    void submit(CommandBuffer* cmdBuffer, Fence* fence) override;
    void waitIdle() override;
};

}  // namespace direct3d12
}  // namespace gfx
