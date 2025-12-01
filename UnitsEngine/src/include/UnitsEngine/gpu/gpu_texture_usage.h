#pragma once
#include <stdint.h>

namespace Units {
  using GPUTextureUsageFlags= uint32_t;

  #define UE_GPU_TEXTUREUSAGE_SAMPLER                                 (1u << 0) /**< Texture supports sampling. */
  #define UE_GPU_TEXTUREUSAGE_COLOR_TARGET                            (1u << 1) /**< Texture is a color render target. */
  #define UE_GPU_TEXTUREUSAGE_DEPTH_STENCIL_TARGET                    (1u << 2) /**< Texture is a depth stencil target. */
  #define UE_GPU_TEXTUREUSAGE_GRAPHICS_STORAGE_READ                   (1u << 3) /**< Texture supports storage reads in graphics stages. */
  #define UE_GPU_TEXTUREUSAGE_COMPUTE_STORAGE_READ                    (1u << 4) /**< Texture supports storage reads in the compute stage. */
  #define UE_GPU_TEXTUREUSAGE_COMPUTE_STORAGE_WRITE                   (1u << 5) /**< Texture supports storage writes in the compute stage. */
  #define UE_GPU_TEXTUREUSAGE_COMPUTE_STORAGE_SIMULTANEOUS_READ_WRITE (1u << 6) /**< Texture supports reads and writes in the same compute shader. This is NOT equivalent to READ | WRITE. */
} // namespace Units