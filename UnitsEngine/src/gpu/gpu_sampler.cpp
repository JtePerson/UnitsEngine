#include "UnitsEngine/gpu/gpu_sampler.h"

#include <SDL3/SDL.h> 

#include "UnitsEngine/gpu/gpu_device.h"
#include "UnitsEngine/gpu/gpu_sampler_specs.h"
#include "UnitsEngine/core/log.h"
#include "UnitsEngine/core/assert.h"

namespace units {
  GPUSampler::GPUSampler(GPUDevice& p_gpu_device, GPUSamplerSpecs& p_specs) noexcept {
    if (p_gpu_device.expired()) { return; }
    m_gpu_device_ptr_= p_gpu_device.getGPUDevicePtr();
    auto* sdl_gpu_device_ptr= reinterpret_cast<SDL_GPUDevice*>(m_gpu_device_ptr_);
    SDL_GPUSamplerCreateInfo sdl_gpu_sampler_create_info= {
      .min_filter= static_cast<SDL_GPUFilter>(p_specs.min_filter),
      .mag_filter= static_cast<SDL_GPUFilter>(p_specs.mag_filter),
      .mipmap_mode= SDL_GPU_SAMPLERMIPMAPMODE_NEAREST,
      .address_mode_u= static_cast<SDL_GPUSamplerAddressMode>(p_specs.adress_mode_u),
      .address_mode_v= static_cast<SDL_GPUSamplerAddressMode>(p_specs.adress_mode_v),
      .address_mode_w= static_cast<SDL_GPUSamplerAddressMode>(p_specs.adress_mode_w)
    };
    m_gpu_sampler_ptr_= SDL_CreateGPUSampler(sdl_gpu_device_ptr, &sdl_gpu_sampler_create_info);
    if (m_gpu_sampler_ptr_ == nullptr) {
      UE_CORE_ERROR("SDL error: {0}", SDL_GetError());
      UE_CORE_ASSERT(false, "Could not create GPUSampler!");
    }
  }
  void GPUSampler::destroy() noexcept {
    if (!expired()) {
      SDL_ReleaseGPUSampler(reinterpret_cast<SDL_GPUDevice*>(m_gpu_device_ptr_), reinterpret_cast<SDL_GPUSampler*>(m_gpu_sampler_ptr_));
      m_gpu_sampler_ptr_= nullptr;
    }
  }
} // namespace units