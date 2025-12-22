module;

#include <ranges>

#include <stdint.h>

#include "UnitsEngine/config.h"

#ifdef UE_INCLUDE_VULKAN
#  define VULKAN_HPP_NO_EXCEPTIONS
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
        vk::ApplicationInfo app_info{};
        app_info.pApplicationName= p_specs.app_name;
        app_info.applicationVersion= VK_MAKE_VERSION(p_specs.app_version_major, p_specs.app_version_minor, p_specs.app_version_patch);
        app_info.pEngineName= "UnitsEngine";
        app_info.engineVersion= VK_MAKE_VERSION(UE_VERSION_MAJOR, UE_VERSION_MINOR, UE_VERSION_PATCH);
        app_info.apiVersion= vk::ApiVersion14;

        uint32_t extension_count= 0u;
        const char** extension_names= nullptr;

#  ifdef UE_INCLUDE_GLFW
        extension_names= glfwGetRequiredInstanceExtensions(&extension_count);

        auto [extension_result, extension_properties]= vk::enumerateInstanceExtensionProperties();
        for (size_t i= 0u; i < extension_count; ++i) {
          const bool none_same= std::ranges::none_of(extension_properties, [glfw_extention_name= extension_names[i]](const auto& p_extension_props) -> bool {
            return std::strcmp(glfw_extention_name, p_extension_props.extensionName) == 0;
          });
          if (none_same) {
            UE_ERROR("Could not Init GPU Instance!");
            return false;
          }
        }
#  endif

        constexpr uint32_t validation_layer_count= 0u;
        const char* validation_layer_names[]= {
          "VK_LAYER_KHRONOS_validation",
        };

        if (p_debug_mode) {
          auto [result, validation_layer_properties]= vk::enumerateInstanceLayerProperties();
          for (size_t i= 0u; i < validation_layer_count; ++i) {
            const bool none_same= std::ranges::none_of(validation_layer_properties, [validation_layer_name= validation_layer_names[i]](const auto& p_validation_layer_props) -> bool {
              return std::strcmp(validation_layer_name, p_validation_layer_props.layerName) == 0;
            });
            if (none_same) {
              UE_ERROR("Could not Init GPU Instance!");
              return false;
            }
          }
        }

        vk::InstanceCreateInfo instance_create_info{};
        instance_create_info.pApplicationInfo= &app_info;
        instance_create_info.enabledExtensionCount= extension_count;
        instance_create_info.ppEnabledExtensionNames= extension_names;
        instance_create_info.enabledLayerCount= p_debug_mode ? validation_layer_count : 0u;
        instance_create_info.ppEnabledLayerNames= p_debug_mode ? validation_layer_names : nullptr;

        s_instance_ptr_= [&]() -> Instance* {
          static auto [result, vk_instance]= vk::createInstance(instance_create_info);
          static Instance instance{};
          if (result != vk::Result::eSuccess) {
            UE_ERROR("Could not Create GPU Instance!");
            return nullptr;
          }
          instance.m_native_ptr_= &vk_instance;
          return &instance;
        }();

        return s_instance_ptr_ != nullptr;
      }();
      return initialized;
    }
    void Instance::quit(void) noexcept {
      if (!s_instance_ptr_->m_initialized_)
        return;
      reinterpret_cast<vk::Instance*>(s_instance_ptr_->m_native_ptr_)->destroy();
    }
  } // namespace GPU
} // namespace units

#endif