#pragma once
#include <memory>

#include "UnitsEngine/core/engine_api.h"
#include "UnitsEngine/types/number.h"
#include "UnitsEngine/types/factory.h"
#include "UnitsEngine/event/event.h"

namespace Units {
  class ILayer {
  public:
    // Destructor should not access anything outside of ILayer
    virtual inline ~ILayer() noexcept= default;
    // Called when layer attatched to stack
    // Can access outside content
    virtual void onAttatch() noexcept= 0;
    // Called when layer detatched from stack
    // Can access outside content
    virtual void onDetatch() noexcept= 0;
    // Called when Layer recieves Event
    virtual void onEvent(IEvent& p_event) noexcept= 0;
    // Called when Layer gets ticked
    // Return false to prevent tick from propagating through layers
    virtual bool onTick() noexcept= 0;
  protected:
    // Constructor should not access anything outside of ILayer
    inline ILayer() noexcept= default;
  public:
    static std::unique_ptr<ILayer> UE_API createLayer(const Id& p_layer_id) noexcept;
    template<typename LayerT>
    static inline Id registerLayer() noexcept {
      const Id layer_id= registerLayer();
      s_factory_.registerType<LayerT>(layer_id);
      return layer_id;
    }
  private:
    static Factory<Id, ILayer, std::unique_ptr<ILayer>> UE_API s_factory_;
    
    static Id UE_API registerLayer() noexcept;
  };
  template<typename LayerT>
  struct LayerTraits {
    static inline const Id id= ILayer::registerLayer<LayerT>();
  };
} // namespace Units