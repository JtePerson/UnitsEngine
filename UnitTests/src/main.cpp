#include <UnitsEngine/iapplication.h>
#include <UnitsEngine/ilayer.h>
#include <UnitsEngine/core/log.h>

class TestLayer : public Units::ILayer {
public:
  inline TestLayer() noexcept= default;
  virtual inline ~TestLayer() noexcept= default;
 
  virtual void onAttatch() noexcept override {
    UE_TRACE("TestLayer Attatched");
  }
  virtual void onDetatch() noexcept override {
    UE_TRACE("TestLayer Detatched");
  }

  virtual void onEvent() noexcept override {}
  virtual void onFixedTick() noexcept override {}
  virtual void onTick() noexcept override {
    UE_TRACE("TestLayer Ticked");
  }
  virtual void onImGui() noexcept override {}
  virtual void onRender() noexcept override {}
protected:
};
class AnotherTestLayer : public Units::ILayer {
public:
  inline AnotherTestLayer() noexcept= default;
  virtual inline ~AnotherTestLayer() noexcept= default;
 
  virtual void onAttatch() noexcept override {
    UE_TRACE("AnotherTestLayer Attatched");
  }
  virtual void onDetatch() noexcept override {
    UE_TRACE("AnotherTestLayer Detatched");
  }

  virtual void onEvent() noexcept override {}
  virtual void onFixedTick() noexcept override {}
  virtual void onTick() noexcept override {
    UE_TRACE("AnotherTestLayer Ticked");
  }
  virtual void onImGui() noexcept override {}
  virtual void onRender() noexcept override {}
protected:
};

class TestApplication final : public Units::IApplication {
public:
  inline TestApplication() noexcept {
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
    attatchLayer<AnotherTestLayer>(1);
  }
  virtual inline void onQuit() noexcept {
    UE_TRACE("TestApplication onQuit");
  }
private:
};

int main(int p_argc, char** p_argv) {
  TestApplication test_application{};
  test_application.run();
  return 0;
}