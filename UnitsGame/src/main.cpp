#include <UnitsEngine/core/application.h>
#include <UnitsEngine/core/entry_point.h>

namespace Units::core {
  class UnitsGame final : public Application {
  public:
    UnitsGame() noexcept: Application({}) {
      UE_WARN("Initializing UnitsGame");
      UE_INFO("UnitsGame Initialized");
    }
    ~UnitsGame() noexcept {
      UE_WARN("Deinitializing UnitsGame");
      UE_INFO("UnitsGame Deinitialized");
    }
  private:
  };

  Application* createApplication() noexcept {
    return new UnitsGame();
  }
} // namespace Units