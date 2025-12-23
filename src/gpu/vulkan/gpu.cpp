module;

#include <ranges>

#include <stdint.h>

#include "UnitsEngine/config.h"

#ifdef UE_INCLUDE_VULKAN
#  define VULKAN_HPP_NO_EXCEPTIONS
#  define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#  include <vulkan/vulkan.hpp>

#  include "UnitsEngine/gpu/vulkan/gpu.h"
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
        const vk::InstanceCreateFlags vk_instance_flags{};

        auto vk_application_info= vk::ApplicationInfo{
          .pApplicationName= p_specs.app_name,
          .applicationVersion= VK_MAKE_VERSION(p_specs.app_version_major, p_specs.app_version_minor, p_specs.app_version_patch),
          .pEngineName= "UnitsEngine",
          .engineVersion= VK_MAKE_VERSION(UE_VERSION_MAJOR, UE_VERSION_MINOR, UE_VERSION_PATCH),
          .apiVersion= vk::ApiVersion14,
        };

        static constexpr uint32_t vk_layer_count= 1u;
        static const char* vk_layer_names[]= {
          "VK_LAYER_KHRONOS_validation",
        };

        if (p_debug_mode) {
          auto [vk_result, vk_layer_properties]= vk::enumerateInstanceLayerProperties();
          if (vk_result != vk::Result::eSuccess) {
            UE_ERROR("Could not Init GPU Instance!");
            UE_ERROR("Could not enumerate Vulkan Layers!");
            return false;
          }
          for (uint32_t i= 0; i < vk_layer_count; ++i) {
            const bool none_same= std::ranges::none_of(vk_layer_properties, [vk_layer_name= vk_layer_names[i]](const auto& p_layer_props) -> bool {
              return std::strcmp(p_layer_props.layerName, vk_layer_name) == 0;
            });
            if (none_same) {
              UE_ERROR("Could not Init GPU Instance!");
              UE_ERROR("One or more Vulkan Layers not found!");
              return false;
            }
          }
        }

        static uint32_t vk_extension_count= 0u;
        static const char** vk_extension_names= nullptr;

#  ifdef UE_INCLUDE_GLFW
        if (p_debug_mode) {
          vk_extension_names= glfwGetRequiredInstanceExtensions(&vk_extension_count);
          auto [vk_result, vk_extension_properties]= vk::enumerateInstanceExtensionProperties();
          if (vk_result != vk::Result::eSuccess) {
            UE_ERROR("Could not Init GPU Instance!");
            UE_ERROR("Could not enumerate Vulkan Extensions!");
            return false;
          }
          for (uint32_t i= 0; i < vk_extension_count; ++i) {
            const bool none_same= std::ranges::none_of(vk_extension_properties, [vk_extension_name= vk_extension_names[i]](const auto& p_extension_props) -> bool {
              return std::strcmp(p_extension_props.extensionName, vk_extension_name) == 0;
            });
            if (none_same) {
              UE_ERROR("Could not Init GPU Instance!");
              UE_ERROR("One or more Vulkan Extensions not found!");
              return false;
            }
          }
        }
#  endif

        const vk::InstanceCreateInfo vk_instance_create_info{
          .flags= vk_instance_flags,
          .pApplicationInfo= &vk_application_info,
          .enabledLayerCount= p_debug_mode ? vk_layer_count : 0u,
          .ppEnabledLayerNames= vk_layer_names,
          .enabledExtensionCount= p_debug_mode ? vk_extension_count : 0u,
          .ppEnabledExtensionNames= vk_extension_names,
        };

        static vk::Instance vk_instance{};
        vk::Result vk_result= vk::createInstance(&vk_instance_create_info, nullptr, &vk_instance);
        if (vk_result != vk::Result::eSuccess) {
          UE_ERROR("Could not Init GPU Instance!");
          UE_ERROR("Vulkan Instance could not be created!");
          return false;
        }

        s_instance_ptr_= [&]() -> Instance* {
          static InstanceProps instance_props{
            .vk_layer_count= p_debug_mode ? vk_layer_count : 0u,
            .vk_layer_names= vk_layer_names,
            .vk_extension_count= p_debug_mode ? vk_extension_count : 0u,
            .vk_extension_names= vk_extension_names,
          };
          static Instance instance{};
          instance.m_native_ptr_= &vk_instance;
          instance.m_props_ptr_= &instance_props;
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
      s_instance_ptr_->m_native_ptr_= nullptr;
    }
  } // namespace GPU
} // namespace units

#endif