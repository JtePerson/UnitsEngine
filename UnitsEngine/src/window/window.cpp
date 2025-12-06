#include "UnitsEngine/window/window.h"

#include <SDL3/SDL.h>

#include "UnitsEngine/core/log.h"
#include "UnitsEngine/core/assert.h"
#include "UnitsEngine/gpu/gpu_device.h"

namespace units {
  std::unordered_map<Id, Window*> Window::s_id_map_;
  std::unordered_map<std::string, Window*> Window::s_title_map_;

  Window::Window(const WindowSpecs& p_specs) noexcept {
    if (p_specs.width == 0 || p_specs.height == 0) { return; }
    m_window_ptr_= reinterpret_cast<void*>(SDL_CreateWindow(p_specs.title.c_str(), p_specs.width, p_specs.height, p_specs.flags));
    if (m_window_ptr_ == nullptr) {
      UE_CORE_ERROR("SDL error: {0}", SDL_GetError());
      UE_CORE_ASSERT(false, "Could not create Window!");
    }
    m_id_= SDL_GetWindowID(reinterpret_cast<SDL_Window*>(m_window_ptr_));
    m_title_= p_specs.title;
    s_id_map_[m_id_]= this;
    s_title_map_[p_specs.title]= this;
  }

  void Window::destroy() noexcept {
    if (!expired()) {
      SDL_DestroyWindow(reinterpret_cast<SDL_Window*>(m_window_ptr_));
      m_window_ptr_= nullptr;
      s_id_map_.erase(m_id_);
      s_title_map_.erase(m_title_);
    }
  }

  GPUTextureFormat Window::getGPUTextureFormat(GPUDevice& p_gpu_device) noexcept {
    return static_cast<GPUTextureFormat>(SDL_GetGPUSwapchainTextureFormat(reinterpret_cast<SDL_GPUDevice*>(p_gpu_device.getGPUDevicePtr()), reinterpret_cast<SDL_Window*>(m_window_ptr_)));
  }
} // namespace units