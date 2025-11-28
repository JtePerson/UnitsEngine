#pragma once
#include "UnitsEngine/core/units_engine_api.h"

int main(int p_argc, char** p_argv);

namespace Units {
  class UE_API Application;
  // Defined in Client
  extern Application* createApplication() noexcept;

  class UE_API Application {
  public:
    struct Specs {};
  public:
    static inline Application* getInstance() noexcept {
      static Application* s_instance_ptr= createApplication();
      return s_instance_ptr;
    }
  protected:
    Application(const Specs& p_specs) noexcept;
    ~Application() noexcept;
    Application(Application&&) noexcept= delete;
    Application(const Application&) noexcept= delete;
    Application operator=(Application&&) noexcept= delete;
    Application operator=(const Application&) noexcept= delete;
  private:
    friend int ::main(int p_argc, char** p_argv);
  private:
    bool should_run_= false;

    void run();
    void quit() noexcept;
  };
} // namespace Units