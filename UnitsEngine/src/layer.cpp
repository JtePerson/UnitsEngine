#include "UnitsEngine/layer.h"

#include <memory>

namespace Units {
  Factory<Id, ILayer, std::unique_ptr<ILayer>> ILayer::s_factory_;
  std::unique_ptr<ILayer> ILayer::createLayer(const Id& p_layer_id) noexcept {
    return s_factory_.createType(p_layer_id);
  }
  Id ILayer::registerLayer() noexcept {
    static Id layer_count= 0;
    return layer_count++;
  }
} // namespace Units