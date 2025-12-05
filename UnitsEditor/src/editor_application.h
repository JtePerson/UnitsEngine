#pragma once
#include <UnitsEngine/iapplication.h>

namespace editor {
  class Application final : public units::IApplication {
  public:
    friend class EditorLayer;
  public:
    Application() noexcept;
    virtual ~Application() noexcept override;

    virtual void onRun() noexcept override;
    virtual void onQuit() noexcept override;

    static inline Application* getInstance() noexcept { return IApplication::getInstance<Application>(); }
  private:
    units::GPUTexture m_editor_gpu_texture_;
    units::GPUTexture m_game_gpu_texture_;
  };
} // namespace editor