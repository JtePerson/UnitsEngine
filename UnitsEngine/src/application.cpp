#include "application.h"

#include <SDL3/SDL.h>

#include "UnitsEngine/core/log.h"
#include "UnitsEngine/event/event_type.h"
#include "UnitsEngine/event/event_category.h"
#include "UnitsEngine/event/application_event.h"

namespace units {
  IApplication::Impl::Impl() noexcept {
    UE_CORE_WARN("Initializing Application");
    UE_CORE_INFO("Application Initialized");
  }
  IApplication::Impl::~Impl() noexcept {
    UE_CORE_WARN("Quitting Application");
    UE_CORE_INFO("Application Quit");
  }

  void IApplication::Impl::run() noexcept {
    if (m_should_run_) { return; }
    m_should_run_= true;

    m_on_run_callback_();
    while (m_should_run_) {
      m_layer_stack_.processLayerQueue();
      {
        SDL_Event sdl_event;
        SDL_zero(sdl_event);
        while (SDL_PollEvent(&sdl_event)) {
          if (sdl_event.type == SDL_EVENT_QUIT) {
            quit();
            break;
          }
        }
        Event event;
        const void* data_ptr;
        while (m_application_ptr_->m_event_bus_.pollEvents(event, data_ptr)) {
          m_application_ptr_->m_event_dispatcher_.dispatch(event, data_ptr);
        }
      }
      m_layer_stack_.forEachLayer([](std::unique_ptr<ILayer>& p_layer_uptr){
        p_layer_uptr->onTick();
      });
      quit();
    }
    m_layer_stack_.detatchAllLayers();
    m_on_quit_callback_();
  }
  void IApplication::Impl::quit() noexcept {
    UE_CORE_WARN("Attempt made to quit Application");
    if (!m_should_run_) { return; }
    m_should_run_= false;
    m_application_ptr_->m_event_bus_.push(ApplicationQuitEvent{}, kUE_EventTypeApplicationQuit, UE_EVENTCATEGORY_NONE);
  }
} // namespace units