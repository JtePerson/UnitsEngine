#pragma once
#include <functional>

namespace Units {
  template<typename EventT>
  class EventListener final {
  public:
    template<typename CallableT>
    inline EventListener(CallableT&& p_callable) noexcept {
      m_callback_= p_callable;
    }
    template<typename CallableT>
    inline EventListener& operator=(CallableT&& p_callable) noexcept {
      m_callback_= p_callable;
      return *this;
    }
    inline bool operator()(const EventT& p_event) const noexcept {
      return m_callback_(p_event);
    }
  private:
    std::function<bool(const EventT&)> m_callback_;
  };
} // namespace Units