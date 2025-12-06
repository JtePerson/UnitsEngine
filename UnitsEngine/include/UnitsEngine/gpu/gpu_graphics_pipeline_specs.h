#pragma once
#include "UnitsEngine/gpu/gpu_shader.h"
#include "UnitsEngine/gpu/gpu_texture_format.h"

namespace units {
  struct GPUGraphicsPipelineSpecs final {
    GPUShader* vertex_shader_ptr= nullptr;
    GPUShader* fragment_shader_ptr= nullptr;
    GPUTextureFormat texture_format= GPU_TEXTUREFORMAT_R8G8B8A8_UNORM;
    bool wireframe_mode= false;
  };
} // namespace units