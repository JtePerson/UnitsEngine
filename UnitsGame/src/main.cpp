#include <UnitsEngine/core/application.h>
#include <UnitsEngine/core/entry_point.h>

class Sandbox final : public Units::Application {
public:
  Sandbox() noexcept: Application({}) {
    UE_WARN("Initializing Sandbox");
    UE_INFO("Sandbox Initialized");
  }
  ~Sandbox() noexcept {
    UE_WARN("Deinitializing Sandbox");
    UE_INFO("Sandbox Deinitialized");
  }
private:
};

namespace Units {
  Application* createApplication() noexcept {
    return new Sandbox();
  }
} // namespace Units