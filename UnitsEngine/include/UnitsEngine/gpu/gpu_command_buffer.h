#pragma once
#include "UnitsEngine/core/engine_api.h"
#include "UnitsEngine/gpu/gpu_device.h"

namespace units {
  class UE_API GPUCommandBuffer final {
  public:
    inline GPUCommandBuffer() noexcept= default;
    GPUCommandBuffer(GPUDevice& p_gpu_device) noexcept;
    inline GPUCommandBuffer(GPUCommandBuffer&& p_gpu_command_buffer) noexcept {
      *this= p_gpu_command_buffer;
      p_gpu_command_buffer.m_gpu_command_buffer_ptr_= nullptr;
    }
    inline GPUCommandBuffer& operator=(GPUCommandBuffer&& p_gpu_command_buffer) noexcept {
      *this= p_gpu_command_buffer;
      p_gpu_command_buffer.m_gpu_command_buffer_ptr_= nullptr;
      return *this;
    }
    inline ~GPUCommandBuffer() noexcept { destroy(); }

    inline bool expired() noexcept { return m_gpu_command_buffer_ptr_ == nullptr; }
    
    void submit() noexcept;

    void destroy() noexcept;
    
    inline void* getGPUCommandBufferPtr() noexcept { return m_gpu_command_buffer_ptr_; }
  private:
    inline GPUCommandBuffer(const GPUCommandBuffer&) noexcept= default;
    inline GPUCommandBuffer& operator=(const GPUCommandBuffer&) noexcept= default;

    void* m_gpu_command_buffer_ptr_= nullptr;
  };
} // namespace units