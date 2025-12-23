module;

#include <ranges>

#include <stdint.h>

#include "UnitsEngine/config.h"

#ifdef UE_INCLUDE_VULKAN
#  define VULKAN_HPP_NO_EXCEPTIONS
#  define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#  include <vulkan/vulkan.hpp>
#endif

#ifdef UE_INCLUDE_GLFW
#  include <GLFW/glfw3.h>
#endif

#ifdef __INTELLISENSE__
#  include "../modules/gpu/gpu.mpp"
#endif

module units.GPU;

#include "UnitsEngine/core/log.hpp"

#ifdef UE_INCLUDE_VULKAN

namespace units {
  namespace GPU {
    Instance* Instance::s_instance_ptr_= nullptr;

    bool Instance::init(const InstanceSpecs& p_specs, const bool& p_debug_mode) noexcept {
      static const bool initialized= [&]() -> bool {
        vk::InstanceCreateFlags vk_instance_flags{};

        auto vk_application_info= vk::ApplicationInfo{
          .pApplicationName= p_specs.app_name,
          .applicationVersion= VK_MAKE_VERSION(p_specs.app_version_major, p_specs.app_version_minor, p_specs.app_version_patch),
          .pEngineName= "UnitsEngine",
          .engineVersion= VK_MAKE_VERSION(UE_VERSION_MAJOR, UE_VERSION_MINOR, UE_VERSION_PATCH),
          .apiVersion= vk::ApiVersion14,
        };

        constexpr uint32_t vk_layer_count= 0u;
        const char* vk_layer_names[]= {};

        constexpr uint32_t vk_extension_count= 0u;
        const char* vk_extension_names[]= {};

        const auto vk_instance_create_info= vk::InstanceCreateInfo{
          .flags= vk_instance_flags,
          .pApplicationInfo= &vk_application_info,
          .enabledLayerCount= vk_layer_count,
          .ppEnabledLayerNames= vk_layer_names,
          .enabledExtensionCount= vk_extension_count,
          .ppEnabledExtensionNames= vk_extension_names,
        };

        static vk::Instance vk_instance{};
        vk::Result vk_result= vk::createInstance(&vk_instance_create_info, nullptr, &vk_instance);
        if (vk_result != vk::Result::eSuccess)
          return false;

        s_instance_ptr_= [&]() -> Instance* {
          static Instance instance{};
          instance.m_native_ptr_= &vk_instance;
          return &instance;
        }();

        return s_instance_ptr_ != nullptr;
      }();
      return initialized;
    }
    void Instance::quit(void) noexcept {
      if (s_instance_ptr_ == nullptr || s_instance_ptr_->m_native_ptr_ == nullptr)
        return;
      reinterpret_cast<vk::Instance*>(s_instance_ptr_->m_native_ptr_)->destroy();
    }
  } // namespace GPU
} // namespace units

#endif