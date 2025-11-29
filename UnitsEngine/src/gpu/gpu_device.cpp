#include "UnitsEngine/gpu/gpu_device.h"

#include <SDL3/SDL.h>

#include "UnitsEngine/core/log.h"
#include "UnitsEngine/core/assert.h"
#include "window/window.h"

namespace Units {
  GPUDevice::GPUDevice() noexcept {
    UE_CORE_WARN("Initializing Renderer");
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
    UE_CORE_ASSERT((m_gpu_device_ptr_ != nullptr && "GPUDevice could not initialize GPU Device!"));
    UE_CORE_TRACE("GPUDevice backend: {0}", SDL_GetGPUDeviceDriver(reinterpret_cast<SDL_GPUDevice*>(m_gpu_device_ptr_)));
    UE_CORE_INFO("GPUDevice Initialized");
  }
  GPUDevice::~GPUDevice() noexcept {
    UE_CORE_WARN("Quitting GPUDevice");
    SDL_DestroyGPUDevice(reinterpret_cast<SDL_GPUDevice*>(m_gpu_device_ptr_));
    UE_CORE_INFO("GPUDevice Quit");
  }

  void GPUDevice::claimWindow(Window& p_window) noexcept {
    if (!SDL_ClaimWindowForGPUDevice(reinterpret_cast<SDL_GPUDevice*>(m_gpu_device_ptr_), core::Window::getFromId(p_window.getId()).getSDLWindowPtr())) {
      UE_CORE_ERROR("SDL error: {0}", SDL_GetError());
      UE_CORE_ASSERT(false && "Could not claim Window for GPUDevice");
    }
  }
} // namespace Units