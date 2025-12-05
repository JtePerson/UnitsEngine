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

    virtual bool onEvent(units::Event& p_event, const void*& p_data_ptr) noexcept override { return true; }
    virtual bool onFixedTick() noexcept override { return true; }
    virtual bool onTick() noexcept override { return true; }
    virtual bool onImGui() noexcept override { return true; }
    virtual void onRender() noexcept override;
  private:
  };
} // namespace game