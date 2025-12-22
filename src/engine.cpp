module;

#include <iostream>

#include "UnitsEngine/core/log.hpp"
#include "UnitsEngine/events/application_events.hpp"
#include "UnitsEngine/events/window_events.hpp"

#ifdef __INTELLISENSE__
#  include "../modules/core/log.mpp"
#  include "../modules/engine.mpp"
#  include "../modules/events/events.mpp"
#  include "../modules/inputs.mpp"
#  include "../modules/layers.mpp"
#endif

module units.Engine;

import units.Log;
import units.Memory;
import units.Inputs;

namespace units {
  bool Engine::load(void) noexcept {
    const bool init_success= [](void) -> bool {
      Log::init();
      Memory::Allocator::init(65536u);

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
    Memory::Allocator::quit();
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

    while (getInstance()->m_should_run_) {
      auto layer_stack_lock= getLayerStack()->lockToScope();
      Inputs::pollInputs(getInstance()->m_event_bus_);
      Events::Event* event_ptr= nullptr;
      while (getInstance()->m_event_bus_.pollEvent(event_ptr)) {
        switch (event_ptr->type) {
          case Events::Type::ApplicationQuit: {
            UE_TRACE("Application Quit Event!");
          } break;
          case Events::Type::WindowClose: {
            UE_TRACE("Window Close Event!");
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
    }

    while (getLayerStack()->activeCount() > 0u) {
      getLayerStack()->pop();
    }
  }
  void Engine::quit(void) noexcept {
    if (!getInstance()->m_should_run_)
      return;

    Events::ApplicationQuitEvent event{};
    getInstance()->m_event_bus_.pushEvent(&event);

    getInstance()->m_should_run_= false;
  }

  Engine* Engine::s_instance_ptr_;
} // namespace units