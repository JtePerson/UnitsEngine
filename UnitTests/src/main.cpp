#include <memory>
#include <UnitsEngine/application.h>
#include <UnitsEngine/layer.h>
#include <UnitsEngine/core/core.h>
#include <UnitsEngine/event/event.h>
#include <UnitsEngine/window/window.h>
#include <UnitsEngine/gpu/gpu.h>

class TestLayer : public Units::ILayer {
public:
  inline TestLayer() noexcept {}
  virtual inline ~TestLayer() noexcept override {}

  virtual inline void onAttatch() noexcept override {
    UE_TRACE("Test Layer Attatched");
  }
  virtual inline void onDetatch() noexcept override {
    UE_TRACE("Test Layer Detatched");
  }

  virtual inline void onEvent(Units::IEvent& p_event) noexcept override {
    UE_TRACE("Event triggered [name: {0}]", p_event.getName());
  }
  virtual inline bool onTick() noexcept override {
    return true;
  }
private:
};

class UnitTests : public Units::IApplication {
public:
  inline UnitTests() noexcept
  : IApplication{this, {}},
  m_window_(Units::Window::newWindow(Units::WindowSpecs{
      .title= "UnitTests Window",
      .width= 640,
      .height= 360,
      .flags= UE_WINDOW_RESIZABLE
    })) 
  {
    UE_WARN("Initializing UnitTests");
    attatchLayer<TestLayer>(0);
    m_gpu_device_uptr_= std::make_unique<Units::GPUDevice>();
    m_gpu_device_uptr_->claimWindow(m_window_);
    UE_INFO("UnitTests Initialized");
  }
  virtual inline ~UnitTests() noexcept override {
    UE_WARN("Quitting UnitTests");
    UE_INFO("UnitTests Quit");
  }

  virtual inline void onEvent(Units::IEvent& p_event) noexcept override {}
  virtual inline void onTick() noexcept override {
    Units::GPUCommandBuffer gpu_command_buffer{*m_gpu_device_uptr_};
    {
      Units::GPURenderPass gpu_render_pass{m_window_, gpu_command_buffer};
    }
    gpu_command_buffer.submit();
  }
private:
  std::unique_ptr<Units::GPUDevice> m_gpu_device_uptr_= nullptr;
  Units::Window& m_window_;
};

int main(int p_argc, char** p_argv) {
  UnitTests unit_tests{};
  unit_tests.run();
  return 0;
}