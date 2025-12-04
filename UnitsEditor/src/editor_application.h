#pragma once
#include <UnitsEngine/iapplication.h>

namespace Editor {
  class Application final : public units::IApplication {
  public:
    Application() noexcept;
    virtual ~Application() noexcept override;

    virtual void onRun() noexcept override;
    virtual void onQuit() noexcept override;

    static inline Application* getInstance() noexcept { return IApplication::getInstance<Application>(); }
  private:
  };
} // namespace Editor