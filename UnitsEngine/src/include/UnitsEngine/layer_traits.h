#pragma once
#include "UnitsEngine/types/number.h"
#include "UnitsEngine/layer_factory.h"

namespace Units {
  template<typename LayerT>
  struct LayerTraits final {
    static inline const Id id= LayerFactory::registerType<LayerT>();
  };
} // namespace Units