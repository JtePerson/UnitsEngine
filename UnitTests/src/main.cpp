#include <UnitsEngine/iapplication.h>
#include <UnitsEngine/ilayer.h>
#include <UnitsEngine/core/log.h>
#include <UnitsEngine/event/application_event.h>
#include <UnitsEngine/event/window_event.h>
#include <UnitsEngine/window/window.h>
#include <UnitsEngine/gpu/gpu_device.h>
#include <UnitsEngine/gpu/gpu_command_buffer.h>
#include <UnitsEngine/gpu/gpu_render_pass.h>

class TestLayer;

class TestApplication final : public units::IApplication {
public:
  inline TestApplication() noexcept: IApplication{this} {
    UE_WARN("Initializing TestApplication");
    UE_INFO("TestApplication Initialized");
  }
  virtual inline ~TestApplication() noexcept {
    UE_WARN("Quitting TestApplication");
    UE_INFO("TestApplication Quit");
  }

  virtual inline void onRun() noexcept {
    UE_TRACE("TestApplication onRun");
    attatchLayer<TestLayer>(0);
    registerEventListener([](units::ApplicationQuitEvent&){
      UE_TRACE("Application Quit Event!");
      return false;
    });
    registerEventListener([](units::WindowCloseEvent& p_event){
      UE_TRACE("Window Close Event [ptr: {0}]!", reinterpret_cast<void*>(p_event.window_ptr));
      return false;
    });
  }
  virtual inline void onQuit() noexcept {
    UE_TRACE("TestApplication onQuit");
  }

  static inline TestApplication* getInstance() noexcept {
    return IApplication::getInstance<TestApplication>();
  }
private:
};

class TestLayer : public units::ILayer {
public:
  inline TestLayer() noexcept= default;
  virtual inline ~TestLayer() noexcept= default;
 
  virtual void onAttatch() noexcept override {
    UE_TRACE("TestLayer Attatched");
    m_window_= units::WindowSpecs{
      .title= "Test Window 0",
      .width= 640,
      .height= 360,
      .flags= UE_WINDOW_RESIZABLE
    };
    m_gpu_device_= units::GPUDevice{m_window_};
  }
  virtual void onDetatch() noexcept override {
    UE_TRACE("TestLayer Detatched");
  }

  virtual void onFixedTick() noexcept override {}
  virtual void onTick() noexcept override {}
  virtual void onImGui() noexcept override {}
  virtual void onRender() noexcept override {
    units::GPUCommandBuffer gpu_command_buffer{m_gpu_device_};
    {
      units::GPUTexture window_gpu_texture{gpu_command_buffer, m_window_};
      units::GPURenderPassSpecs gpu_render_pass_specs= {
        .texture_ptr= &window_gpu_texture,
        .clear_color= {.r= 0.117f, .g= 0.117f, .b=0.176f, .a= 1.0f}
      };
      units::GPURenderPass gpu_render_pass{gpu_command_buffer, gpu_render_pass_specs};
    }
    gpu_command_buffer.submit();
  }
private:
  units::Window m_window_;
  units::GPUDevice m_gpu_device_;
};

int main(int p_argc, char** p_argv) {
  TestApplication test_application{};
  test_application.run();
  return 0;
}