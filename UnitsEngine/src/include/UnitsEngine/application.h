#pragma once
#include <memory>
#include <type_traits>

#include "UnitsEngine/engine_api.h"
#include "UnitsEngine/app_specs.h"
#include "UnitsEngine/layer.h"
#include "UnitsEngine/event/event.h"

namespace Units {
  // Interface class for Application
  class UE_API IApplication {
  public:
    virtual ~IApplication() noexcept;
    // Get Singleton Instance
    template<typename ApplicationType= IApplication>
    static inline ApplicationType* getInstance() noexcept {
      static_assert((std::is_base_of<IApplication, ApplicationType>::value && "ApplicationType must derive from IApplication!"));
      return static_cast<ApplicationType*>(s_instance_ptr_);
    }

    // Attatches Layer to Layer Stack
    void attatchLayer(const Id& p_layer_id, const I& p_i) noexcept;
    template<typename LayerT>
    inline void attatchLayer(const I& p_i) noexcept {
      attatchLayer(LayerTraits<LayerT>::id, p_i);
    }
    // Detatches Layer from Layer Stack
    void detatchLayer(const Id& p_layer_id, const I& p_i) noexcept;
    template<typename LayerT>
    inline void detatchLayer(const I& p_i) noexcept {
      detatchLayer(LayerTraits<LayerT>::id, p_i);
    }

    // Runs Application
    void run() const noexcept;
    // Attempts to Quit Application
    void quit() const noexcept;

    virtual void onEvent(IEvent& p_event) noexcept= 0;
    virtual void onTick() noexcept= 0;
  protected:
    IApplication(IApplication* p_derived_ptr, AppSpecs&& p_specs) noexcept;
    static inline IApplication* s_instance_ptr_= nullptr;
  };

  // Defined in Client
  extern IApplication* createApplication() noexcept;
} // namespace Units