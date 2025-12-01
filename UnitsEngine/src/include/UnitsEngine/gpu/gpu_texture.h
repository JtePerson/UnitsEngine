#pragma once
#include "UnitsEngine/core/engine_api.h"
#include "UnitsEngine/gpu/gpu_device.h"
#include "UnitsEngine/gpu/gpu_texture_specs.h"
#include "UnitsEngine/gpu/gpu_command_buffer.h"

namespace Units {
  class Window;
  class UE_API GPUTexture final {
  public:
    friend class Window;
  public:
    inline GPUTexture() noexcept
    : m_gpu_device_ptr_(nullptr), m_gpu_texture_ptr_(nullptr), m_from_window_(false)
    {}
    inline GPUTexture(GPUTexture&& p_gpu_texture) noexcept {
      *this= p_gpu_texture;
      p_gpu_texture.m_gpu_texture_ptr_= nullptr;
    }
    inline GPUTexture& operator=(GPUTexture&& p_gpu_texture) noexcept {
      *this= p_gpu_texture;
      p_gpu_texture.m_gpu_texture_ptr_= nullptr;
      return *this;
    }
    GPUTexture(GPUDevice& p_gpu_device, GPUTextureSpecs& p_specs) noexcept;
    ~GPUTexture() noexcept;
    inline void* getGPUTexturePtr() noexcept {
      return m_gpu_texture_ptr_;
    }
  private:
    inline GPUTexture(const GPUTexture&) noexcept= default;
    inline GPUTexture& operator=(const GPUTexture&) noexcept= default;
    GPUTexture(GPUCommandBuffer& p_gpu_command_buffer, Window& p_window, const bool& p_wait= true) noexcept;

    void* m_gpu_device_ptr_= nullptr;
    void* m_gpu_texture_ptr_= nullptr;

    bool m_from_window_= false;
  };
} // namespace Units

#include "UnitsEngine/gpu/gpu_texture_format.h"
#include "UnitsEngine/gpu/gpu_texture_type.h"
#include "UnitsEngine/gpu/gpu_texture_usage.h"