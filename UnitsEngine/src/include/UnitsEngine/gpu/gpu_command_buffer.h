#pragma once
#include "UnitsEngine/core/engine_api.h"
#include "UnitsEngine/gpu/gpu_device.h"

namespace Units {
  class UE_API GPUCommandBuffer final {
  public:
    GPUCommandBuffer(GPUDevice& p_gpu_device) noexcept;
    inline GPUCommandBuffer(GPUCommandBuffer&&) noexcept= delete;
    inline GPUCommandBuffer(const GPUCommandBuffer&) noexcept= delete;
    inline GPUCommandBuffer& operator=(GPUCommandBuffer&&) noexcept= delete;
    inline GPUCommandBuffer& operator=(const GPUCommandBuffer&) noexcept= delete;
    ~GPUCommandBuffer() noexcept;
    
    void submit() noexcept;
    
    inline void* getGPUCommandBufferPtr() noexcept {
      return m_gpu_command_buffer_ptr_;
    }
  private:
    void* m_gpu_command_buffer_ptr_= nullptr;
  };
} // namespace Units