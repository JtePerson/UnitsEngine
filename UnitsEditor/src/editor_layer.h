#pragma once
#include <UnitsEngine/ilayer.h>

namespace editor {
  class EditorLayer final : public units::ILayer {
  public:
    EditorLayer() noexcept;
    virtual ~EditorLayer() noexcept override;

    virtual void onAttatch() noexcept override;
    virtual void onDetatch() noexcept override;

    virtual bool onEvent(units::Event& p_event, const void*& p_data_ptr) noexcept override;
    virtual bool onFixedTick() noexcept override;
    virtual bool onTick() noexcept override;
    virtual bool onImGui() noexcept override;
    virtual void onRender() noexcept override;
  private:
    void showSceneWindow() noexcept;
    void showSceneResolutionWindow() noexcept;
  };
} // namespace editor