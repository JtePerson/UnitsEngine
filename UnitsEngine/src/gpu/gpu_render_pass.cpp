#include "UnitsEngine/gpu/gpu_render_pass.h"

#include <SDL3/SDL.h>

#include "UnitsEngine/window/window.h"
#include "UnitsEngine/gpu/gpu_command_buffer.h"
#include "UnitsEngine/gpu/gpu_render_pass_specs.h"
#include "UnitsEngine/core/log.h"
#include "UnitsEngine/core/assert.h"

namespace units {
  GPURenderPass::GPURenderPass(GPUCommandBuffer& p_pipeline, GPURenderPassSpecs& p_specs) noexcept {
    if (p_pipeline.expired() || p_specs.texture_ptr->expired()) { return; }
    auto* command_buffer_ptr= reinterpret_cast<SDL_GPUCommandBuffer*>(p_pipeline.getGPUCommandBufferPtr());
    SDL_GPUDepthStencilTargetInfo depth_stencil_target_info= {};
    m_gpu_render_pass_ptr_= reinterpret_cast<void*>(SDL_BeginGPURenderPass(
      command_buffer_ptr,
      (SDL_GPUColorTargetInfo[]){{
        .texture= reinterpret_cast<SDL_GPUTexture*>(p_specs.texture_ptr->getGPUTexturePtr()),
        .clear_color= SDL_FColor{p_specs.clear_color.r, p_specs.clear_color.g, p_specs.clear_color.b, p_specs.clear_color.a},
        .load_op= SDL_GPU_LOADOP_CLEAR,
        .store_op= SDL_GPU_STOREOP_STORE
      }},
      1,
      nullptr
    ));
    if (m_gpu_render_pass_ptr_ == nullptr) {
      UE_CORE_ERROR("SDL error: {0}", SDL_GetError());
      UE_CORE_ASSERT(false, "Could not begin GPURenderPass!");
    }
  }
  void GPURenderPass::destroy() noexcept {
    if (!expired()) {
      SDL_EndGPURenderPass(reinterpret_cast<SDL_GPURenderPass*>(m_gpu_render_pass_ptr_));
      m_gpu_render_pass_ptr_= nullptr;
    }
  }
} // namespace units