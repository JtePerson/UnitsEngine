#include <UnitsEngine/core/application.h>
#include <UnitsEngine/core/entry_point.h>

class UnitTests final : public Units::Application {
public:
  UnitTests() noexcept: Application({}) {
    UE_WARN("Initializing UnitTests");
    UE_INFO("UnitTest Initialized");
  }
  ~UnitTests() noexcept {
    UE_WARN("Deinitializing UnitTests");
    UE_INFO("UnitTest Deinitialized");
  }
private:
};

namespace Units {
  Application* createApplication() noexcept {
    return new UnitTests();
  }
} // namespace Units