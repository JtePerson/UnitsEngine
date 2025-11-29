#include "UnitsEngine/application.h"
#include "application.h"

#include <SDL3/SDL.h>

#include "UnitsEngine/core/log.h"
#include "UnitsEngine/core/assert.h"
#include "UnitsEngine/app_specs.h"
#include "UnitsEngine/event/event.h"
#include "UnitsEngine/gpu/gpu_device.h"
#include "UnitsEngine/gpu/gpu_command_buffer.h"
#include "UnitsEngine/gpu/gpu_render_pass.h"

namespace Units {
  IApplication::IApplication(IApplication* p_derived_ptr, AppSpecs&& p_specs) noexcept {
    core::Application::getInstance(p_specs);
    if (s_instance_ptr_ != nullptr) { return; }
    s_instance_ptr_= p_derived_ptr;
  }

  void IApplication::attatchLayer(const Id& p_layer_id, const I& p_i) noexcept {
    core::Application::getInstance()->attatchLayer(p_layer_id, p_i);
  }
  void IApplication::detatchLayer(const Id& p_layer_id, const I& p_i) noexcept {
    core::Application::getInstance()->detatchLayer(p_layer_id, p_i);
  }

  IApplication::~IApplication() noexcept {}
  void IApplication::run() const noexcept {
    core::Application::getInstance()->run();
  }
  void IApplication::quit() const noexcept {
    core::Application::getInstance()->quit();
  }

  namespace core {
    Application::Application(const AppSpecs& p_specs) noexcept {
      UE_CORE_WARN("Initializing Application");
      if (!SDL_Init(SDL_INIT_VIDEO)) {
        UE_CORE_CRITICAL("Could not Initialize SDL! error: {0}", SDL_GetError());
        UE_CORE_ASSERT(false, "SDL not initialized!");
      }
      initSDLEventCallbacks();
      UE_CORE_INFO("Application Initialized");
    }
    Application::~Application() noexcept {
      UE_CORE_WARN("Quitting Application");
      UE_CORE_INFO("Application Quit");
    }

    void Application::attatchLayer(const Id& p_layer_id, const I& p_i) noexcept {
      m_layer_stack_.attatchLayer(p_layer_id, p_i);
    }
    void Application::detatchLayer(const Id& p_layer_id, const I& p_i) noexcept {
      m_layer_stack_.detatchLayer(p_layer_id, p_i);
    }

    void Application::run() {
      if (m_should_run_) { UE_CORE_WARN("Application Already Running!"); return; }
      m_should_run_= true;

      UE_CORE_WARN("Running Application");
      while (m_should_run_) {
        // Run Application
        m_layer_stack_.processLayerQueue();

        while (SDL_PollEvent(&m_sdl_event_)) {
          auto current_event= sdlEventCallback(m_sdl_event_);
          if (current_event->getId() != static_cast<EventId>(EventType::kNone)) {
            if (onEvent(*current_event)) { break; }
          }
        }
        if (!m_should_run_) { break; }

        IApplication::getInstance()->onTick();
        m_layer_stack_.processLayerTick();
      }
      m_layer_stack_.detatchAllLayers();
      UE_CORE_INFO("Application Ran");
    }

    void Application::initSDLEventCallbacks() noexcept {
      registerSDLEventCallback(SDL_EVENT_QUIT, [this](const SDL_Event& p_event){
        return std::make_unique<ApplicationQuitEvent>();
      });
      registerSDLEventCallback(SDL_EVENT_WINDOW_CLOSE_REQUESTED, [this](const SDL_Event& p_event){
        return std::make_unique<WindowCloseEvent>(SDL_GetWindowTitle(SDL_GetWindowFromEvent(&p_event)), p_event.window.windowID);
      });
    }

    bool Application::onEvent(IEvent& p_event) noexcept {
      EventDispatcher event_dispatcher{p_event};
      if (event_dispatcher.dispatch<ApplicationQuitEvent>(UE_BIND_FUNCTION(Application::onApplicationQuit))) { return true; }
      event_dispatcher.dispatch<WindowCloseEvent>(UE_BIND_FUNCTION(Application::onWindowClose));

      IApplication::getInstance()->onEvent(p_event);
      if (!p_event.handled()) {
        m_layer_stack_.processLayerEvents(p_event);
      }
      
      return false;
    }
  } // namespace core
} // namespace Units