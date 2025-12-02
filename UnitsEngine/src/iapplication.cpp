#include "UnitsEngine/iapplication.h"
#include "application.h"

#include "UnitsEngine/core/macros.h"

namespace units {
  IApplication::IApplication() noexcept {
    if (s_application_instance_ != nullptr) { return; }
    m_impl_uptr_= std::make_unique<Impl>();
    m_impl_uptr_->m_application_ptr_= this;
    m_impl_uptr_->m_on_run_callback_= UE_BIND_FUNCTION(onRun);
    m_impl_uptr_->m_on_quit_callback_= UE_BIND_FUNCTION(onQuit);
  }
  IApplication::~IApplication() noexcept {
    m_impl_uptr_.reset();
  }

  void IApplication::run() noexcept {
    m_impl_uptr_->run();
  }
  void IApplication::quit() noexcept {
    m_impl_uptr_->quit();
  }

  void IApplication::attatchLayer(const Id& p_layer_id, const I& p_layer_i) noexcept {
    m_impl_uptr_->m_layer_stack_.attatchLayer(p_layer_id, p_layer_i);
  }
  void IApplication::detatchLayer(const I& p_layer_i) noexcept {
    m_impl_uptr_->m_layer_stack_.detatchLayer(p_layer_i);
  }
} // namespace units