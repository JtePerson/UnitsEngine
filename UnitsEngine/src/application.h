#pragma once
#include "UnitsEngine/iapplication.h"

#include <functional>
#include <SDL3/SDL.h>

#include "layer_stack.h"

namespace units {
  struct IApplication::Impl {
    Impl() noexcept;
    ~Impl() noexcept;

    void run() noexcept;
    void quit() noexcept;

    IApplication* m_application_ptr_;

    bool m_should_run_= false;

    std::function<void()> m_on_run_callback_;
    std::function<void()> m_on_quit_callback_;

    LayerStack m_layer_stack_;
  };
} // namespace units