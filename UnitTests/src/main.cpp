#include <UnitsEngine/application.h>
#include <UnitsEngine/log.h>
#include <UnitsEngine/layer.h>

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
private:
};

class UnitTests : public Units::IApplication {
public:
  inline UnitTests() noexcept: IApplication{this, {}} {
    UE_WARN("Initializing UnitTests");
    attatchLayer<TestLayer>(0);
    UE_INFO("UnitTests Initialized");
  }
  virtual inline ~UnitTests() noexcept override {
    UE_WARN("Quitting UnitTests");
    UE_INFO("UnitTests Quit");
  }
private:
};

int main(int p_argc, char** p_argv) {
  UnitTests unit_tests{};
  unit_tests.run();
  return 0;
}