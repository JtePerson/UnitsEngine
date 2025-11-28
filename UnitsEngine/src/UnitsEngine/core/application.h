#pragma once
#include "UnitsEngine/core/units_engine_api.h"

int main(int p_argc, char** p_argv);

namespace Units {
  class UE_API Application {
  public:
    struct Specs {};
  public:
    static inline Application* getInstance(const Specs& p_specs= {}) noexcept {
      static inline Application s_instance{p_specs};
      return &s_instance;
    }
  private:
    friend int ::main(int p_argc, char** p_argv);
  private:
    Application(const Specs& p_specs) noexcept;
    ~Application() noexcept;
    Application(Application&&) noexcept= delete;
    Application(const Application&) noexcept= delete;
    Application operator=(Application&&) noexcept= delete;
    Application operator=(const Application&) noexcept= delete;

    void run();
    void quit();
  };
} // namespace Units