#include "UnitsEngine/gpu/gpu_texture_sampler_binding.h"

#include <SDL3/SDL.h>

namespace Units {
  void* GPUTextureSamplerBinding::getGPUTextureSamplerBindingPtr() noexcept {
    SDL_GPUTextureSamplerBinding sdl_gpu_texture_sampler_binding;
    sdl_gpu_texture_sampler_binding= {
      .texture= reinterpret_cast<SDL_GPUTexture*>(m_gpu_texture_ptr_->getGPUTexturePtr()),
      .sampler= reinterpret_cast<SDL_GPUSampler*>(m_gpu_sampler_ptr_->getGPUSamplerPtr())
    };
    return reinterpret_cast<void*>(&sdl_gpu_texture_sampler_binding);
  }
} // namespace Units