#pragma once
#include <stdint.h>

#include "UnitsEngine/gpu/gpu_texture_type.h"
#include "UnitsEngine/gpu/gpu_texture_format.h"
#include "UnitsEngine/gpu/gpu_texture_usage.h"

namespace units {
  struct GPUTextureSpecs final {
    GPUTextureType type;
    GPUTextureFormat format;
    GPUTextureUsageFlags usage= 0;
    uint32_t width= 0u;
    uint32_t height= 0u;
    uint32_t layer_count_or_depth= 0;
  };
} // namespace units