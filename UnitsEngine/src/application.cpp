#include "application.h"

#include "UnitsEngine/core/log.h"

namespace Units {
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
  }
} // namespace Units