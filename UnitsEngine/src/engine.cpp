#include "UnitsEngine/engine.h"

#include "UnitsEngine/application_events.h"
#include "UnitsEngine/inputs.h"

namespace units {
  Engine* Engine::s_instance_ptr_= nullptr;

  bool Engine::load() noexcept {
    static Engine instance{};
    if (s_instance_ptr_ != nullptr)
      return false;
    s_instance_ptr_= &instance;

    return true;
  }
  void Engine::unload() noexcept {
  }

  Engine::Engine() noexcept {
  }
  Engine::~Engine() noexcept {
  }

  void Engine::run() noexcept {
    if (s_instance_ptr_->m_should_run_)
      return;
    s_instance_ptr_->m_should_run_= true;

    while (s_instance_ptr_->m_should_run_) {
      quit();
      Inputs::getInputs(getEventDispatcher());
      Events::Event event;
      const void* event_data_ptr= nullptr;
      while (s_instance_ptr_->m_event_bus_.pollEvents(&event, event_data_ptr)) {
        getEventDispatcher()->dispatch(&event, event_data_ptr);
      }
    }
  }
  void Engine::quit() noexcept {
    if (!s_instance_ptr_->m_should_run_)
      return;
    const Events::ApplicationQuitEvent event{};
    s_instance_ptr_->m_event_bus_.pushEvent(&event);
    s_instance_ptr_->m_should_run_= false;
  }
} // namespace units