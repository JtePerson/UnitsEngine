#pragma once
#include "UnitsEngine/application.h"

#include "UnitsEngine/log.h"

namespace Units {
  namespace core {
    class Application {
    public:
      static inline Application* getInstance(const AppSpecs& p_specs= {}) noexcept {
        static Application instance{p_specs};
        return &instance;
      }
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
    };
  } // namespace core
} // namespace Units