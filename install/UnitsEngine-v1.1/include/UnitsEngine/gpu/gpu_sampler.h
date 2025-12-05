#pragma once
#include "UnitsEngine/core/engine_api.h"
#include "UnitsEngine/gpu/gpu_device.h"
#include "UnitsEngine/gpu/gpu_sampler_specs.h"

namespace units {
  class UE_API GPUSampler final {
  public:
    inline GPUSampler() noexcept= default;
    GPUSampler(GPUDevice& p_gpu_device, GPUSamplerSpecs& p_specs) noexcept;
    inline GPUSampler(GPUSampler&& p_gpu_sampler) noexcept {
      *this= p_gpu_sampler;
      p_gpu_sampler.m_gpu_sampler_ptr_= nullptr;
    }
    inline GPUSampler& operator=(GPUSampler&& p_gpu_sampler) noexcept {
      *this= p_gpu_sampler;
      p_gpu_sampler.m_gpu_sampler_ptr_= nullptr;
      return *this;
    }
    inline ~GPUSampler() noexcept { destroy(); }

    inline bool expired() noexcept { return m_gpu_sampler_ptr_ == nullptr; }

    void destroy() noexcept;

    inline void* getGPUSamplerPtr() noexcept {
      return m_gpu_sampler_ptr_;
    }
  private:
    inline GPUSampler(const GPUSampler&) noexcept= default;
    inline GPUSampler& operator=(const GPUSampler&) noexcept= default;

    void* m_gpu_device_ptr_= nullptr;
    void* m_gpu_sampler_ptr_= nullptr;
  };
} // namespace units

#include "UnitsEngine/gpu/gpu_filter.h"
#include "UnitsEngine/gpu/gpu_sampler_address_mode.h"