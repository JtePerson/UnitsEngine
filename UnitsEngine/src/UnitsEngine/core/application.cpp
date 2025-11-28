#include "UnitsEngine/core/application.h"
#include "UnitsEngine/core/log.h"

namespace Units {
  Application::Application(const Specs& p_specs) noexcept {
    UE_CORE_WARN("Initializing Application");
    UE_CORE_INFO("Application Initialized");
  }
  Application::~Application() noexcept {
    UE_CORE_WARN("Deinitializing Application");
    UE_CORE_INFO("Application Deinitialized");
  }

  void Application::run() {
    if (should_run_) {
      UE_CORE_ERROR("Application already running!");
      return;
    }
    should_run_= true;
    UE_CORE_WARN("Running Application");
    while (should_run_) {
      // Run application
    }
    UE_CORE_INFO("Application Ran");
  }
  void Application::quit() noexcept {
    UE_CORE_WARN("Attempt made to Quit Application");
    should_run_= false;
  }
} // namespace Units