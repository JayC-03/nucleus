/**
 * (c) 2014-2016 Alexandro Sanchez Bach. All rights reserved.
 * Released under GPL v2 license. Read LICENSE for more details.
 */

#pragma once

#include "nucleus/graphics/graphics.h"
#include "nucleus/graphics/backend/direct3d12/direct3d12.h"


namespace gfx {
namespace direct3d12 {

class Direct3D12CommandBuffer : public CommandBuffer {
private:
    ID3D12CommandAllocator* allocator;

public:
    ID3D12GraphicsCommandList* list;

    Direct3D12CommandBuffer();
    ~Direct3D12CommandBuffer();

    bool initialize(ID3D12Device* device);

    virtual bool reset() override;
    virtual bool finalize() override;

    // Commands
    virtual void cmdBindPipeline(Pipeline* pipeline) override;
    virtual void cmdClearColor(ColorTarget* target, const F32* colorValue) override;
    virtual void cmdClearDepthStencil(DepthStencilTarget* target, F32 depthValue, U08 stencilValue) override;
    virtual void cmdDraw(U32 firstVertex, U32 vertexCount, U32 firstInstance, U32 instanceCount) override;
    virtual void cmdDrawIndexed(U32 firstIndex, U32 indexCount, U32 vertexOffset, U32 firstInstance, U32 instanceCount) override;
    virtual void cmdSetHeaps(const std::vector<Heap*>& heaps) override;
    virtual void cmdSetDescriptor(Size index, Heap* heap, Size offset) override;
    virtual void cmdSetVertexBuffers(U32 index, U32 vtxBufferCount, VertexBuffer** vtxBuffer, U32* offsets, U32* strides) override;
    virtual void cmdSetPrimitiveTopology(PrimitiveTopology topology) override;
    virtual void cmdSetTargets(U32 colorCount, ColorTarget** colorTargets, DepthStencilTarget* depthStencilTarget) override;
    virtual void cmdSetViewports(U32 viewportsCount, const Viewport* viewports) override;
    virtual void cmdSetScissors(U32 scissorsCount, const Rectangle* scissors) override;
    virtual void cmdResourceBarrier(U32 barrierCount, const ResourceBarrier* barriers) override;
};

}  // namespace direct3d12
}  // namespace gfx
