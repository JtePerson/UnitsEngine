module;

#ifdef UE_INCLUDE_GLFW
#  include <GLFW/glfw3.h>
#endif

#include "UnitsEngine/events/window_events.hpp"

module units.Window;

#include "UnitsEngine/core/log.hpp"

#ifdef UE_INCLUDE_GLFW

namespace units {
  std::unordered_map<const char*, Window*> Window::s_title_map_{};

  Window::Window(const WindowSpecs& p_specs) noexcept {
    if (p_specs.render_backend == RenderBackend::Vulkan)
      glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    m_native_ptr_= glfwCreateWindow(1280, 720, p_specs.title, nullptr, nullptr);
    if (m_native_ptr_ == nullptr) {
      UE_ERROR("Could not Create Window!");
      return;
    }

    m_title_= p_specs.title;
    s_title_map_[m_title_]= this;
  }

  void Window::destroy(void) noexcept {
    if (expired())
      return;

    glfwDestroyWindow(reinterpret_cast<GLFWwindow*>(m_native_ptr_));
    m_native_ptr_= nullptr;
    s_title_map_.erase(m_title_);
  }

  void Window::pollCloseEvents(Events::EventBus& p_event_bus) noexcept {
    for (auto& [title, window_ptr] : s_title_map_) {
      auto* glfw_window_ptr= reinterpret_cast<GLFWwindow*>(window_ptr->native());
      if (glfwWindowShouldClose(glfw_window_ptr)) {
        Events::WindowCloseEvent event{
          .title= title,
        };
        p_event_bus.pushEvent(&event);
      }
    }
  }
} // namespace units

#endif