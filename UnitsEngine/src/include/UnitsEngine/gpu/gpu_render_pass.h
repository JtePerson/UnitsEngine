#pragma once
#include "UnitsEngine/core/engine_api.h"
#include "UnitsEngine/window/window.h"
#include "UnitsEngine/gpu/gpu_command_buffer.h"

namespace Units {
  class UE_API GPURenderPass final {
  public:
    GPURenderPass(Window& p_window, GPUCommandBuffer& p_pipeline) noexcept;
    ~GPURenderPass() noexcept;
    
    inline void* getGPURenderPass() noexcept {
      return m_gpu_render_pass_ptr_;
    }
  private:
    void* m_gpu_render_pass_ptr_= nullptr;
  };
} // namespace Units