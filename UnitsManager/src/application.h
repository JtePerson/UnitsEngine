#pragma once
#include <UnitsEngine/application_events.h>

namespace manager {
  class Application final {
   public:
    Application() noexcept;
    ~Application() noexcept;

    void run() noexcept;
    bool onApplicationQuit(units::Events::ApplicationQuitEvent& p_event);

   private:
  };
} // namespace manager
