#include "UnitsEngine/gpu/gpu_render_pass.h"

#include <SDL3/SDL.h>

#include "UnitsEngine/window/window.h"
#include "window/window.h"
#include "UnitsEngine/gpu/gpu_command_buffer.h"

namespace Units {
  GPURenderPass::GPURenderPass(Window& p_window, GPUCommandBuffer& p_pipeline) noexcept {
    auto* command_buffer_ptr= reinterpret_cast<SDL_GPUCommandBuffer*>(p_pipeline.getGPUCommandBufferPtr());
    auto* window_ptr= core::Window::getFromId(p_window.getId()).getSDLWindowPtr();
    SDL_GPUDepthStencilTargetInfo depth_stencil_target_info= {};
    SDL_GPUTexture* swapchain_texture;
    SDL_WaitAndAcquireGPUSwapchainTexture(command_buffer_ptr, window_ptr, &swapchain_texture, nullptr, nullptr);
    if (swapchain_texture != nullptr) {
      m_gpu_render_pass_ptr_= reinterpret_cast<void*>(SDL_BeginGPURenderPass(
        command_buffer_ptr,
        (SDL_GPUColorTargetInfo[]){{
          .texture= swapchain_texture,
          .clear_color= SDL_FColor{0.117f, 0.117f, 0.176f, 1.0f},
          .load_op= SDL_GPU_LOADOP_CLEAR,
          .store_op= SDL_GPU_STOREOP_STORE
        }},
        1,
        nullptr
      ));
    }
  }
  GPURenderPass::~GPURenderPass() noexcept {
    if (m_gpu_render_pass_ptr_ != nullptr) {
      SDL_EndGPURenderPass(reinterpret_cast<SDL_GPURenderPass*>(m_gpu_render_pass_ptr_));
      m_gpu_render_pass_ptr_= nullptr;
    }
  }
} // namespace Units