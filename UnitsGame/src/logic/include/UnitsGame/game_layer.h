#pragma once
#include <UnitsEngine/ilayer.h>
#include <UnitsEngine/gpu/gpu_texture.h>

#include "game_api.h"

namespace game {
  class GAME_API GameLayer final : public units::ILayer {
  public:
    GameLayer() noexcept;
    virtual ~GameLayer() noexcept override;

    virtual void onAttatch() noexcept override;
    virtual void onDetatch() noexcept override;

    virtual void onFixedTick() noexcept override;
    virtual void onTick() noexcept override;
    virtual void onImGui() noexcept override {}
    virtual void onRender() noexcept override;
  private:
  };
} // namespace game