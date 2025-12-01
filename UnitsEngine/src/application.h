#pragma once
#include "UnitsEngine/iapplication.h"

#include <functional>

#include "layer_stack.h"

namespace Units {
  struct IApplication::Impl {
    Impl() noexcept;
    ~Impl() noexcept;

    void run() noexcept;
    void quit() noexcept;

    bool m_should_run_= false;

    std::function<void()> m_on_run_callback_;
    std::function<void()> m_on_quit_callback_;

    LayerStack m_layer_stack_;
  };
} // namespace Units