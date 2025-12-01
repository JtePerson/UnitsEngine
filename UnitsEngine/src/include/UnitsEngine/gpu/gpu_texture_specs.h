#pragma once
#include <stdint.h>

#include "UnitsEngine/gpu/gpu_texture_type.h"
#include "UnitsEngine/gpu/gpu_texture_format.h"
#include "UnitsEngine/gpu/gpu_texture_usage.h"

namespace Units {
  struct GPUTextureSpecs final {
    GPUTextureType type= UE_GPU_TEXTURETYPE_2D;
    GPUTextureFormat format= UE_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM;
    GPUTextureUsageFlags usage= UE_GPU_TEXTUREUSAGE_COLOR_TARGET;
    uint32_t width= 0u;
    uint32_t height= 0u;
    uint32_t layer_count_or_depth= 1;
  };
} // namespace Units