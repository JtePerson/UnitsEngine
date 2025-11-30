#pragma once
#include "UnitsEngine/application.h"

#include <SDL3/SDL.h>
#include <unordered_map>
#include <memory>
#include <imgui/imgui.h>

#include "UnitsEngine/types/number.h"
#include "UnitsEngine/core/log.h"
#include "layer_stack.h"
#include "UnitsEngine/event/event.h"
#include "window/window.h"
#include "UnitsEngine/gpu/gpu_device.h"
#include "UnitsEngine/gpu/gpu_command_buffer.h"
#include "UnitsEngine/gpu/gpu_render_pass.h"

namespace Units {
  namespace core {
    class Application {
    public:
      static inline Application* getInstance(const AppSpecs& p_specs= {}) noexcept {
        static Application instance{p_specs};
        return &instance;
      }

      void attatchLayer(const Id& p_layer_id, const I& p_i) noexcept;
      void detatchLayer(const Id& p_layer_id, const I& p_i) noexcept;

      void run();
      inline void quit() noexcept {
        if (!m_should_run_) { return; }
        UE_CORE_WARN("Attempt made to quit Application");
        m_should_run_= false;
      }

      // Returns true to disregard further events in current tick
      bool onEvent(IEvent& p_event) noexcept;
      inline bool onApplicationQuit(ApplicationQuitEvent& p_event) noexcept {
        quit();
        return true;
      }
      inline bool onWindowClose(WindowCloseEvent& p_event) noexcept {
        core::Window::destroyWindow(p_event.getWindowId());
        return false;
      }
      
      inline ImGuiContext*& getImGuiContext() noexcept {
        return m_imgui_context_ptr_;
      }
      void beginImGui() noexcept;
      void prepareImgui(GPUCommandBuffer& p_gpu_command_buffer) noexcept;
      void renderImGui(GPUCommandBuffer& p_gpu_command_buffer, GPURenderPass& p_gpu_render_pass) noexcept;
    private:
      Application(const AppSpecs& p_specs) noexcept;
      ~Application() noexcept;

      bool m_should_run_= false;

      LayerStack m_layer_stack_;
      SDL_Event m_sdl_event_;

      ImDrawData* m_imgui_draw_data_ptr_= nullptr;
      ImGuiContext* m_imgui_context_ptr_= nullptr;

      std::unordered_map<Id, std::function<std::unique_ptr<IEvent>(const SDL_Event&)>> m_sdl_event_callbacks_;
      template<typename CallbackT>
      inline void registerSDLEventCallback(const Id& p_sdl_event_type, CallbackT&& p_callback) noexcept {
        m_sdl_event_callbacks_[p_sdl_event_type]= p_callback;
      }
      inline std::unique_ptr<IEvent> sdlEventCallback(const SDL_Event& p_sdl_event) const noexcept {
        auto callback_it= m_sdl_event_callbacks_.find(p_sdl_event.type);
        if (callback_it == m_sdl_event_callbacks_.end()) { return std::make_unique<NoneEvent>(); }
        return callback_it->second(p_sdl_event);
      }
      void initSDLEventCallbacks() noexcept;
    };
  } // namespace core
} // namespace Units