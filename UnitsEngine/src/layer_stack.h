#pragma once
#include <queue>
#include <tuple>
#include <functional>

#include "UnitsEngine/types/number.h"
#include "UnitsEngine/ilayer.h"
#include "UnitsEngine/layer_factory.h"

namespace units {
  class LayerStack final {
  public:
    inline LayerStack() noexcept= default;
    inline ~LayerStack() noexcept= default;
    
    inline void attatchLayer(const Id& p_layer_id, const I& p_layer_i) noexcept {
      m_layer_queue_.emplace(std::make_tuple(p_layer_id, p_layer_i, 1));
    }
    inline ILayer* getLayer(const I& p_layer_i) noexcept {
      if (p_layer_i >= m_layer_vector_.size()) {
        return nullptr;
      }
      return m_layer_vector_[p_layer_i].get();
    }
    inline void detatchLayer(const I& p_layer_i) noexcept {
      m_layer_queue_.emplace(std::make_tuple(-1, p_layer_i, -1));
    }
    
    inline void processLayerQueue() noexcept {
      while (!m_layer_queue_.empty()) {
        auto& layer_tuple= m_layer_queue_.front();
        if (std::get<Operation>(layer_tuple) > 0) {
          attatchLayerToStack(std::get<LayerId>(layer_tuple), std::get<LayerI>(layer_tuple));
        } else if (std::get<Operation>(layer_tuple) < 0) {
          detatchLayerFromStack(std::get<LayerI>(layer_tuple));
        }
        m_layer_queue_.pop();
      }
    }
    inline void detatchAllLayers() noexcept {
      for (auto& layer : m_layer_vector_) {
        if (layer != nullptr) {
          layer->onDetatch();
        }
      }
      m_layer_vector_.clear();
    }

    inline void forEachLayer(std::function<void(std::unique_ptr<ILayer>&)>&& p_callable) noexcept {
      for (auto layer_it= m_layer_vector_.begin(); layer_it != m_layer_vector_.end(); layer_it++) {
        if (*layer_it != nullptr) {
          p_callable(*layer_it);
        }
      }
    }
    inline void forEachLayerReverse(std::function<void(std::unique_ptr<ILayer>&)>&& p_callable) noexcept {
      for (auto layer_it= m_layer_vector_.rbegin(); layer_it != m_layer_vector_.rend(); layer_it++) {
        if (*layer_it != nullptr) {
          p_callable(*layer_it);
        }
      }
    }
  private:
    enum TupleTypes : I {
      LayerId= 0,
      LayerI= 1,
      Operation= 2
    };
    std::queue<std::tuple<Id, I, int>> m_layer_queue_;
    std::vector<std::unique_ptr<ILayer>> m_layer_vector_;
    
    inline void attatchLayerToStack(const Id& p_layer_id, const I& p_layer_i) noexcept {
      if (p_layer_i >= m_layer_vector_.size()) {
        m_layer_vector_.resize(p_layer_i + 1);
      } else {
        detatchLayerFromStack(p_layer_i);
      }
      m_layer_vector_[p_layer_i]= LayerFactory::createLayer(p_layer_id);
      m_layer_vector_[p_layer_i]->onAttatch();
    }
    inline void detatchLayerFromStack(const I& p_layer_i) noexcept {
      if (p_layer_i >= m_layer_vector_.size()) { return; }
      if (m_layer_vector_[p_layer_i] == nullptr) { return; }
      m_layer_vector_[p_layer_i]->onDetatch();
      m_layer_vector_[p_layer_i].reset();
    }
  };
} // namespace units