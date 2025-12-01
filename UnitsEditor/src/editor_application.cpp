#include "editor_application.h"

#include <UnitsEngine/event/event.h>
#include <UnitsEngine/application.h>
#include <UnitsEngine/gpu/gpu.h>
#include <UnitsEngine/gpu/gpu_texture.h>
#include <UnitsEngine/gpu/gpu_sampler.h>
#include <UnitsEngine/gpu/gpu_texture_sampler_binding.h>
#include <imgui/imgui.h>

#include "editor_layer.h"

namespace Editor {
  Application::Application() noexcept
  : Units::IApplication(this, Units::AppSpecs{
    .main_window_specs= {
      .title= "Units Editor",
      .width= 1280,
      .height= 720,
      .flags= 0
    }
  })
  {
    attatchLayer<EditorLayer>(0);
    initImGui();
    Units::GPUTextureSpecs gpu_texture_specs= {
      .width= 100,
      .height= 100
    };
    m_gpu_texture_= Units::GPUTexture(*Units::IApplication::getInstance()->m_gpu_device_uptr_, gpu_texture_specs);
    Units::GPUSamplerSpecs gpu_sampler_specs= {};
    m_gpu_sampler_= Units::GPUSampler(*Units::IApplication::getInstance()->m_gpu_device_uptr_, gpu_sampler_specs);
    m_gpu_texture_sampler_binding_= Units::GPUTextureSamplerBinding(&m_gpu_texture_, &m_gpu_sampler_);
  }
  Application::~Application() noexcept {}

  void Application::onEvent(Units::IEvent& p_event) noexcept {}
  void Application::onTick() noexcept {}
  void Application::onImGui() noexcept {
    ImGui::Begin("Texture Window");
    ImGui::End();
  }
  void Application::onRender() noexcept {
    Units::GPUCommandBuffer gpu_command_buffer{*m_gpu_device_uptr_};
    prepareImGui(gpu_command_buffer);
    {
      Units::GPURenderPassSpecs gpu_render_pass_specs= {
        .texture= m_gpu_texture_,
        .clear_color= {1.0f, 1.0f, 1.0f, 1.0f}
      };
      Units::GPURenderPass(gpu_command_buffer, gpu_render_pass_specs);
    }
    {
      auto main_window_texture= m_main_window_.getGPUTexture(gpu_command_buffer, true);
      Units::GPURenderPassSpecs gpu_render_pass_specs= {
        .texture= main_window_texture
      };
      Units::GPURenderPass gpu_render_pass{gpu_command_buffer, gpu_render_pass_specs};
      renderImGui(gpu_command_buffer, gpu_render_pass);
    }
    gpu_command_buffer.submit();
  }
} // namespace Editor