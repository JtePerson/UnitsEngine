module;

#include <iostream>

module units.Engine;

namespace units {
  bool Engine::load(void) noexcept {
    const bool init_success= [](void) -> bool {
      std::cout << "Units-Engine Loaded" << std::endl;

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
    std::cout << "Units-Engine Unloaded" << std::endl;
    return true;
  }

  void Engine::run(void) noexcept {
    if (m_should_run_)
      return;
    m_should_run_= true;

    std::cout << "Units-Engine Running" << std::endl;

    while (m_should_run_) {
      quit();
    }
  }
  void Engine::quit(void) noexcept {
    if (!m_should_run_)
      return;

    std::cout << "Units-Engine Quitting" << std::endl;

    m_should_run_= false;
  }

  Engine* Engine::s_instance_ptr_;
} // namespace units