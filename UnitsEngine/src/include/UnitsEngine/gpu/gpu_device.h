#pragma once
#include "UnitsEngine/core/engine_api.h"
#include "UnitsEngine/window/window.h"

namespace Units {
  class UE_API GPUDevice final {
  public:
    GPUDevice() noexcept;
    inline GPUDevice(GPUDevice&&) noexcept= delete;
    inline GPUDevice(const GPUDevice&) noexcept= delete;
    inline GPUDevice& operator=(GPUDevice&&) noexcept= delete;
    inline GPUDevice& operator=(const GPUDevice&) noexcept= delete;
    ~GPUDevice() noexcept;
    
    void claimWindow(Window& p_window) noexcept;
    inline void* getDevicePtr() noexcept {
      return m_gpu_device_ptr_;
    }
  private:
    void* m_gpu_device_ptr_= nullptr;
  };
} // namespace Units