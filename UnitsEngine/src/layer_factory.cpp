#include "UnitsEngine/layer_factory.h"

#include "UnitsEngine/types/factory.h"
#include "UnitsEngine/ilayer.h"

namespace units {
  Factory<Id, ILayer, std::unique_ptr<ILayer>> LayerFactory::s_layer_factory;
  N LayerFactory::s_layer_types_count;

  std::unique_ptr<ILayer> LayerFactory::createLayer(const Id& p_layer_id) noexcept {
      return s_layer_factory.createType(p_layer_id);
    }
} // namespace units