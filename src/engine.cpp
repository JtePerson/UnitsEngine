module;

#include "UnitsEngine/core/log.hpp"
#include "UnitsEngine/events/application_events.hpp"
#include "UnitsEngine/events/window_events.hpp"

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
      Events::Event* event_ptr= nullptr;
      while (getInstance()->m_event_bus_.pollEvent(event_ptr)) {
        switch (event_ptr->type) {
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