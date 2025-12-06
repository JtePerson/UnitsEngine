#pragma once
#include "UnitsEngine/core/engine_api.h"
#include "UnitsEngine/gpu/gpu_device.h"
#include "UnitsEngine/gpu/gpu_graphics_pipeline_specs.h"
#include "UnitsEngine/gpu/gpu_render_pass.h"

namespace units {
  class UE_API GPUGraphicsPipeline final {
  public:
    inline GPUGraphicsPipeline() noexcept= default;
    GPUGraphicsPipeline(GPUDevice& p_gpu_device, const GPUGraphicsPipelineSpecs& p_specs) noexcept;
    inline GPUGraphicsPipeline(GPUGraphicsPipeline&& p_other) noexcept {
      *this= p_other;
      p_other.m_gpu_graphics_pipeline_ptr_= nullptr;
    }
    inline GPUGraphicsPipeline& operator=(GPUGraphicsPipeline&& p_other) noexcept {
      *this= p_other;
      p_other.m_gpu_graphics_pipeline_ptr_= nullptr;
      return *this;
    }
    inline ~GPUGraphicsPipeline() noexcept { destroy(); }

    inline bool expired() noexcept { return m_gpu_graphics_pipeline_ptr_ == nullptr; }

    void destroy() noexcept;

    bool bindToRenderPass(GPURenderPass& p_gpu_render_pass) noexcept;

    inline void* getGPUGraphicsPipelinePtr() noexcept { return m_gpu_graphics_pipeline_ptr_; }
  private:
    inline GPUGraphicsPipeline(const GPUGraphicsPipeline&) noexcept= default;
    inline GPUGraphicsPipeline& operator=(const GPUGraphicsPipeline&) noexcept= default;

    void* m_gpu_graphics_pipeline_ptr_= nullptr;
    void* m_gpu_device_ptr_= nullptr;
  };
} // namespace units