#pragma once
#include <UnitsEngine/ilayer.h>
#include <UnitsEngine/event/event.h>

namespace Editor {
  class EditorLayer final : public Units::ILayer {
  public:
    EditorLayer() noexcept;
    virtual ~EditorLayer() noexcept override;

    virtual void onAttatch() noexcept override;
    virtual void onDetatch() noexcept override;

    virtual void onEvent() noexcept override;
    virtual void onFixedTick() noexcept override;
    virtual void onTick() noexcept override;
    virtual void onImGui() noexcept override;
    virtual void onRender() noexcept override;
  private:
  };
} // namespace Editor