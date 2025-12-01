#include "UnitsEngine/window/window_specs.h"
#include "UnitsEngine/window/window.h"
#include "window/window.h"

#include <SDL3/SDL.h>
#include <memory>
#include <string>
#include <glm/vec2.hpp>

#include "UnitsEngine/core/assert.h"
#include "UnitsEngine/gpu/gpu_texture.h"

namespace Units {
  std::unordered_map<std::string, Window> Window::s_window_title_map_;

  Window::Window(const WindowSpecs& p_specs) noexcept {
    m_title_= p_specs.title;
    m_expired_= false;
  }
  Window& Window::newWindow(const WindowSpecs& p_specs) noexcept {
    UE_CORE_ASSERT(s_window_title_map_.find(p_specs.title) == s_window_title_map_.end(), "Window with WindowSpecs.title already exists!");
    auto& new_window= s_window_title_map_[p_specs.title]= p_specs;
    core::Window::createWindow(p_specs, &new_window, &new_window.m_id_);
    return new_window;
  }
  Window::~Window() noexcept {
    if (m_expired_) { return; }
    core::Window::destroyWindow(m_id_);
    s_window_title_map_.erase(m_title_);
  }
  void Window::make_expired() noexcept {
    if (core::Window::windowExists(m_id_)) {
      core::Window::s_window_id_map_.erase(m_id_);
    }
    m_expired_= true;
  }

  glm::i32vec2 Window::getSize() noexcept {
    glm::i32vec2 i32v2{};
    SDL_GetWindowSize(core::Window::getFromId(m_id_).getSDLWindowPtr(), &i32v2.x, &i32v2.y);
    return i32v2;
  }

  GPUTexture Window::getGPUTexture(GPUCommandBuffer& p_gpu_command_buffer, const bool& p_wait) noexcept {
    return GPUTexture{p_gpu_command_buffer, *this, p_wait};
  }

  namespace core {
    std::unordered_map<Id, core::Window> core::Window::s_window_id_map_;

    bool core::Window::windowExists(const Id& p_window_id) noexcept {
      auto core_window_it= s_window_id_map_.find(p_window_id);
      return core_window_it != s_window_id_map_.end();
    }
    Id core::Window::createWindow(const WindowSpecs& p_specs, Units::Window* p_window_ptr, Id* p_window_id_ptr) noexcept {
      SDL_Window* sdl_window_ptr= SDL_CreateWindow(p_specs.title.c_str(), p_specs.width, p_specs.height, p_specs.flags);
      Id sdl_window_id= SDL_GetWindowID(sdl_window_ptr);

      core::Window& window= s_window_id_map_[sdl_window_id];
      window.m_window_ptr= p_window_ptr;
      window.m_sdl_window_ptr_= sdl_window_ptr;
      window.m_id_= sdl_window_id;

      if (p_window_id_ptr != nullptr) {
        *p_window_id_ptr= sdl_window_id;
      }
      return sdl_window_id;
    }
    void core::Window::destroyWindow(const Id& p_window_id) noexcept {
      if (!windowExists(p_window_id)) { return; }
      core::Window window= s_window_id_map_.at(p_window_id);
      s_window_id_map_.erase(p_window_id);
      if (window.m_window_ptr != nullptr) {
        window.m_window_ptr->make_expired();
      }
      SDL_DestroyWindow(window.m_sdl_window_ptr_);
    }
  } // namespace core
} // namespace Units