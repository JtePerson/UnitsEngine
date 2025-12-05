#pragma once
#include <UnitsEngine/iapplication.h>

#include "test_layer.h"

namespace test {
  class TestApplication final : public units::IApplication {
  public:
    friend class TestLayer;
  public:
    TestApplication() noexcept;
    inline virtual ~TestApplication() noexcept {
      UE_WARN("Quitting TestApplication");
      UE_INFO("TestApplication Quit");
    }

    virtual void onRun() noexcept;
    inline virtual void onQuit() noexcept {
      UE_TRACE("TestApplication onQuit");
    }

    static inline TestApplication* getInstance() noexcept { return IApplication::getInstance<TestApplication>(); }
  private:
    units::GPUTexture m_gpu_texture_;
  };
} // namespace test