#include "application.h"

#include <SDL3/SDL.h>
/* #include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/imgui_impl_sdl3.h>
#include <imgui/imgui_impl_sdlgpu3.h> */

#include "UnitsEngine/core/log.h"
#include "UnitsEngine/event/event_type.h"
#include "UnitsEngine/event/event_category.h"
#include "UnitsEngine/event/application_event.h"
#include "UnitsEngine/event/window_event.h"

namespace units {
  IApplication::Impl::Impl() noexcept {
    UE_CORE_WARN("Initializing Application");
    SDL_zero(m_sdl_event_);

    /* IMGUI_CHECKVERSION();
    m_application_ptr_->m_imgui_context_ptr= ImGui::CreateContext();
    ImGuiIO& io= ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;

    ImGui::StyleColorsDark();

    auto* sdl_main_window_ptr= core::Window::getFromId(m_main_window_.getId()).getSDLWindowPtr();
    auto* sdl_gpu_device_ptr= reinterpret_cast<SDL_GPUDevice*>(m_gpu_device_uptr_->getDevicePtr());
    ImGui_ImplSDL3_InitForSDLGPU(sdl_main_window_ptr);
    ImGui_ImplSDLGPU3_InitInfo imgui_init_info = {};
    imgui_init_info.Device = sdl_gpu_device_ptr;
    imgui_init_info.ColorTargetFormat = SDL_GetGPUSwapchainTextureFormat(sdl_gpu_device_ptr, sdl_main_window_ptr);
    imgui_init_info.MSAASamples = SDL_GPU_SAMPLECOUNT_1;                      // Only used in multi-viewports mode.
    imgui_init_info.SwapchainComposition = SDL_GPU_SWAPCHAINCOMPOSITION_SDR;  // Only used in multi-viewports mode.
    imgui_init_info.PresentMode = SDL_GPU_PRESENTMODE_VSYNC;
    ImGui_ImplSDLGPU3_Init(&imgui_init_info); */
    UE_CORE_INFO("Application Initialized");
  }
  IApplication::Impl::~Impl() noexcept {
    UE_CORE_WARN("Quitting Application");
    UE_CORE_INFO("Application Quit");
  }

  void IApplication::Impl::run() noexcept {
    if (m_should_run_) { return; }
    m_should_run_= true;

    m_on_run_callback_();
    while (m_should_run_) {
      m_layer_stack_.processLayerQueue();
      {
        while (SDL_PollEvent(&m_sdl_event_)) {
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
            m_application_ptr_->m_event_dispatcher_.dispatch(event, &window_close_event);
            window_close_event.window_ptr->destroy();
          }
        }
        Event event;
        const void* data_ptr;
        while (m_application_ptr_->m_event_bus_.pollEvents(event, data_ptr)) {
          m_application_ptr_->m_event_dispatcher_.dispatch(event, data_ptr);
        }
      }
      m_layer_stack_.forEachLayer([](std::unique_ptr<ILayer>& p_layer_uptr){
        p_layer_uptr->onTick();
      });
      m_layer_stack_.forEachLayer([](std::unique_ptr<ILayer>& p_layer_uptr){
        p_layer_uptr->onRender();
      });
    }
    m_layer_stack_.detatchAllLayers();
    m_on_quit_callback_();
  }
  void IApplication::Impl::quit() noexcept {
    UE_CORE_WARN("Attempt made to quit Application");
    if (!m_should_run_) { return; }
    m_should_run_= false;
    m_application_ptr_->m_event_bus_.push(ApplicationQuitEvent{});
  }
} // namespace units