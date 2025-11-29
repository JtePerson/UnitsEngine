#pragma once
#include "UnitsEngine/application.h"

#include "UnitsEngine/log.h"
#include "core/layer_stack.h"

namespace Units {
  namespace core {
    class Application {
    public:
      static inline Application* getInstance(const AppSpecs& p_specs= {}) noexcept {
        static Application instance{p_specs};
        return &instance;
      }

      void attatchLayer(const Id& p_layer_id, const I& p_i) noexcept;
      void detatchLayer(const Id& p_layer_id, const I& p_i) noexcept;

      void run();
      inline void quit() noexcept {
        if (!m_should_run_) { return; }
        UE_CORE_WARN("Attempt made to quit Application");
        m_should_run_= false;
      }
    private:
      Application(const AppSpecs& p_specs) noexcept;
      ~Application() noexcept;

      bool m_should_run_= false;

      LayerStack m_layer_stack_;
    };
  } // namespace core
} // namespace Units