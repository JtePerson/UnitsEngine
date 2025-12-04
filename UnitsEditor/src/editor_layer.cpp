#include "editor_layer.h"

#include <UnitsEngine/iapplication.h>
#include <UnitsEngine/core/log.h>
#include <UnitsEngine/gpu/gpu_command_buffer.h>
#include <glm/vec2.hpp>

#include "editor_application.h"

namespace editor {
  EditorLayer::EditorLayer() noexcept {
    m_window_= units::WindowSpecs{
      .title= "UnitsEditor Window",
      .width= 1280,
      .height= 720,
      .flags= UE_WINDOW_RESIZABLE
    };
    m_gpu_device_= units::GPUDevice{m_window_};
    Application::getInstance()->initImGui(m_window_, m_gpu_device_);
    units::GPUTextureSpecs gpu_texture_specs{
      .type= units::GPU_TEXTURETYPE_2D,
      .format= units::GPU_TEXTUREFORMAT_R8G8B8A8_UNORM,
      .usage= UE_GPU_TEXTUREUSAGE_COLOR_TARGET | UE_GPU_TEXTUREUSAGE_SAMPLER,
      .width= 100,
      .height= 100,
      .layer_count_or_depth= 1
    };
    m_gpu_texture_= units::GPUTexture{m_gpu_device_, gpu_texture_specs};
  }
  EditorLayer::~EditorLayer() noexcept {
    Application::getInstance()->quitImGui();
  }

  void EditorLayer::onAttatch() noexcept {
    UE_TRACE("EditorLayer attatched");
  }
  void EditorLayer::onDetatch() noexcept {
    UE_TRACE("EditorLayer detatched");
  }

  void EditorLayer::onFixedTick() noexcept {}
  void EditorLayer::onTick() noexcept {}
  void EditorLayer::onImGui() noexcept {
    ImGui::DockSpaceOverViewport(ImGui::GetID("Editor Dockspace"), ImGui::GetMainViewport());
    showSceneWindow();
    showSceneResolutionWindow();
  }
  void EditorLayer::onRender() noexcept {
    units::GPUCommandBuffer gpu_command_buffer{m_gpu_device_};
    Application::getInstance()->prepareImGuiDrawData(gpu_command_buffer);
    {
      units::GPURenderPassSpecs gpu_render_pass_specs{
        .texture_ptr= &m_gpu_texture_,
        .clear_color= {0.117f, 0.117f, 0.176f, 1.0f}
      };
      units::GPURenderPass gpu_render_pass{gpu_command_buffer, gpu_render_pass_specs};
    }
    {
      units::GPUTexture gpu_texture{gpu_command_buffer, m_window_};
      units::GPURenderPassSpecs gpu_render_pass_specs{
        .texture_ptr= &gpu_texture,
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
      ImVec2 texture_size= {static_cast<float32_t>(m_gpu_texture_.getWidth()), static_cast<float32_t>(m_gpu_texture_.getHeight())};
      float32_t scale= std::min(window_size.x / texture_size.x, window_size.y / texture_size.y);
      texture_size.x*= scale;
      texture_size.y*= scale;
      ImGui::SetCursorPos(ImVec2{0.5f * (window_size.x - texture_size.x), 0.5f * (window_size.y - texture_size.y)});
      ImGui::Image(reinterpret_cast<ImTextureID>(m_gpu_texture_.getGPUTexturePtr()), texture_size);
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
        m_gpu_texture_= units::GPUTexture{m_gpu_device_, gpu_texture_specs};
      }
    }
    ImGui::End();
  }
} // namespace editor