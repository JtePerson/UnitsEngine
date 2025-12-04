#pragma once
#include <UnitsEngine/ilayer.h>
#include <UnitsEngine/window/window.h>
#include <UnitsEngine/gpu/gpu_device.h>
#include <UnitsEngine/gpu/gpu_texture.h>
#include <UnitsEngine/gpu/gpu_sampler.h>

namespace editor {
  class EditorLayer final : public units::ILayer {
  public:
    EditorLayer() noexcept;
    virtual ~EditorLayer() noexcept override;

    virtual void onAttatch() noexcept override;
    virtual void onDetatch() noexcept override;

    virtual void onFixedTick() noexcept override;
    virtual void onTick() noexcept override;
    virtual void onImGui() noexcept override;
    virtual void onRender() noexcept override;
  private:
    units::Window m_window_;
    units::GPUDevice m_gpu_device_;
    units::GPUTexture m_gpu_texture_;

    void showSceneWindow() noexcept;
    void showSceneResolutionWindow() noexcept;
  };
} // namespace editor