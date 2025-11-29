#include "core/layer_stack.h"

#include <tuple>

namespace Units {
  namespace core {
    void LayerStack::processLayerQueue() noexcept {
      while (!m_layer_queue_.empty()) {
        auto& layer_tuple= m_layer_queue_.front();
        if (std::get<int>(layer_tuple) > 0) {
          const auto& layer_it= m_layer_vector_.emplace(m_layer_vector_.begin() + std::get<0>(layer_tuple), ILayer::createLayer(std::get<1>(layer_tuple)));
          layer_it->get()->onAttatch();
        } else if (std::get<int>(layer_tuple) < 0) {
          m_layer_vector_.erase(m_layer_vector_.begin() + std::get<1>(layer_tuple))->get()->onDetatch();
        }
        m_layer_queue_.pop();
      }
    }
    void LayerStack::detatchAllLayers() noexcept {
      for (auto& layer : m_layer_vector_) {
        layer->onDetatch();
      }
      m_layer_vector_.clear();
    }
  } // namespace core
} // namespace Units