#pragma once
#include "UnitsEngine/core/engine_api.h"
#include "UnitsEngine/gpu/gpu_command_buffer.h"
#include "UnitsEngine/gpu/gpu_render_pass_specs.h"

namespace units {
  class UE_API GPURenderPass final {
  public:
    inline GPURenderPass() noexcept= default;
    GPURenderPass(GPUCommandBuffer& p_pipeline, GPURenderPassSpecs& p_specs) noexcept;
    inline GPURenderPass(GPURenderPass&& p_gpu_render_pass) noexcept {
      *this= p_gpu_render_pass;
      p_gpu_render_pass.m_gpu_render_pass_ptr_= nullptr;
    }
    inline GPURenderPass& operator=(GPURenderPass&& p_gpu_render_pass) noexcept {
      *this= p_gpu_render_pass;
      p_gpu_render_pass.m_gpu_render_pass_ptr_= nullptr;
      return *this;
    }
    inline ~GPURenderPass() noexcept { destroy(); }

    inline bool expired() noexcept { return m_gpu_render_pass_ptr_ == nullptr; }

    void destroy() noexcept;
    
    inline void* getGPURenderPassPtr() noexcept { return m_gpu_render_pass_ptr_; }
  private:
    inline GPURenderPass(const GPURenderPass&) noexcept= default;
    inline GPURenderPass& operator=(const GPURenderPass&) noexcept= default;

    void* m_gpu_render_pass_ptr_= nullptr;
  };
} // namespace units