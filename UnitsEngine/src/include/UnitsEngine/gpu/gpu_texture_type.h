#pragma once

namespace Units {
  enum GPUTextureType {
    UE_GPU_TEXTURETYPE_2D,         /**< The texture is a 2-dimensional image. */
    UE_GPU_TEXTURETYPE_2D_ARRAY,   /**< The texture is a 2-dimensional array image. */
    UE_GPU_TEXTURETYPE_3D,         /**< The texture is a 3-dimensional image. */
    UE_GPU_TEXTURETYPE_CUBE,       /**< The texture is a cube image. */
    UE_GPU_TEXTURETYPE_CUBE_ARRAY  /**< The texture is a cube array image. */
  };
} // namespace Units