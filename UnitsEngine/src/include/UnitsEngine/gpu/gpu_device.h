#pragma once
#include "UnitsEngine/core/engine_api.h"

namespace Units {
  class Window;
  class UE_API GPUDevice final {
  public:
    GPUDevice() noexcept;
    inline GPUDevice(GPUDevice&& p_gpu_device) noexcept {
      *this= p_gpu_device;
      p_gpu_device.m_gpu_device_ptr_= nullptr;
    }
    inline GPUDevice& operator=(GPUDevice&& p_gpu_device) noexcept {
      *this= p_gpu_device;
      p_gpu_device.m_gpu_device_ptr_= nullptr;
      return *this;
    }
    ~GPUDevice() noexcept;
    
    void claimWindow(Window& p_window) noexcept;
    inline void* getDevicePtr() noexcept {
      return m_gpu_device_ptr_;
    }
  private:
    inline GPUDevice(const GPUDevice&) noexcept= default;
    inline GPUDevice& operator=(const GPUDevice&) noexcept= default;

    void* m_gpu_device_ptr_= nullptr;
  };
} // namespace Units