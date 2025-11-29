#pragma once
#include <functional>
#include <utility>

namespace Units {
  template<typename EventT>
  class EventListener final {
  public:
    template<typename CallableT>
    inline EventListener(CallableT&& p_callable) noexcept
    : m_callback_(std::forward<CallableT>(p_callable))
    {}
    inline bool operator()(EventT& p_event) const noexcept {
      return m_callback_(p_event);
    }
  private:
    std::function<bool(EventT&)> m_callback_;
  };
} // namespace Units