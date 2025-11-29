#include <UnitsEngine/core/application.h>
#include <UnitsEngine/core/entry_point.h>


namespace Units::core {
  class UnitsEditor final : public Application {
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

  Application* createApplication() noexcept {
    return new UnitsEditor();
  }
} // namespace Units