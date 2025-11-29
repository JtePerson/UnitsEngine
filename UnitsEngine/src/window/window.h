#pragma once
#include "UnitsEngine/window/window_specs.h"
#include "UnitsEngine/window/window.h"

#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>

#include "UnitsEngine/types/number.h"

namespace Units {
  namespace core {
    class Window final {
    public:
      friend class ::Units::Window;
    public:
      inline Window() noexcept= default;
      inline ~Window() noexcept= default;
      static Id createWindow(const WindowSpecs& p_specs, Units::Window* p_window_ptr= nullptr, Id* p_window_id= nullptr) noexcept;
      static void destroyWindow(const Id& p_window_id) noexcept;
      static bool windowExists(const Id& p_window_id) noexcept;
      static inline core::Window& getFromId(const Id& p_window_id) noexcept {
        UE_CORE_ASSERT(s_window_id_map_.find(p_window_id) != s_window_id_map_.end(), "Window with Id does not exist!");
        return s_window_id_map_.at(p_window_id);
      }
      inline SDL_Window* getSDLWindowPtr() noexcept {
        return m_sdl_window_ptr_;
      }
      inline SDL_WindowID getSDLWindowId() noexcept {
        return m_id_;
      }
    private:

      Units::Window* m_window_ptr= nullptr;
      SDL_Window* m_sdl_window_ptr_= nullptr;
      Id m_id_= k_null_Id;

      static std::unordered_map<Id, Window> s_window_id_map_;
    };
  } // namespace core
} // namespace Units