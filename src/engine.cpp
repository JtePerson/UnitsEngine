module;

#include <iostream>

#include "UnitsEngine/events/application_events.hpp"
#include "UnitsEngine/events/window_events.hpp"

#ifdef __INTELLISENSE__
#  include "../modules/core/log.mpp"
#  include "../modules/engine.mpp"
#  include "../modules/events/events.mpp"
#  include "../modules/layers.mpp"
#endif

module units.Engine;

import units.Log;
import units.Memory;

namespace units {
  bool Engine::load(void) noexcept {
    const bool init_success= [](void) -> bool {
      Log::init();
      Memory::Allocator::init(65536u);

      s_instance_ptr_= [](void) -> Engine* {
        static Engine instance{};
        return &instance;
      }();

      if (s_instance_ptr_ != nullptr)
        Log::Core::engineLogger()->trace("Loaded");
      return s_instance_ptr_ != nullptr;
    }();
    return init_success;
  }
  bool Engine::unload(void) noexcept {
    if (!loaded() || getInstance()->m_should_run_)
      return false;
    Memory::Allocator::quit();
    Log::Core::engineLogger()->trace("Unloaded");
    Log::quit();
    return true;
  }

  Engine::Engine(void) noexcept: m_event_bus_(Memory::Allocator::request(1024u).ptr, 1024u) {
  }
  Engine::~Engine(void) noexcept {
  }

  void Engine::run(void) noexcept {
    if (getInstance()->m_should_run_)
      return;
    getInstance()->m_should_run_= true;

    Log::Core::engineLogger()->trace("Running");

    while (getInstance()->m_should_run_) {
      auto layer_stack_lock= getLayerStack()->lockToScope();
      Events::Event* event_ptr= nullptr;
      while (getInstance()->m_event_bus_.pollEvent(event_ptr)) {
        switch (event_ptr->type) {
          case Events::Type::ApplicationQuit: {
            Log::Core::engineLogger()->trace("Application Quit Event!");
          } break;
          case Events::Type::WindowClose: {
            Log::Core::engineLogger()->trace("Window Close Event!");
          } break;
          default: {
          } break;
        }
        getLayerStack()->forEach([&](Layer& p_layer) -> bool {
          return p_layer.onEvent(event_ptr);
        });
      }
      getLayerStack()->forEach([&](Layer& p_layer) -> bool {
        return p_layer.onTick();
      });
      getLayerStack()->forEach([&](Layer& p_layer) -> bool {
        return p_layer.onRender();
      });
      quit();
    }
  }
  void Engine::quit(void) noexcept {
    if (!getInstance()->m_should_run_)
      return;
    Log::Core::engineLogger()->trace("Quitting");

    Events::ApplicationQuitEvent event{};
    getInstance()->m_event_bus_.pushEvent(&event);

    getInstance()->m_should_run_= false;
  }

  Engine* Engine::s_instance_ptr_;
} // namespace units