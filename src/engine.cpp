module;

#include <iostream>

module units.Engine;

import units.Log;

namespace units {
  bool Engine::load(void) noexcept {
    const bool init_success= [](void) -> bool {
      Log::init();
      Log::Core::engineLogger()->trace("Units-Engine Loaded");

      s_instance_ptr_= [](void) -> Engine* {
        static Engine instance{};
        return &instance;
      }();

      return s_instance_ptr_ != nullptr;
    }();
    return init_success;
  }
  bool Engine::unload(void) noexcept {
    if (!loaded() || getInstance()->m_should_run_)
      return false;
    Log::Core::engineLogger()->trace("Units-Engine Unloaded");
    Log::quit();
    return true;
  }

  Engine::Engine(void) noexcept {
  }
  Engine::~Engine(void) noexcept {
  }

  void Engine::run(void) noexcept {
    if (m_should_run_)
      return;
    m_should_run_= true;

    Log::Core::engineLogger()->trace("Units-Engine Running");

    while (m_should_run_) {
      quit();
    }
  }
  void Engine::quit(void) noexcept {
    if (!m_should_run_)
      return;

    Log::Core::engineLogger()->trace("Units-Engine Quitting");

    m_should_run_= false;
  }

  Engine* Engine::s_instance_ptr_;
} // namespace units