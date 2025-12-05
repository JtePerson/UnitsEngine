#include "editor_layer.h"

#include <UnitsEngine/iapplication.h>
#include <UnitsEngine/core/log.h>
#include <UnitsEngine/gpu/gpu_command_buffer.h>
#include <glm/vec2.hpp>

#include "editor_application.h"

namespace editor {
  EditorLayer::EditorLayer() noexcept {}
  EditorLayer::~EditorLayer() noexcept {
    Application::getInstance()->quitImGui();
  }

  void EditorLayer::onAttatch() noexcept {
    UE_TRACE("EditorLayer attatched");
  }
  void EditorLayer::onDetatch() noexcept {
    UE_TRACE("EditorLayer detatched");
  }

  bool EditorLayer::onEvent(units::Event& p_event, const void*& p_data_ptr) noexcept { return false; }
  bool EditorLayer::onFixedTick() noexcept { return false; }
  bool EditorLayer::onTick() noexcept { return false; }
  bool EditorLayer::onImGui() noexcept {
    ImGui::DockSpaceOverViewport(ImGui::GetID("Editor Dockspace"), ImGui::GetMainViewport());
    showSceneWindow();
    showSceneResolutionWindow();
    return false;
  }
  void EditorLayer::onRender() noexcept {
    units::GPUCommandBuffer gpu_command_buffer{Application::getInstance()->m_gpu_device_};

    Application::getInstance()->prepareImGuiDrawData(gpu_command_buffer);
    units::GPUTexture* gpu_texture_ptr= getGPUTexture(&gpu_command_buffer);
    if (gpu_texture_ptr != nullptr && !gpu_texture_ptr->expired()) {
      units::GPURenderPassSpecs gpu_render_pass_specs{
        .texture_ptr= gpu_texture_ptr,
        .clear_color= {0.0f, 0.0f, 0.0f, 1.0f}
      };
      units::GPURenderPass gpu_render_pass{gpu_command_buffer, gpu_render_pass_specs};
      Application::getInstance()->renderImGuiDrawData(gpu_command_buffer, gpu_render_pass);
    }
    
    gpu_command_buffer.submit();
  }

  void EditorLayer::showSceneWindow() noexcept {
    ImVec2 old_padding= ImGui::GetStyle().WindowPadding;
    ImGui::GetStyle().WindowPadding= ImVec2{0.0f, 0.0f};
    if (ImGui::Begin("Scene")) {
      ImVec2 window_size= ImGui::GetWindowSize();
      units::GPUTexture& gpu_texture= Application::getInstance()->m_game_gpu_texture_;
      ImVec2 texture_size= {static_cast<float32_t>(gpu_texture.getWidth()), static_cast<float32_t>(gpu_texture.getHeight())};
      float32_t scale= std::min(window_size.x / texture_size.x, window_size.y / texture_size.y);
      texture_size.x*= scale;
      texture_size.y*= scale;
      ImGui::SetCursorPos(ImVec2{0.5f * (window_size.x - texture_size.x), 0.5f * (window_size.y - texture_size.y)});
      ImGui::Image(reinterpret_cast<ImTextureID>(gpu_texture.getGPUTexturePtr()), texture_size);
    }
    ImGui::End();
    ImGui::GetStyle().WindowPadding= old_padding;
  }
  void EditorLayer::showSceneResolutionWindow() noexcept {
    if (ImGui::Begin("Scene Resolution")) {
      static const char* items[]= {"100x100", "640x360"};
      static const glm::uvec2 resolutions[]= {{100u, 100u}, {640u, 360u}};
      static int selected_item= 0;
      if (ImGui::Combo("Resolution", &selected_item, items, IM_ARRAYSIZE(items))) {
        units::GPUTextureSpecs gpu_texture_specs{
          .type= units::GPU_TEXTURETYPE_2D,
          .format= units::GPU_TEXTUREFORMAT_R8G8B8A8_UNORM,
          .usage= UE_GPU_TEXTUREUSAGE_COLOR_TARGET | UE_GPU_TEXTUREUSAGE_SAMPLER,
          .width= resolutions[selected_item].x,
          .height= resolutions[selected_item].y,
          .layer_count_or_depth= 1
        };
        Application::getInstance()->m_game_gpu_texture_= units::GPUTexture{Application::getInstance()->m_gpu_device_, gpu_texture_specs};
      }
    }
    ImGui::End();
  }
} // namespace editor