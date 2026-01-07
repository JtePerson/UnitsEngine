#pragma once

#ifdef __INTELLISENSE__
#  include "../modules/gpu/gpu.mpp"
#endif

namespace units {
  namespace GPU {
    struct InstanceProps final {
#ifdef UE_INCLUDE_VULKAN
      const uint32_t vk_layer_count= 0u; 
      const char** vk_layer_names= nullptr;
      const uint32_t vk_extension_count= 0u;
      const char** vk_extension_names= nullptr;
#endif
    };
  } // namespace GPU
} // namespace units