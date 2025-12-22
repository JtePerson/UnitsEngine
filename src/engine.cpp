module;

#include <iostream>

module units.Engine;

extern "C" namespace units {
  void Engine::init(void) noexcept {
    std::cout << "Units-Engine Initialized" << std::endl;
  }
  void Engine::quit(void) noexcept {
    std::cout << "Units-Engine Quit" << std::endl;
  }
} // namespace units