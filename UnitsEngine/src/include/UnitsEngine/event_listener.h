#pragma once
#include <functional>

namespace Units {
  template<typename EventT>
  class EventListener final {
  public:
    template<typename Callable>
    inline EventListener(Callable&& p_callable) noexcept {
      m_callback_= p_callable;
    }
    template<typename Callable>
    inline EventListener& operator=(Callable&& p_callable) noexcept {
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