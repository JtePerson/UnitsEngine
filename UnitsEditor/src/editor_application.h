#pragma once
#include <UnitsEngine/iapplication.h>

namespace Editor {
  class Application final : public Units::IApplication {
  public:
    Application() noexcept;
    virtual ~Application() noexcept override;

    virtual void onRun() noexcept override;
    virtual void onQuit() noexcept override;
  private:
  };
} // namespace Editor