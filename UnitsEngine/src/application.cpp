#include "application.h"

#include <SDL3/SDL.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl3.h>
#include <imgui/imgui_impl_sdlgpu3.h>

#include "UnitsEngine/core/log.h"
#include "UnitsEngine/event/event_type.h"
#include "UnitsEngine/event/event_category.h"
#include "UnitsEngine/event/application_event.h"
#include "UnitsEngine/event/window_event.h"

namespace units {
  IApplication::Impl::Impl() noexcept {
    UE_CORE_WARN("Initializing Application");
    SDL_zero(m_sdl_event_);
    if (!SDL_Init(SDL_INIT_VIDEO)) {
      UE_CORE_ERROR("SDL error: {0}", SDL_GetError());
      UE_CORE_ASSERT(false, "Could not Initialize SDL!");
    }
    UE_CORE_INFO("Application Initialized");
  }
  IApplication::Impl::~Impl() noexcept {
    UE_CORE_WARN("Quitting Application");
    SDL_Quit();
    UE_CORE_INFO("Application Quit");
  }

  void IApplication::initImGuiBackend(Window& p_window, GPUDevice& p_gpu_device) noexcept {
    ImGui::SetCurrentContext(m_imgui_context_ptr_);

    auto* sdl_main_window_ptr= reinterpret_cast<SDL_Window*>(p_window.getWindowPtr());
    auto* sdl_gpu_device_ptr= reinterpret_cast<SDL_GPUDevice*>(p_gpu_device.getGPUDevicePtr());
    ImGui_ImplSDL3_InitForSDLGPU(sdl_main_window_ptr);
    ImGui_ImplSDLGPU3_InitInfo imgui_init_info = {};
    imgui_init_info.Device = sdl_gpu_device_ptr;
    imgui_init_info.ColorTargetFormat = SDL_GetGPUSwapchainTextureFormat(sdl_gpu_device_ptr, sdl_main_window_ptr);
    imgui_init_info.MSAASamples = SDL_GPU_SAMPLECOUNT_1;                      // Only used in multi-viewports mode.
    imgui_init_info.SwapchainComposition = SDL_GPU_SWAPCHAINCOMPOSITION_SDR;  // Only used in multi-viewports mode.
    imgui_init_info.PresentMode = SDL_GPU_PRESENTMODE_VSYNC;
    ImGui_ImplSDLGPU3_Init(&imgui_init_info);
  }
  void IApplication::quitImGui() noexcept {
    ImGui_ImplSDL3_Shutdown();
    ImGui_ImplSDLGPU3_Shutdown();
    ImGui::DestroyContext();
  }

  void IApplication::prepareImGuiDrawData(GPUCommandBuffer& p_gpu_command_buffer) noexcept {
    ImGui::Render();
    m_imgui_draw_data_ptr_= ImGui::GetDrawData();
    ImGui_ImplSDLGPU3_PrepareDrawData(
      m_imgui_draw_data_ptr_,
      reinterpret_cast<SDL_GPUCommandBuffer*>(p_gpu_command_buffer.getGPUCommandBufferPtr())
    );
  }
  void IApplication::renderImGuiDrawData(GPUCommandBuffer& p_gpu_command_buffer, GPURenderPass& p_gpu_render_pass) noexcept {
    ImGui_ImplSDLGPU3_RenderDrawData(
      m_imgui_draw_data_ptr_,
      reinterpret_cast<SDL_GPUCommandBuffer*>(p_gpu_command_buffer.getGPUCommandBufferPtr()),
      reinterpret_cast<SDL_GPURenderPass*>(p_gpu_render_pass.getGPURenderPassPtr())
    );
  }

  void IApplication::processLayerQueue() noexcept {
    m_impl_uptr_->m_layer_stack_.processLayerQueue();
  }

  void IApplication::Impl::run() noexcept {
    if (m_should_run_) { return; }
    m_should_run_= true;

    m_on_run_callback_();
    while (m_should_run_) {
      m_layer_stack_.processLayerQueue();
      {
        while (SDL_PollEvent(&m_sdl_event_)) {
          if (m_application_ptr_->m_imgui_context_ptr_ != nullptr) {
            ImGui_ImplSDL3_ProcessEvent(&m_sdl_event_);
          }
          if (m_sdl_event_.type == SDL_EVENT_QUIT) {
            quit();
            break;
          }
          if (m_sdl_event_.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED) {
            Event event{
              .type= kUE_EventTypeWindowClose,
              .category= UE_EVENTCATEGORY_NONE,
              .size= sizeof(WindowCloseEvent),
              .handled= false
            };
            WindowCloseEvent window_close_event{
              .window_ptr= Window::getFromId(m_sdl_event_.window.windowID)
            };
            m_application_ptr_->dispatchEvent(event, &window_close_event);
            window_close_event.window_ptr->destroy();
            if (Window::count() == 0) {
              quit();
              break;
            }
          }
        }
        Event event;
        const void* data_ptr;
        while (m_application_ptr_->m_event_bus_.pollEvents(event, data_ptr)) {
          m_application_ptr_->dispatchEvent(event, data_ptr);
          m_layer_stack_.forEachLayer([&](std::unique_ptr<ILayer>& p_layer_uptr){
            return p_layer_uptr->onEvent(event, data_ptr);
          });
        }
      }
      if (!m_should_run_) { break; }
      m_layer_stack_.forEachLayer([](std::unique_ptr<ILayer>& p_layer_uptr){
        return p_layer_uptr->onTick();
      });
      if (m_application_ptr_->m_imgui_context_ptr_ != nullptr) {
        ImGui_ImplSDLGPU3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        m_layer_stack_.forEachLayer([](std::unique_ptr<ILayer>& p_layer_uptr){
          return p_layer_uptr->onImGui();
        });
      }
      m_layer_stack_.forEachLayerReverse([](std::unique_ptr<ILayer>& p_layer_uptr){
        p_layer_uptr->onRender();
        return false;
      });
      if (m_application_ptr_->m_imgui_context_ptr_ != nullptr) {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        ImGui::EndFrame();
      }
    }
    m_layer_stack_.detatchAllLayers();
    m_on_quit_callback_();
  }
  void IApplication::Impl::quit() noexcept {
    UE_CORE_WARN("Attempt made to quit Application");
    if (!m_should_run_) { return; }
    m_should_run_= false;
    m_application_ptr_->pushEvent(ApplicationQuitEvent{});
  }
} // namespace units