#include <memory>
#include <UnitsEngine/application.h>
#include <UnitsEngine/layer.h>
#include <UnitsEngine/core/core.h>
#include <UnitsEngine/event/event.h>
#include <UnitsEngine/window/window.h>
#include <UnitsEngine/gpu/gpu.h>

class UnitTests : public Units::IApplication {
public:
  inline UnitTests() noexcept: IApplication{this, {}} {
    UE_WARN("Initializing UnitTests");
    Units::WindowSpecs window_specs{
      .title= "UnitTests Window",
      .width= 640,
      .height= 360,
      .flags= UE_WINDOW_RESIZABLE
    };
    Units::Window::newWindow(window_specs);
    m_gpu_device_uptr_->claimWindow(Units::Window::getFromTitle("UnitTests Window"));
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
      auto& window= Units::Window::getFromTitle("UnitTests Window");
      Units::GPURenderPass gpu_render_pass{window, gpu_command_buffer};
    }
    gpu_command_buffer.submit();
  }
private:
};

int main(int p_argc, char** p_argv) {
  UnitTests unit_tests{};
  unit_tests.run();
  return 0;
}