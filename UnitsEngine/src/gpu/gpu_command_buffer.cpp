#include "UnitsEngine/gpu/gpu_command_buffer.h"

#include <SDL3/SDL.h>

#include "UnitsEngine/gpu/gpu_device.h"

namespace Units {
  GPUCommandBuffer::GPUCommandBuffer(GPUDevice& p_gpu_device) noexcept {
    auto* gpu_device_ptr= reinterpret_cast<SDL_GPUDevice*>(p_gpu_device.getDevicePtr());
    m_gpu_command_buffer_ptr_= reinterpret_cast<void*>(SDL_AcquireGPUCommandBuffer(gpu_device_ptr));
  }
  GPUCommandBuffer::~GPUCommandBuffer() noexcept {
    if (m_gpu_command_buffer_ptr_ != nullptr) {
      SDL_CancelGPUCommandBuffer(reinterpret_cast<SDL_GPUCommandBuffer*>(m_gpu_command_buffer_ptr_));
    }
  }
  
  void GPUCommandBuffer::submit() noexcept {
    SDL_SubmitGPUCommandBuffer(reinterpret_cast<SDL_GPUCommandBuffer*>(m_gpu_command_buffer_ptr_));
    m_gpu_command_buffer_ptr_= nullptr;
  }
} // namespace Units