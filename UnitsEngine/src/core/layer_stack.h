#pragma once
#include <memory>
#include <vector>
#include <queue>
#include <tuple>

#include "UnitsEngine/layer.h"
#include "UnitsEngine/types/number.h"

namespace Units {
  namespace core {
    class LayerStack final {
    public:
      inline LayerStack() noexcept {}
      inline ~LayerStack() noexcept= default;

      inline void attatchLayer(const Id& p_layer_id, const I& p_i) noexcept {
        m_layer_queue_.emplace(std::make_tuple(p_layer_id, p_i,  1));
      }
      inline void detatchLayer(const Id& p_layer_id, const I& p_i) noexcept {
        m_layer_queue_.emplace(std::make_tuple(p_layer_id, p_i, -1));
      }

      void processLayerQueue() noexcept;
      void detatchAllLayers() noexcept;
    private:
      std::queue<std::tuple<Id, I, int>> m_layer_queue_;
      std::vector<std::unique_ptr<ILayer>> m_layer_vector_;
    };
  } // namespace core
} // namespace Units