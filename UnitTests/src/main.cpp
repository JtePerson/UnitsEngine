#include <UnitsEngine/application.h>
#include <UnitsEngine/log.h>

class UnitTests : public Units::IApplication {
public:
  inline UnitTests() noexcept: IApplication{this, {}} {
    UE_WARN("Initializing UnitTests");
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