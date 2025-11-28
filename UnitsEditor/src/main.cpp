#include <UnitsEngine/core/application.h>
#include <UnitsEngine/core/entry_point.h>

class UnitsEditor final : public Units::Application {
public:
  UnitsEditor() noexcept: Application({}) {
    UE_WARN("Initializing UnitsEditor");
    UE_INFO("UnitsEditor Initialized");
  }
  ~UnitsEditor() noexcept {
    UE_WARN("Deinitializing UnitsEditor");
    UE_INFO("UnitsEditor Deinitialized");
  }
private:
};

namespace Units {
  Application* createApplication() noexcept {
    return new UnitsEditor();
  }
} // namespace Units