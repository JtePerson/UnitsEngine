#pragma once

namespace units {
  enum GPUSamplerAddressMode {
      UE_GPU_SAMPLERADDRESSMODE_REPEAT,           /**< Specifies that the coordinates will wrap around. */
      UE_GPU_SAMPLERADDRESSMODE_MIRRORED_REPEAT,  /**< Specifies that the coordinates will wrap around mirrored. */
      UE_GPU_SAMPLERADDRESSMODE_CLAMP_TO_EDGE     /**< Specifies that the coordinates will clamp to the 0-1 range. */
  };
} // namespace units