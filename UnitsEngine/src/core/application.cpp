#include "UnitsEngine/application.h"
#include "core/application.h"

#include "UnitsEngine/log.h"

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
        quit();
      }
      m_layer_stack_.detatchAllLayers();
      UE_CORE_INFO("Application Ran");
    }
  } // namespace core
} // namespace Units