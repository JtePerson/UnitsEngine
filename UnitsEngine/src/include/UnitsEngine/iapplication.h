#pragma once
#include <memory>
#include <type_traits>
#include <imgui/imgui.h>

#include "UnitsEngine/core/engine_api.h"
#include "UnitsEngine/types/number.h"
#include "UnitsEngine/layer_traits.h"
#include "UnitsEngine/event/event_bus.h"
#include "UnitsEngine/event/event_dispatcher.h"

namespace units {
  class UE_API IApplication {
  public:
    virtual ~IApplication() noexcept;

    virtual void onRun() noexcept= 0;
    virtual void onQuit() noexcept= 0;

    void run() noexcept;
    void quit() noexcept;

    template<typename LayerT>
    inline void attatchLayer(const I& p_layer_i) noexcept {
      attatchLayer(LayerTraits<LayerT>::id, p_layer_i);
    }
    void detatchLayer(const I& p_layer_i) noexcept;

    template<typename EventT>
    inline void pushEvent(const EventT& p_event, const EventType& p_type, const EventCategory& p_category) noexcept {
      m_event_bus_.push(p_event, p_type, p_category);
    }
    template<typename CallableT>
    inline void registerEventListener(CallableT&& p_listener) noexcept {
      m_event_dispatcher_.registerListener(std::forward<CallableT>(p_listener));
    }
    template<typename EventT>
    inline void dispatchEvent(Event& p_event, const EventT* p_data_ptr) noexcept {
      m_event_dispatcher_.dispatch(p_event, reinterpret_cast<const void*>(p_data_ptr));
    }

    inline void initImGui() noexcept {
      ImGui::SetCurrentContext(m_imgui_context_ptr);
    }

    template<typename ApplicationT>
    static inline ApplicationT* getInstance() noexcept {
      static_assert(std::is_base_of<IApplication, ApplicationT>::value, "ApplicationT must inherit from IApplication!");
      return static_cast<ApplicationT*>(s_application_instance_);
    }
  protected:
    IApplication(IApplication* p_instance) noexcept;
  private:
    friend struct Impl;
  private:
    struct Impl;
    std::unique_ptr<Impl> m_impl_uptr_= nullptr;

    static inline IApplication* s_application_instance_= nullptr;

    EventBus m_event_bus_;
    EventDispatcher m_event_dispatcher_{0};

    ImGuiContext* m_imgui_context_ptr= nullptr;

    void attatchLayer(const Id& p_layer_id, const I& p_layer_i) noexcept;
  };
} // namespace units