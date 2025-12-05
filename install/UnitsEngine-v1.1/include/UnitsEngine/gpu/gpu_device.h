#pragma once
#include "UnitsEngine/core/engine_api.h"
#include "UnitsEngine/window/window.h"

namespace units {
  class UE_API GPUDevice final {
  public:
    inline GPUDevice() noexcept= default;
    GPUDevice(Window& p_window) noexcept;
    inline GPUDevice(GPUDevice&& p_gpu_device) noexcept {
      *this= p_gpu_device;
      p_gpu_device.m_gpu_device_ptr_= nullptr;
    }
    inline GPUDevice& operator=(GPUDevice&& p_gpu_device) noexcept {
      *this= p_gpu_device;
      p_gpu_device.m_gpu_device_ptr_= nullptr;
      return *this;
    }
    inline ~GPUDevice() noexcept { destroy(); }

    inline bool expired() noexcept { return m_gpu_device_ptr_ == nullptr; }
    
    void claimWindow(Window& p_window) noexcept;

    inline void* getGPUDevicePtr() noexcept { return m_gpu_device_ptr_; }

    void destroy() noexcept;
  private:
    inline GPUDevice(const GPUDevice&) noexcept= default;
    inline GPUDevice& operator=(const GPUDevice&) noexcept= default;

    void* m_gpu_device_ptr_= nullptr;
  };
} // namespace units