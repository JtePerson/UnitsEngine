module;

#ifdef UE_INCLUDE_VULKAN
#  define VK_HPP_NO_EXCEPTIONS
#  define VK_HPP_NO_STRUCT_CONSTRUCTORS
#  include <vulkan/vulkan.hpp>
#endif

#ifdef UE_INCLUDE_GLFW
#  include <GLFW/glfw3.h>
#endif

#ifdef __INTELLISENSE__
#  include "../modules/gpu/gpu.mpp"
#  include "../modules/gpu/gpu_surface.mpp"
#  include "../modules/window.mpp"
#endif

module units.GPU.Surface;

#include "UnitsEngine/core/log.hpp"

import units.GPU;
import units.Window;

#ifdef UE_INCLUDE_VULKAN

namespace units {
  namespace GPU {
    Surface::Surface(const Instance& p_gpu_instance, const Window& p_window) noexcept {
      static vk::SurfaceKHR vk_surface{};
      VkSurfaceKHR vk_surface_handle;
#  ifdef UE_INCLUDE_GLFW
      if (glfwCreateWindowSurface(*reinterpret_cast<vk::Instance*>(p_gpu_instance.native()), reinterpret_cast<GLFWwindow*>(p_window.native()), nullptr, &vk_surface_handle) != 0u) {
        UE_ERROR("Could not create Surface from Window!");
        UE_ERROR("Could not create VKSurfaceKHR from GLFW Window!");
        return;
      }
#  endif
      vk_surface= vk_surface_handle;
      m_native_ptr_= &vk_surface;
    }
    void Surface::destroy(void) noexcept {
      if (expired())
        return;
      vk::Instance* vk_instance_ptr= reinterpret_cast<vk::Instance*>(Instance::getInstance()->native());
      vk_instance_ptr->destroySurfaceKHR(*reinterpret_cast<vk::SurfaceKHR*>(m_native_ptr_));
      m_native_ptr_= nullptr;
    }
  } // namespace GPU
} // namespace units

#endif