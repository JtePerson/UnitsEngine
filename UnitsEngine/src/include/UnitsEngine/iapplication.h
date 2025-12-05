#pragma once
#include <memory>
#include <type_traits>
#include <imgui/imgui.h>

#include "UnitsEngine/core/engine_api.h"
#include "UnitsEngine/types/number.h"
#include "UnitsEngine/layer_traits.h"
#include "UnitsEngine/event/event_bus.h"
#include "UnitsEngine/event/event_dispatcher.h"
#include "UnitsEngine/window/window.h"
#include "UnitsEngine/gpu/gpu_device.h"
#include "UnitsEngine/gpu/gpu_command_buffer.h"
#include "UnitsEngine/gpu/gpu_render_pass.h"

namespace units {
  class UE_API IApplication {
  public:
    virtual ~IApplication() noexcept;

    Window m_window_;
    GPUDevice m_gpu_device_;

    virtual void onRun() noexcept= 0;
    virtual void onQuit() noexcept= 0;

    void run() noexcept;
    void quit() noexcept;

    template<typename LayerT>
    inline void attatchLayer(const I& p_layer_i) noexcept {
      attatchLayer(LayerTraits<LayerT>::id, p_layer_i);
    }
    template<typename LayerT>
    inline LayerT* getLayer(const I& p_layer_i) noexcept {
      static_assert(std::is_base_of<ILayer, LayerT>::value, "LayerT must inherit from ILayer!");
      return static_cast<LayerT*>(getLayer(p_layer_i));
    }
    void detatchLayer(const I& p_layer_i) noexcept;

    template<typename EventT>
    inline void pushEvent(const EventT& p_event) noexcept {
      m_event_bus_.push(p_event);
    }
    template<typename CallableT>
    inline void registerEventListener(CallableT&& p_listener) noexcept {
      m_event_dispatcher_.registerListener(std::forward<CallableT>(p_listener));
    }
    template<typename EventT>
    inline void dispatchEvent(Event& p_event, const EventT* p_data_ptr) noexcept {
      m_event_dispatcher_.dispatch(p_event, reinterpret_cast<const void*>(p_data_ptr));
    }

    inline void initImGui(Window& p_window, GPUDevice&p_gpu_device) noexcept {
      IMGUI_CHECKVERSION();
      m_imgui_context_ptr_= ImGui::CreateContext();
      ImGuiIO& io= ImGui::GetIO(); (void)io;
      io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;

      ImGui::StyleColorsDark();

      initImGuiBackend(p_window, p_gpu_device);
    }
    void quitImGui() noexcept;
    void prepareImGuiDrawData(GPUCommandBuffer& p_gpu_command_buffer) noexcept;
    void renderImGuiDrawData(GPUCommandBuffer& p_gpu_command_buffer, GPURenderPass& p_gpu_render_pass) noexcept;


    template<typename ApplicationT= IApplication>
    static inline ApplicationT* getInstance() noexcept {
      static_assert(std::is_base_of<IApplication, ApplicationT>::value, "ApplicationT must inherit from IApplication!");
      return static_cast<ApplicationT*>(s_application_instance_);
    }
  protected:
    IApplication(IApplication* p_instance) noexcept;

    void processLayerQueue() noexcept;
  private:
    friend struct Impl;
    friend class ILayer;
  private:
    struct Impl;
    std::unique_ptr<Impl> m_impl_uptr_= nullptr;

    static inline IApplication* s_application_instance_= nullptr;

    EventBus m_event_bus_;
    EventDispatcher m_event_dispatcher_;

    ImGuiContext* m_imgui_context_ptr_= nullptr;

    ImDrawData* m_imgui_draw_data_ptr_= nullptr;

    void attatchLayer(const Id& p_layer_id, const I& p_layer_i) noexcept;
    ILayer* getLayer(const I& p_layer_i) noexcept;

    void initImGuiBackend(Window& p_window, GPUDevice& p_gpu_device) noexcept;
  };
} // namespace units