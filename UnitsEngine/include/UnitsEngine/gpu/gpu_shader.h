#pragma once
#include "UnitsEngine/core/engine_api.h"
#include "UnitsEngine/gpu/gpu_device.h"
#include "UnitsEngine/gpu/gpu_shader_specs.h"

namespace units {
  class UE_API GPUShader final {
  public:
    inline GPUShader() noexcept= default;
    GPUShader(GPUDevice& p_gpu_device, const GPUShaderSpecs& p_specs) noexcept;
    inline GPUShader(GPUShader&& p_other) noexcept {
      *this= p_other;
      p_other.m_gpu_shader_ptr_= nullptr;
    }
    inline GPUShader& operator=(GPUShader&& p_other) noexcept {
      *this= p_other;
      p_other.m_gpu_shader_ptr_= nullptr;
      return *this;
    }
    inline ~GPUShader() noexcept { destroy(); }

    inline bool expired() noexcept { return m_gpu_shader_ptr_ == nullptr; }

     void destroy() noexcept;

     inline void* getGPUShaderPtr() noexcept { return m_gpu_shader_ptr_; }
  private:
    inline GPUShader(const GPUShader&) noexcept= default;
    inline GPUShader& operator=(const GPUShader&) noexcept= default;

    void* m_gpu_shader_ptr_= nullptr;
    void* m_gpu_device_ptr_= nullptr;
  };
} // namespace units