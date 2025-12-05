#pragma once
#include "UnitsEngine/gpu/gpu_filter.h"
#include "UnitsEngine/gpu/gpu_sampler_address_mode.h"

namespace units {
  struct GPUSamplerSpecs final {
    GPUFilter min_filter= UE_GPU_FILTER_NEAREST;
    GPUFilter mag_filter= UE_GPU_FILTER_NEAREST;
    GPUSamplerAddressMode adress_mode_u= UE_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
    GPUSamplerAddressMode adress_mode_v= UE_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
    GPUSamplerAddressMode adress_mode_w= UE_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE;
  };
} // namespace units