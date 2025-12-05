#include "game_application.h"

namespace game {
  Application::Application() noexcept: IApplication{this} {
    UE_WARN("Initializing Game");
    m_window_= units::WindowSpecs{
      .title= "Units Game",
      .width= 1280,
      .height= 720,
      .flags= 0
    };
    m_gpu_device_= units::GPUDevice{m_window_};
    UE_INFO("Game Initialized");
  }

  void Application::onRun() noexcept {
    UE_TRACE("Run Game");
    attatchLayer<game::GameLayer>(0);
    processLayerQueue();
    m_game_layer_ptr_= getLayer<game::GameLayer>(0);
    UE_TRACE("GameLayer ptr: {0}", static_cast<void*>(m_game_layer_ptr_));
    m_game_layer_ptr_->setGPUTextureCallback([&](units::GPUCommandBuffer* p_gpu_command_buffer_ptr)->units::GPUTexture* {
      if (p_gpu_command_buffer_ptr == nullptr || p_gpu_command_buffer_ptr->expired()) { return nullptr; }
      m_gpu_texture_= units::GPUTexture(*p_gpu_command_buffer_ptr, m_window_);
      return &m_gpu_texture_;
    });
  }
} // namespace game