#pragma once
#include "UnitsEngine/core/engine_api.h"
#include "UnitsEngine/gpu/gpu_texture.h"
#include "UnitsEngine/gpu/gpu_sampler.h"

namespace Units {
  class UE_API GPUTextureSamplerBinding final {
  public:
    inline GPUTextureSamplerBinding() noexcept= default;
    inline GPUTextureSamplerBinding(GPUTexture* p_gpu_texture_ptr, GPUSampler* p_gpu_sampler_ptr) noexcept
    : m_gpu_texture_ptr_(p_gpu_texture_ptr), m_gpu_sampler_ptr_(p_gpu_sampler_ptr)
    {}
    inline ~GPUTextureSamplerBinding() noexcept= default;
    void* getGPUTextureSamplerBindingPtr() noexcept;
  private:
    GPUTexture* m_gpu_texture_ptr_= nullptr;
    GPUSampler* m_gpu_sampler_ptr_= nullptr;
  };
} // namespace Units