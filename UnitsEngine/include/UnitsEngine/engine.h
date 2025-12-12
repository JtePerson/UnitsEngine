#pragma once
#include "UnitsEngine/core/engine_api.h"
#include "UnitsEngine/events.h"

namespace units {
  class UE_API Engine final {
   public:
    static bool load() noexcept;
    static void unload() noexcept;

    static void run() noexcept;
    static void quit() noexcept;

    static inline Engine* getInstance() noexcept { return s_instance_ptr_; }
    static inline Events::EventDispatcher* getEventDispatcher() noexcept { return &s_instance_ptr_->m_event_dispatcher_; }

   private:
    Engine() noexcept;
    ~Engine() noexcept;

    static Engine* s_instance_ptr_;

    bool m_should_run_= false;

    Events::EventBus m_event_bus_{};
    Events::EventDispatcher m_event_dispatcher_{};
  };
} // namespace units