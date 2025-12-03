#pragma once
#include "UnitsEngine/window/window_specs.h"

#include <unordered_map>
#include <string>

#include "UnitsEngine/core/engine_api.h"
#include "UnitsEngine/types/number.h"

namespace units {
  class UE_API Window final {
  public:
    inline Window() noexcept= default;
    Window(const WindowSpecs& p_specs) noexcept;
    inline Window(Window&& p_other) noexcept {
      *this= p_other;
      p_other.m_window_ptr_= nullptr;
      if (m_window_ptr_ != nullptr) {
        s_id_map_[m_id_]= this;
        s_title_map_[m_title_]= this;
      }
    }
    inline Window& operator=(Window&& p_other) noexcept {
      *this= p_other;
      p_other.m_window_ptr_= nullptr;
      if (m_window_ptr_ != nullptr) {
        s_id_map_[m_id_]= this;
        s_title_map_[m_title_]= this;
      }
      return *this;
    }
    ~Window() noexcept;

    static inline Window* getFromId(const Id& p_window_id) noexcept {
      const auto window_it= s_id_map_.find(p_window_id);
      if (window_it == s_id_map_.end()) {
        return nullptr;
      }
      return window_it->second;
    }
    static inline Window* getFromTitle(const std::string& p_window_title) noexcept {
      const auto window_it= s_title_map_.find(p_window_title);
      if (window_it == s_title_map_.end()) {
        return nullptr;
      }
      return window_it->second;
    }
  private:
    inline Window(const Window& p_other) noexcept= default;
    inline Window& operator=(const Window& p_other) noexcept= default;

    void* m_window_ptr_= nullptr;
    Id m_id_= k_null_Id;
    std::string m_title_= "";

    static std::unordered_map<Id, Window*> s_id_map_;
    static std::unordered_map<std::string, Window*> s_title_map_;
  };
} // namespace units