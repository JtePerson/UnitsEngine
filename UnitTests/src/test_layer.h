#pragma once
#include <UnitsEngine/ilayer.h>

namespace test {
  class TestLayer : public units::ILayer {
  public:
    inline TestLayer() noexcept= default;
    virtual inline ~TestLayer() noexcept= default;
   
    inline virtual void onAttatch() noexcept override {
      UE_TRACE("TestLayer Attatched");
    }
    inline virtual void onDetatch() noexcept override {
      UE_TRACE("TestLayer Detatched");
    }

    inline virtual bool onEvent(units::Event& p_event, const void*& p_data_ptr) noexcept override { return true; }
    inline virtual bool onFixedTick() noexcept override { return true; }
    inline virtual bool onTick() noexcept override { return true; }
    inline virtual bool onImGui() noexcept override {
      ImGui::ShowDemoWindow();
      return true;
    }
    virtual void onRender() noexcept override;
  private:
  };
} // namespace test