#include "layer_stack.h"

#include <tuple>

namespace Units {
  namespace core {
    void LayerStack::processLayerQueue() noexcept {
      while (!m_layer_queue_.empty()) {
        auto& layer_tuple= m_layer_queue_.front();
        if (std::get<int>(layer_tuple) > 0) {
          const auto& layer_it= m_layer_vector_.emplace(m_layer_vector_.begin() + std::get<1>(layer_tuple), ILayer::createLayer(std::get<0>(layer_tuple)));
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

    void LayerStack::processLayerEvents(IEvent& p_event) noexcept {
      for (auto& layer : m_layer_vector_) {
        if (p_event.handled()) {
          break;
        }
        layer->onEvent(p_event);
      }
    }
    void LayerStack::processLayerTick() noexcept {
      for (auto& layer : m_layer_vector_) {
        if (!layer->onTick()) {
          break;
        }
      }
    }
    void LayerStack::processLayerImGui() noexcept {
      for (auto& layer : m_layer_vector_) {
        if (!layer->onImGui()) {
          break;
        }
      }
    }
  } // namespace core
} // namespace Units