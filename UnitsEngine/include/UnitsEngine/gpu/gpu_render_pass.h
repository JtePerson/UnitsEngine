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

    void setGPUViewport(const float32_t& p_x, const float32_t& p_y, const float32_t& p_w, const float32_t& p_h, const float32_t& p_min_depth, const float32_t& p_max_depth) noexcept;
    void setGPUScissor(const int& p_x, const int& p_y, const int& p_w, const int& p_h) noexcept;

    void drawGPUPrimitives(const uint32_t& p_vertex_count, const uint32_t& p_instance_count, const uint32_t& p_first_vertex, const uint32_t& p_first_instance) noexcept;
    
    inline void* getGPURenderPassPtr() noexcept { return m_gpu_render_pass_ptr_; }
  private:
    inline GPURenderPass(const GPURenderPass&) noexcept= default;
    inline GPURenderPass& operator=(const GPURenderPass&) noexcept= default;

    void* m_gpu_render_pass_ptr_= nullptr;
  };
} // namespace units