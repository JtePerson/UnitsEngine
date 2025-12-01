#pragma once
#include <UnitsEngine/layer.h>
#include <UnitsEngine/event/event.h>

namespace Editor {
  class EditorLayer final : public Units::ILayer {
  public:
    EditorLayer() noexcept;
    virtual ~EditorLayer() noexcept override;

    virtual void onAttatch() noexcept override;
    virtual void onDetatch() noexcept override;
    virtual void onEvent(Units::IEvent& p_event) noexcept override;
    virtual bool onTick() noexcept override;
    virtual bool onImGui() noexcept override;
  private:
    void showTestWindow() noexcept;
    void showAnotherTestWindow() noexcept;
  };
} // namespace Editor