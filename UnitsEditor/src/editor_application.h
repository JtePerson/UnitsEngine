#pragma once
#include <UnitsEngine/application.h>
#include <UnitsEngine/event/event.h>
#include <UnitsEngine/gpu/gpu_texture.h>
#include <UnitsEngine/gpu/gpu_sampler.h>
#include <UnitsEngine/gpu/gpu_texture_sampler_binding.h>

namespace Editor {
  class Application final : public Units::IApplication {
  public:
    Application() noexcept;
    virtual ~Application() noexcept override;

    Units::GPUTexture m_gpu_texture_;
    Units::GPUSampler m_gpu_sampler_;
    Units::GPUTextureSamplerBinding m_gpu_texture_sampler_binding_;

    virtual void onEvent(Units::IEvent& p_event) noexcept override;
    virtual void onTick() noexcept override;
    virtual void onImGui() noexcept override;
    virtual void onRender() noexcept override;
  private:
  };
} // namespace Editor