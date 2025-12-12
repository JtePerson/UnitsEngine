#pragma once
#include "UnitsEngine/events.h"

namespace units {
  class Inputs final {
   public:
    static void getInputs(Events::EventDispatcher* p_event_dispatcher_ptr) noexcept;

   private:
    Inputs()= delete;
    ~Inputs()= delete;
  };
} // namespace units