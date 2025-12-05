#pragma once

namespace units {
  enum GPUTextureType {
    GPU_TEXTURETYPE_2D,         /**< The texture is a 2-dimensional image. */
    GPU_TEXTURETYPE_2D_ARRAY,   /**< The texture is a 2-dimensional array image. */
    GPU_TEXTURETYPE_3D,         /**< The texture is a 3-dimensional image. */
    GPU_TEXTURETYPE_CUBE,       /**< The texture is a cube image. */
    GPU_TEXTURETYPE_CUBE_ARRAY  /**< The texture is a cube array image. */
  };
} // namespace units