#include "application.h"

#include <iostream>

#include <UnitsEngine/core/macros.h>
#include <UnitsEngine/engine.h>

namespace manager {
  Application::Application() noexcept {
    units::Engine::load();
  }
  Application::~Application() noexcept {
    units::Engine::unload();
  }

  void Application::run() noexcept {
    units::Engine::getEventDispatcher()->registerListener<units::Events::ApplicationQuitEvent>(UE_BIND_FUNCTION(onApplicationQuit));
    units::Engine::run();
  }

  bool Application::onApplicationQuit(units::Events::ApplicationQuitEvent& p_event) {
    std::printf("Application Quit!\n");
    return false;
  }
} // namespace manager