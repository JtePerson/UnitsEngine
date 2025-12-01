#pragma once
#include <memory>

#include "UnitsEngine/core/engine_api.h"
#include "UnitsEngine/types/number.h"
#include "UnitsEngine/types/factory.h"
#include "UnitsEngine/ilayer.h"

namespace Units {
  class LayerFactory final {
  public:
    static inline std::unique_ptr<ILayer> createLayer(const Id& p_layer_id) noexcept {
      return s_layer_factory.createType(p_layer_id);
    }
  private:
    template<typename LayerT>
    friend struct LayerTraits;
  private:
    inline LayerFactory() noexcept= default;
    
    static Factory<Id, ILayer, std::unique_ptr<ILayer>> UE_API s_layer_factory;
    static N UE_API s_layer_types_count;
    template<typename LayerT>
    static inline I registerType() noexcept {
      const Id layer_id= s_layer_types_count++;
      s_layer_factory.registerType<LayerT>(layer_id);
      return layer_id;
    }
  };
} // namespace Units