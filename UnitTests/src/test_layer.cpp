#include "test_layer.h"

#include <UnitsEngine/iapplication.h>
#include <UnitsEngine/gpu/gpu_shader.h>


namespace test {
  TestLayer::TestLayer() noexcept {
    units::GPUShader gpu_vertex_shader{units::IApplication::getInstance()->m_gpu_device_, units::GPUShaderSpecs{
      .filepath= "RawTriangle.vert",
      .sampler_count= 0,
      .storage_texture_count= 0,
      .storage_buffer_count= 0,
      .uniform_buffer_count= 0
    }};
    units::GPUShader gpu_fragment_shader{units::IApplication::getInstance()->m_gpu_device_, units::GPUShaderSpecs{
      .filepath= "SolidColor.frag",
      .sampler_count= 0,
      .storage_texture_count= 0,
      .storage_buffer_count= 0,
      .uniform_buffer_count= 0
    }};
    m_gpu_graphics_pipeline_= units::GPUGraphicsPipeline{units::IApplication::getInstance()->m_gpu_device_, units::GPUGraphicsPipelineSpecs{
      .vertex_shader_ptr= &gpu_vertex_shader,
      .fragment_shader_ptr= &gpu_fragment_shader,
      .texture_format= units::IApplication::getInstance()->m_window_.getGPUTextureFormat(units::IApplication::getInstance()->m_gpu_device_),
      .wireframe_mode= true
    }};
  }
  void TestLayer::onRender() noexcept {
    units::GPUCommandBuffer gpu_command_buffer{units::IApplication::getInstance()->m_gpu_device_};
    units::IApplication::getInstance()->prepareImGuiDrawData(gpu_command_buffer);
    {
      units::GPURenderPassSpecs gpu_render_pass_specs= {
        .texture_ptr= getGPUTexture(&gpu_command_buffer),
        .clear_color= {.r= 0.117f, .g= 0.117f, .b=0.176f, .a= 1.0f}
      };
      units::GPURenderPass gpu_render_pass{gpu_command_buffer, gpu_render_pass_specs};
      m_gpu_graphics_pipeline_.bindToRenderPass(gpu_render_pass);
      gpu_render_pass.setGPUViewport(0, 0, 200, 200, 0.1f, 1.0f);
      gpu_render_pass.setGPUScissor(0, 0, 150, 150);
      gpu_render_pass.drawGPUPrimitives(3, 1, 0, 0);
      units::IApplication::getInstance()->renderImGuiDrawData(gpu_command_buffer, gpu_render_pass);
    }
    gpu_command_buffer.submit();
  }
} // namespace test
