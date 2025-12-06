#pragma once
#include <stdint.h>
#include <string>

namespace units {
  struct GPUShaderSpecs final {
    std::string filepath= "";
    uint32_t sampler_count= 0;
    uint32_t storage_texture_count= 0;
    uint32_t storage_buffer_count= 0;
    uint32_t uniform_buffer_count= 0;
  };
} // namespace units