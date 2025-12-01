#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <glm/vec2.hpp>

#include "UnitsEngine/core/engine_api.h"
#include "UnitsEngine/types/number.h"
#include "UnitsEngine/window/window_specs.h"
#include "UnitsEngine/core/assert.h"
#include "UnitsEngine/gpu/gpu_command_buffer.h"

namespace Units {
  class GPUTexture;
  class UE_API Window final {
  public:
    inline Window() noexcept {}
    inline Window(Window&) noexcept= default;
    inline Window(Window&&) noexcept= default;
    inline Window(const Window&) noexcept= delete;
    inline Window& operator=(Window&) noexcept= default;
    inline Window& operator=(Window&&) noexcept= default;
    inline Window& operator=(const Window&) noexcept= delete;
    ~Window() noexcept;

    static Window& newWindow(const WindowSpecs& p_specs) noexcept;
    static inline Window& getFromTitle(const std::string& p_window_title) noexcept {
      UE_CORE_ASSERT(s_window_title_map_.find(p_window_title) != s_window_title_map_.end(), "Window with Title does not exist!");
      return s_window_title_map_.at(p_window_title);
    }
    inline Id getId() noexcept { return m_id_; }
    inline bool expired() const noexcept { return m_expired_; }
    void make_expired() noexcept;

    glm::i32vec2 getSize() noexcept;

    GPUTexture getGPUTexture(GPUCommandBuffer& p_gpu_command_buffer, const bool& p_wait= true) noexcept;
  private:
    Window(const WindowSpecs& p_specs) noexcept;
    std::string m_title_= "";
    Id m_id_= k_null_Id;

    bool m_expired_= true;
    
    static std::unordered_map<std::string, Window> s_window_title_map_;
  };
} // namespace Units

#include "UnitsEngine/window/window_flags.h"