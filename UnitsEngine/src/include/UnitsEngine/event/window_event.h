#pragma once
#include "UnitsEngine/event/event.h"

#include <string>

#include "UnitsEngine/types/number.h"

namespace Units {
  class WindowCloseEvent final : public IEvent {
  public:
    inline WindowCloseEvent(std::string&& p_window_title, Id&& p_window_id) noexcept
    : m_window_title_(p_window_title), m_window_id_(p_window_id)
    {}
    virtual inline ~WindowCloseEvent() noexcept override= default;
    UE_EVENT_TYPE(EventType::kWindowClose)

    inline const std::string& getWindowTitle() const noexcept { return m_window_title_; }
    inline Id getWindowId() const noexcept { return m_window_id_; }
  private:
    const std::string m_window_title_;
    const Id m_window_id_;
  };
} // namespace Units