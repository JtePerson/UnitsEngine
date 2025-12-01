#include "UnitsEngine/layer_factory.h"

#include "UnitsEngine/types/factory.h"

namespace Units {
  Factory<Id, ILayer, std::unique_ptr<ILayer>> LayerFactory::s_layer_factory;
  N LayerFactory::s_layer_types_count;
} // namespace Units