#pragma once
#include <UnitsEngine/iapplication.h>

#include "UnitsGame/game_layer.h"

namespace game {
  class Application final : public units::IApplication {
  public:
    Application() noexcept;
    inline virtual ~Application() noexcept override {
      UE_WARN("Quitting Game");
      UE_INFO("Game Quit");
    }

    virtual void onRun() noexcept override;
    inline virtual void onQuit() noexcept override {
      UE_TRACE("Quit Game");
    }

    static inline Application* getInstance() noexcept { return IApplication::getInstance<Application>(); }
  private:
    game::GameLayer* m_game_layer_ptr_= nullptr;
    units::GPUTexture m_gpu_texture_;
  };
} // namespace game