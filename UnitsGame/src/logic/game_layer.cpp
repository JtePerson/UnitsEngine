#include "UnitsGame/game_layer.h"

#include <UnitsEngine/core/log.h>

namespace game {
  GameLayer::GameLayer() noexcept {}
  GameLayer::~GameLayer() noexcept {}

  void GameLayer::onAttatch() noexcept {
    UE_TRACE("GameLayer attatched");
  }
  void GameLayer::onDetatch() noexcept {
    UE_TRACE("GameLayer detatched");
  }
  
  void GameLayer::onRender() noexcept {
    if (units::IApplication::getInstance()->m_gpu_device_.expired()) { UE_WARN("GPUDevice is expired!"); return; }
    units::GPUCommandBuffer gpu_command_buffer{units::IApplication::getInstance()->m_gpu_device_};
    units::GPUTexture* gpu_texture_ptr= getGPUTexture(&gpu_command_buffer);
    if (gpu_texture_ptr != nullptr && !gpu_texture_ptr->expired()) {
      units::GPURenderPassSpecs gpu_render_pass_specs{
        .texture_ptr= gpu_texture_ptr,
        .clear_color= {0.117f, 0.117f, 0.176f, 1.0f}
      };
      units::GPURenderPass gpu_render_pass{gpu_command_buffer, gpu_render_pass_specs};
    }
    gpu_command_buffer.submit();
  }
} // namespace game