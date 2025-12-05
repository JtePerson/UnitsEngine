#include "editor_application.h"

#include <UnitsGame/game_layer.h>

#include "editor_layer.h"

namespace editor {
  Application::Application() noexcept: units::IApplication{this} {
    m_window_= units::WindowSpecs{
      .title= "UnitsEditor Window",
      .width= 1280,
      .height= 720,
      .flags= 0
    };
    m_gpu_device_= units::GPUDevice{m_window_};
    units::GPUTextureSpecs gpu_texture_specs{
      .type= units::GPU_TEXTURETYPE_2D,
      .format= units::GPU_TEXTUREFORMAT_R8G8B8A8_UNORM,
      .usage= UE_GPU_TEXTUREUSAGE_COLOR_TARGET | UE_GPU_TEXTUREUSAGE_SAMPLER,
      .width= 100,
      .height= 100,
      .layer_count_or_depth= 1
    };
    m_game_gpu_texture_= units::GPUTexture{m_gpu_device_, gpu_texture_specs};
    initImGui(m_window_, m_gpu_device_);
  }
  Application::~Application() noexcept {}

  void Application::onRun() noexcept {
    attatchLayer<EditorLayer>(0);
    attatchLayer<game::GameLayer>(1);
    processLayerQueue();
    getLayer<EditorLayer>(0)->setGPUTextureCallback([&](units::GPUCommandBuffer* p_gpu_command_buffer_ptr)->units::GPUTexture* {
      if (p_gpu_command_buffer_ptr == nullptr || p_gpu_command_buffer_ptr->expired()) { return nullptr; }
      m_editor_gpu_texture_= units::GPUTexture(*p_gpu_command_buffer_ptr, m_window_);
      return &m_editor_gpu_texture_;
    });
    getLayer<game::GameLayer>(1)->setGPUTextureCallback([&](units::GPUCommandBuffer* p_gpu_command_buffer_ptr)->units::GPUTexture* {
      return &m_game_gpu_texture_;
    });
  }
  void Application::onQuit() noexcept {}
} // namespace editor