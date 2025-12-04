#include "UnitsEngine/gpu/gpu_texture.h"

#include <SDL3/SDL.h>

#include "UnitsEngine/core/log.h"
#include "UnitsEngine/core/assert.h"

namespace units {
  GPUTexture::GPUTexture(GPUDevice& p_gpu_device, GPUTextureSpecs& p_specs) noexcept {
    if (p_gpu_device.expired()) { return; }
    auto* sdl_gpu_device_ptr= reinterpret_cast<SDL_GPUDevice*>(p_gpu_device.getGPUDevicePtr());
    SDL_GPUTextureCreateInfo sdl_texture_create_info= {
      .type= static_cast<SDL_GPUTextureType>(p_specs.type),
      .format= static_cast<SDL_GPUTextureFormat>(p_specs.format),
      .usage= static_cast<SDL_GPUTextureUsageFlags>(p_specs.usage),
      .width= p_specs.width,
      .height= p_specs.height,
      .layer_count_or_depth= p_specs.layer_count_or_depth,
      .num_levels= 1,
      .sample_count= SDL_GPU_SAMPLECOUNT_1
    };
    m_gpu_texture_ptr_= reinterpret_cast<void*>(SDL_CreateGPUTexture(sdl_gpu_device_ptr, &sdl_texture_create_info));
    if (m_gpu_texture_ptr_ == nullptr) {
      UE_CORE_ERROR("SDL error: {0}", SDL_GetError());
      UE_CORE_ASSERT(false, "Could not create GPUTexture!");
    }
  }
  GPUTexture::GPUTexture(GPUCommandBuffer& p_gpu_command_buffer, Window& p_window, const bool& p_wait) noexcept {
    auto* sdl_gpu_command_buffer_ptr= reinterpret_cast<SDL_GPUCommandBuffer*>(p_gpu_command_buffer.getGPUCommandBufferPtr());
    auto* sdl_window_ptr= reinterpret_cast<SDL_Window*>(p_window.getWindowPtr());
    SDL_GPUTexture* tmp_sdl_gpu_texture_ptr= nullptr;
    if (p_wait) {
      SDL_WaitAndAcquireGPUSwapchainTexture(sdl_gpu_command_buffer_ptr, sdl_window_ptr, &tmp_sdl_gpu_texture_ptr, nullptr, nullptr);
    } else {
      SDL_AcquireGPUSwapchainTexture(sdl_gpu_command_buffer_ptr, sdl_window_ptr, &tmp_sdl_gpu_texture_ptr, nullptr, nullptr);
    }
    m_gpu_texture_ptr_= reinterpret_cast<void*>(tmp_sdl_gpu_texture_ptr);
    m_from_window_= true;
  }

  void GPUTexture::destroy() noexcept {
    if (!expired() && !m_from_window_) {
      SDL_ReleaseGPUTexture(reinterpret_cast<SDL_GPUDevice*>(m_gpu_device_ptr_), reinterpret_cast<SDL_GPUTexture*>(m_gpu_texture_ptr_));
      m_gpu_texture_ptr_= nullptr;
    }
  }
} // namespace units