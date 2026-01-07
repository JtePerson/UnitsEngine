module;

#include "UnitsEngine/core/macros.hpp"

module units.Layers;

namespace units {
  void LayerStack::pop() noexcept {
    if (m_next_top_layer_ > m_top_layer_)
      m_next_top_layer_= m_top_layer_;

    --m_next_top_layer_;

    if (!m_locked_) {
      m_stack_[m_top_layer_]->onDetach();
      m_stack_.resize(m_next_top_layer_ + 1u);
      m_top_layer_= m_next_top_layer_;
    }
  }
} // namespace units