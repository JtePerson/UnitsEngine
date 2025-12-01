#include <memory>
#include <UnitsEngine/application.h>
#include <UnitsEngine/layer.h>
#include <UnitsEngine/core/core.h>
#include <UnitsEngine/event/event.h>
#include <UnitsEngine/window/window.h>
#include <UnitsEngine/gpu/gpu.h>
#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>

class UnitTests final : public Units::IApplication {
public:
  inline UnitTests() noexcept: IApplication{this, Units::AppSpecs{
    .main_window_specs= {
      .title= "UnitTests Window",
      .width= 640,
      .height= 360,
      .flags= UE_WINDOW_RESIZABLE
    }
  }} {
    UE_WARN("Initializing UnitTests");
    initImGui();
    UE_INFO("UnitTests Initialized");
  }
  virtual inline ~UnitTests() noexcept override {
    UE_WARN("Quitting UnitTests");
    UE_INFO("UnitTests Quit");
  }

  virtual inline void onEvent(Units::IEvent& p_event) noexcept override {}
  virtual inline void onTick() noexcept override {}
  virtual inline void onImGui() noexcept override {
    ImGui::ShowDemoWindow();
  }
  virtual inline void onRender() noexcept override {
    Units::GPUCommandBuffer gpu_command_buffer{*m_gpu_device_uptr_};
    prepareImGui(gpu_command_buffer);
    {
      Units::GPURenderPass gpu_render_pass{m_main_window_, gpu_command_buffer};
      renderImGui(gpu_command_buffer, gpu_render_pass);
    }
    gpu_command_buffer.submit();
  }
private:
  bool m_show_imgui_demo_window_= true;
};

int main(int p_argc, char** p_argv) {
  UnitTests unit_tests{};
  unit_tests.run();
  return 0;
}