#include "UnitsEngine/application.h"
#include "application.h"

#include <SDL3/SDL.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl3.h>
#include <imgui/imgui_impl_sdlgpu3.h>

#include "UnitsEngine/core/log.h"
#include "UnitsEngine/core/assert.h"
#include "UnitsEngine/app_specs.h"
#include "UnitsEngine/event/event.h"
#include "UnitsEngine/gpu/gpu_device.h"
#include "UnitsEngine/gpu/gpu_command_buffer.h"
#include "UnitsEngine/gpu/gpu_render_pass.h"

namespace Units {
  IApplication::IApplication(IApplication* p_derived_ptr, AppSpecs&& p_specs) noexcept
  : m_main_window_(Window::newWindow(p_specs.main_window_specs))
  {
    UE_CORE_WARN("Initializing IApplication");
    core::Application::getInstance(p_specs);
    if (s_instance_ptr_ != nullptr) { return; }
    s_instance_ptr_= p_derived_ptr;
    m_gpu_device_uptr_= std::make_unique<GPUDevice>();
    m_gpu_device_uptr_->claimWindow(m_main_window_);
    
    IMGUI_CHECKVERSION();
    core::Application::getInstance()->getImGuiContext()= ImGui::CreateContext();
    ImGuiIO& io= ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

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
    ImGui_ImplSDLGPU3_Init(&imgui_init_info);
    UE_CORE_INFO("IApplication Initialized");
  }

  void IApplication::attatchLayer(const Id& p_layer_id, const I& p_i) noexcept {
    core::Application::getInstance()->attatchLayer(p_layer_id, p_i);
  }
  void IApplication::detatchLayer(const Id& p_layer_id, const I& p_i) noexcept {
    core::Application::getInstance()->detatchLayer(p_layer_id, p_i);
  }

  IApplication::~IApplication() noexcept {
    UE_CORE_WARN("Quitting IApplication");
    ImGui_ImplSDL3_Shutdown();
    ImGui_ImplSDLGPU3_Shutdown();
    ImGui::DestroyContext();
    UE_CORE_INFO("IApplication Quit");
  }
  void IApplication::run() const noexcept {
    core::Application::getInstance()->run();
  }
  void IApplication::quit() const noexcept {
    core::Application::getInstance()->quit();
  }
  
  ImGuiContext* IApplication::getImGuiContext() noexcept {
    return core::Application::getInstance()->getImGuiContext();
  }
  void IApplication::beginImGui() noexcept {
    core::Application::getInstance()->beginImGui();
  }
  void IApplication::prepareImGui(GPUCommandBuffer& p_gpu_command_buffer) noexcept {
    core::Application::getInstance()->prepareImgui(p_gpu_command_buffer);
  }
  void IApplication::renderImGui(GPUCommandBuffer& p_gpu_command_buffer, GPURenderPass& p_gpu_render_pass) noexcept {
    core::Application::getInstance()->renderImGui(p_gpu_command_buffer, p_gpu_render_pass);
  }

  namespace core {
    Application::Application(const AppSpecs& p_specs) noexcept {
      UE_CORE_WARN("Initializing Application");
      if (!SDL_Init(SDL_INIT_VIDEO)) {
        UE_CORE_CRITICAL("Could not Initialize SDL! error: {0}", SDL_GetError());
        UE_CORE_ASSERT(false, "SDL not initialized!");
      }
      initSDLEventCallbacks();
      UE_CORE_INFO("Application Initialized");
    }
    Application::~Application() noexcept {
      UE_CORE_WARN("Quitting Application");
      UE_CORE_INFO("Application Quit");
    }

    void Application::attatchLayer(const Id& p_layer_id, const I& p_i) noexcept {
      m_layer_stack_.attatchLayer(p_layer_id, p_i);
    }
    void Application::detatchLayer(const Id& p_layer_id, const I& p_i) noexcept {
      m_layer_stack_.detatchLayer(p_layer_id, p_i);
    }

    void Application::run() {
      if (m_should_run_) { UE_CORE_WARN("Application Already Running!"); return; }
      m_should_run_= true;

      UE_CORE_WARN("Running Application");
      while (m_should_run_) {
        // Run Application
        m_layer_stack_.processLayerQueue();

        while (SDL_PollEvent(&m_sdl_event_)) {
          ImGui_ImplSDL3_ProcessEvent(&m_sdl_event_);
          auto current_event= sdlEventCallback(m_sdl_event_);
          if (current_event->getId() != static_cast<EventId>(EventType::kNone)) {
            if (onEvent(*current_event)) { break; }
          }
        }
        if (!m_should_run_) { break; }

        IApplication::getInstance()->onTick();
        m_layer_stack_.processLayerTick();
      }
      m_layer_stack_.detatchAllLayers();
      UE_CORE_INFO("Application Ran");
    }

    void Application::initSDLEventCallbacks() noexcept {
      registerSDLEventCallback(SDL_EVENT_QUIT, [this](const SDL_Event& p_event){
        return std::make_unique<ApplicationQuitEvent>();
      });
      registerSDLEventCallback(SDL_EVENT_WINDOW_CLOSE_REQUESTED, [this](const SDL_Event& p_event){
        return std::make_unique<WindowCloseEvent>(SDL_GetWindowTitle(SDL_GetWindowFromEvent(&p_event)), p_event.window.windowID);
      });
    }

    bool Application::onEvent(IEvent& p_event) noexcept {
      EventDispatcher event_dispatcher{p_event};
      if (event_dispatcher.dispatch<ApplicationQuitEvent>(UE_BIND_FUNCTION(Application::onApplicationQuit))) { return true; }
      event_dispatcher.dispatch<WindowCloseEvent>(UE_BIND_FUNCTION(Application::onWindowClose));

      IApplication::getInstance()->onEvent(p_event);
      if (!p_event.handled()) {
        m_layer_stack_.processLayerEvents(p_event);
      }
      
      return false;
    }

    void Application::beginImGui() noexcept {
      ImGui_ImplSDLGPU3_NewFrame();
      ImGui_ImplSDL3_NewFrame();
      ImGui::NewFrame();
    }
    void Application::prepareImgui(GPUCommandBuffer& p_gpu_command_buffer) noexcept {
      ImGui::Render();
      m_imgui_draw_data_ptr_= ImGui::GetDrawData();
      ImGui_ImplSDLGPU3_PrepareDrawData(
        m_imgui_draw_data_ptr_,
        reinterpret_cast<SDL_GPUCommandBuffer*>(p_gpu_command_buffer.getGPUCommandBufferPtr())
      );
    }
    void Application::renderImGui(GPUCommandBuffer& p_gpu_command_buffer, GPURenderPass& p_gpu_render_pass) noexcept {
      ImGui_ImplSDLGPU3_RenderDrawData(
        m_imgui_draw_data_ptr_,
        reinterpret_cast<SDL_GPUCommandBuffer*>(p_gpu_command_buffer.getGPUCommandBufferPtr()),
        reinterpret_cast<SDL_GPURenderPass*>(p_gpu_render_pass.getGPURenderPass())
      );
    }
  } // namespace core
} // namespace Units