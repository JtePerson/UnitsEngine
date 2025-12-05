#include "test_application.h"

namespace test {
  TestApplication::TestApplication() noexcept: IApplication{this} {
    UE_WARN("Initializing TestApplication");
    m_window_= units::WindowSpecs{
      .title= "UnitTests Window",
      .width= 1280,
      .height= 720,
      .flags= 0
    };
    m_gpu_device_= units::GPUDevice{m_window_};
    initImGui(m_window_, m_gpu_device_);
    UE_INFO("TestApplication Initialized");
  }

  void TestApplication::onRun() noexcept {
    UE_TRACE("TestApplication onRun");
    attatchLayer<TestLayer>(0);
    processLayerQueue();
    getLayer<TestLayer>(0)->setGPUTextureCallback([&](units::GPUCommandBuffer* p_gpu_command_buffer_ptr)->units::GPUTexture* {
      if (p_gpu_command_buffer_ptr == nullptr || p_gpu_command_buffer_ptr->expired()) { return nullptr; }
      m_gpu_texture_= units::GPUTexture{*p_gpu_command_buffer_ptr, m_window_};
      return &m_gpu_texture_;
    });
  }
} // namespace test
