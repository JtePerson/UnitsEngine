#include <UnitsEngine/iapplication.h>

#include "test_layer.h"

namespace test {
  void TestLayer::onRender() noexcept {
    units::GPUCommandBuffer gpu_command_buffer{units::IApplication::getInstance()->m_gpu_device_};
    units::IApplication::getInstance()->prepareImGuiDrawData(gpu_command_buffer);
    {
      units::GPURenderPassSpecs gpu_render_pass_specs= {
        .texture_ptr= getGPUTexture(&gpu_command_buffer),
        .clear_color= {.r= 0.117f, .g= 0.117f, .b=0.176f, .a= 1.0f}
      };
      units::GPURenderPass gpu_render_pass{gpu_command_buffer, gpu_render_pass_specs};
      units::IApplication::getInstance()->renderImGuiDrawData(gpu_command_buffer, gpu_render_pass);
    }
    gpu_command_buffer.submit();
  }
} // namespace test
