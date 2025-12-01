#pragma once
#include <memory>
#include <type_traits>

#include "UnitsEngine/core/engine_api.h"
#include "UnitsEngine/types/number.h"
#include "UnitsEngine/layer_traits.h"

namespace Units {
  class UE_API IApplication {
  public:
    virtual ~IApplication() noexcept;

    virtual void onRun() noexcept= 0;
    virtual void onQuit() noexcept= 0;

    void run() noexcept;
    void quit() noexcept;

    template<typename LayerT>
    inline void attatchLayer(const I& p_layer_i) noexcept {
      attatchLayer(LayerTraits<LayerT>::id, p_layer_i);
    }
    void detatchLayer(const I& p_layer_i) noexcept;

    template<typename ApplicationT>
    static inline ApplicationT* getInstance() noexcept {
      static_assert(std::is_base_of<IApplication, ApplicationT>::value, "ApplicationT must inherit from IApplication!");
      return static_cast<ApplicationT*>(s_application_instance_);
    }
  protected:
    IApplication() noexcept;
  private:
    struct Impl;
    std::unique_ptr<Impl> m_impl_uptr_= nullptr;

    static inline IApplication* s_application_instance_= nullptr;

    void attatchLayer(const Id& p_layer_id, const I& p_layer_i) noexcept;
  };
} // namespace Units