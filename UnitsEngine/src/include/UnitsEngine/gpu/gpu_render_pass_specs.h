#pragma once
#include "UnitsEngine/types/float.h"
#include "UnitsEngine/gpu/gpu_texture.h"

namespace Units {
  struct GPURenderPassSpecs final {
    GPUTexture& texture;
    struct {
      float32_t r= 0.0f, g= 0.0f, b= 0.0f, a= 1.0f;
    } clear_color;
  };
} // namespace Units