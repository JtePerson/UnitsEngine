#pragma once

namespace units {
  class ILayer {
  public:
    virtual inline ~ILayer() noexcept= default;

    virtual void onAttatch() noexcept= 0;
    virtual void onDetatch() noexcept= 0;

    virtual void onFixedTick() noexcept= 0;
    virtual void onTick() noexcept= 0;
    virtual void onImGui() noexcept= 0;
    virtual void onRender() noexcept= 0;
  protected:
    inline ILayer() noexcept= default;
  };
} // namespace units