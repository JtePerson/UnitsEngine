module;

#ifdef UE_INCLUDE_VULKAN
#  define VULKAN_HPP_NO_EXCEPTIONS
#  define VULKAN_HPP_NO_STRUCT_CONSTRUCTORS
#  include <vulkan/vulkan.hpp>
#endif

module units.GPU.Device;

import std;

import units.GPU;
import units.GPU.Surface;

#include "UnitsEngine/core/log.hpp"

#ifdef UE_INCLUDE_VULKAN

namespace units {
  namespace GPU {
    PhysicalDevice::PhysicalDevice(const PhysicalDeviceSpecs& p_specs) noexcept {
      static vk::PhysicalDevice vk_physical_device{};
      if (!Instance::loaded()) {
        UE_ERROR("Could not create GPU Device!");
        UE_ERROR("GPU Instance not loaded!");
        return;
      }
      vk::Instance* vk_instance_ptr= reinterpret_cast<vk::Instance*>(Instance::getInstance()->native());
      auto [vk_result, vk_physical_devices]= vk_instance_ptr->enumeratePhysicalDevices();
      if (vk_result != vk::Result::eSuccess) {
        UE_ERROR("Could not create GPU Device!");
        UE_ERROR("Could not enumerate Vulkan Physical Devices!");
        return;
      }
      if (vk_physical_devices.size() == 0u) {
        UE_ERROR("Could not create GPU Device!");
        UE_ERROR("Could not find any Vulkan Physical Devices!");
        return;
      }
      const auto it= std::find_if(vk_physical_devices.begin(), vk_physical_devices.end(), [&](const vk::PhysicalDevice& p_vk_physical_device) -> bool {
        auto vk_device_features= p_vk_physical_device.getFeatures();
        auto vk_device_props= p_vk_physical_device.getProperties();
        auto vk_queue_family_props= p_vk_physical_device.getQueueFamilyProperties();
        bool is_suitable= vk_device_props.apiVersion >= VK_API_VERSION_1_3;
        auto vk_qfp_it= std::find_if(vk_queue_family_props.begin(), vk_queue_family_props.end(), [](const auto& p_vk_qfp) -> bool {
          return (p_vk_qfp.queueFlags & vk::QueueFlagBits::eGraphics) != static_cast<vk::QueueFlags>(0u);
        });
        is_suitable= is_suitable && (vk_qfp_it != vk_queue_family_props.end());
        return is_suitable;
      });
      if (it == vk_physical_devices.end()) {
        UE_ERROR("Could not create GPU Device!");
        UE_ERROR("Could not find suitable Vulkan Physical Device!");
        return;
      }
      vk_physical_device= *it;
      m_native_ptr_= &vk_physical_device;
      m_id_= it - vk_physical_devices.begin();
    }
    void PhysicalDevice::destroy(void) noexcept {
      if (expired())
        return;
      m_native_ptr_= nullptr;
    }

    Device::Device(const PhysicalDevice& p_physical_device, const Surface& p_surface, const DeviceSpecs& p_specs) noexcept {
      static vk::Device vk_device{};
      if (!Instance::loaded()) {
        UE_ERROR("Could not create GPU Device!");
        UE_ERROR("GPU Instance not loaded!");
        return;
      }
      vk::Instance* vk_instance_ptr= reinterpret_cast<vk::Instance*>(Instance::getInstance()->native());
      auto* vk_physical_device_ptr= reinterpret_cast<vk::PhysicalDevice*>(p_physical_device.native());
      auto* vk_surface_ptr= reinterpret_cast<vk::SurfaceKHR*>(p_surface.native());

      const vk::DeviceCreateFlags vk_device_create_flags{0u};

      const auto vk_device_qfp= vk_physical_device_ptr->getQueueFamilyProperties();
      const auto vk_qfp_it= std::find_if(vk_device_qfp.begin(), vk_device_qfp.end(), [&](const auto& p_vk_qfp) -> bool {
        return (p_vk_qfp.queueFlags & vk::QueueFlagBits::eGraphics) != vk::QueueFlags{0u};
      });
      constexpr uint32_t vk_queue_count= 1u;
      const uint32_t vk_graphics_queue_index= vk_qfp_it - vk_device_qfp.begin();
      const float vk_queue_prority= 0.5f;

      vk::Bool32 vk_supported;
      if (vk_physical_device_ptr->getSurfaceSupportKHR(vk_graphics_queue_index, *vk_surface_ptr, &vk_supported) != vk::Result::eSuccess) {
        UE_ERROR("Could not create Logical Device!");
        UE_ERROR("Vulkan Graphics Queue Family does not support Surface!");
        return;
      }

      constexpr uint32_t vk_queue_create_info_count= 1u;
      const vk::DeviceQueueCreateInfo vk_queue_create_infos[]= {{
        .flags= vk::DeviceQueueCreateFlags{},
        .queueFamilyIndex= vk_graphics_queue_index,
        .queueCount= vk_queue_count,
        .pQueuePriorities= &vk_queue_prority,
      }};

      constexpr uint32_t vk_extension_count= 4u;
      const char* vk_extension_names[]= {
        vk::KHRSwapchainExtensionName,
        vk::KHRSpirv14ExtensionName,
        vk::KHRSynchronization2ExtensionName,
        vk::KHRCreateRenderpass2ExtensionName,
      };

      const auto vk_physical_device_features= vk_physical_device_ptr->getFeatures();

      const vk::DeviceCreateInfo vk_device_create_info{
        .flags= vk_device_create_flags,
        .queueCreateInfoCount= vk_queue_create_info_count,
        .pQueueCreateInfos= vk_queue_create_infos,
        .enabledExtensionCount= vk_extension_count,
        .ppEnabledExtensionNames= vk_extension_names,
        .pEnabledFeatures= &vk_physical_device_features,
      };

      vk::Result vk_result= vk_physical_device_ptr->createDevice(&vk_device_create_info, nullptr, &vk_device);
      if (vk_result != vk::Result::eSuccess) {
        UE_ERROR("Could not construct GPU Device!");
        UE_ERROR("Vulkan Logical Device could not be created!");
        return;
      }

      m_native_ptr_= &vk_device;
    }
    void Device::destroy(void) noexcept {
      if (expired())
        return;
      reinterpret_cast<vk::Device*>(m_native_ptr_)->destroy();
      m_native_ptr_= nullptr;
    }
  } // namespace GPU
} // namespace units

#endif