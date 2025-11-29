#pragma once
#include "UnitsEngine/event/event_type.h"
#include "UnitsEngine/event/event.h"

namespace Units {
  class ApplicationQuitEvent final : public IEvent {
  public:
    inline ApplicationQuitEvent() noexcept= default;
    virtual inline ~ApplicationQuitEvent() noexcept override= default;
    UE_EVENT_TYPE(EventType::kApplicationQuit);
  private:
  };
} // namespace Units