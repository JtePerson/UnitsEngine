#include "UnitsEngine/gpu/gpu_device.h"

#include <SDL3/SDL.h>

#include "UnitsEngine/core/log.h"
#include "UnitsEngine/core/assert.h"
#include "UnitsEngine/window/window.h"

namespace units {
  GPUDevice::GPUDevice(Window& p_window) noexcept {
    UE_CORE_WARN("Creating GPUDevice");
    SDL_GPUShaderFormat shader_format= SDL_GPU_SHADERFORMAT_SPIRV |
                                       SDL_GPU_SHADERFORMAT_DXIL |
                                       SDL_GPU_SHADERFORMAT_DXBC |
                                       SDL_GPU_SHADERFORMAT_MSL |
                                       SDL_GPU_SHADERFORMAT_METALLIB;
    #if defined(UE_DEBUG)
      constexpr bool debug_mode= true;
    #else
      constexpr bool debug_mode= false;
    #endif
    m_gpu_device_ptr_= reinterpret_cast<void*>(SDL_CreateGPUDevice(shader_format, debug_mode, nullptr));
    if (m_gpu_device_ptr_ == nullptr) {
      UE_CORE_ERROR("SDL error: {0}", SDL_GetError());
      UE_CORE_ASSERT(false, "Could not initialize GPUDevice!");
    }
    UE_CORE_TRACE("GPUDevice backend: {0}", SDL_GetGPUDeviceDriver(reinterpret_cast<SDL_GPUDevice*>(m_gpu_device_ptr_)));
    claimWindow(p_window);
    UE_CORE_INFO("GPUDevice Created");
  }

  void GPUDevice::claimWindow(Window& p_window) noexcept {
    if (!expired()) {
      if (!SDL_ClaimWindowForGPUDevice(reinterpret_cast<SDL_GPUDevice*>(m_gpu_device_ptr_), reinterpret_cast<SDL_Window*>(p_window.getWindowPtr()))) {
        UE_CORE_ERROR("SDL error: {0}", SDL_GetError());
        UE_CORE_ASSERT(false && "Could not claim Window for GPUDevice");
      }
    }
  }

  void GPUDevice::destroy() noexcept {
    if (!expired()) {
      UE_CORE_WARN("Destroying GPUDevice");
      SDL_DestroyGPUDevice(reinterpret_cast<SDL_GPUDevice*>(m_gpu_device_ptr_));
      m_gpu_device_ptr_= nullptr;
      UE_CORE_INFO("GPUDevice Destroyed");
    }
  }
} // namespace units