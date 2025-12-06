#include "UnitsEngine/gpu/gpu_graphics_pipeline.h"

#include <SDL3/SDL.h>

#include "UnitsEngine/core/log.h"
#include "UnitsEngine/core/assert.h"

namespace units {
  GPUGraphicsPipeline::GPUGraphicsPipeline(GPUDevice& p_gpu_device, const GPUGraphicsPipelineSpecs& p_specs) noexcept {
    if (p_gpu_device.expired()) { return; }
    m_gpu_device_ptr_= p_gpu_device.getGPUDevicePtr();
    auto* sdl_gpu_device_ptr= reinterpret_cast<SDL_GPUDevice*>(m_gpu_device_ptr_);

    SDL_GPUGraphicsPipelineCreateInfo sdl_gpu_graphics_pipeline_create_info= {
      .vertex_shader= reinterpret_cast<SDL_GPUShader*>(p_specs.vertex_shader_ptr->getGPUShaderPtr()),
      .fragment_shader= reinterpret_cast<SDL_GPUShader*>(p_specs.fragment_shader_ptr->getGPUShaderPtr()),
      .vertex_input_state= {},
      .primitive_type= SDL_GPU_PRIMITIVETYPE_TRIANGLELIST,
      .rasterizer_state= {
        .fill_mode= !p_specs.wireframe_mode ? SDL_GPU_FILLMODE_FILL : SDL_GPU_FILLMODE_LINE,
        .cull_mode= SDL_GPU_CULLMODE_NONE,
        .front_face= SDL_GPU_FRONTFACE_CLOCKWISE,
        .depth_bias_constant_factor= 0.0f,
        .depth_bias_clamp= 0.0f,
        .depth_bias_slope_factor= 1.0f,
        .enable_depth_bias= false,
        .enable_depth_clip= false
      },
      .multisample_state= {},
      .depth_stencil_state= {},
      .target_info= SDL_GPUGraphicsPipelineTargetInfo{
        .color_target_descriptions= (SDL_GPUColorTargetDescription[]){{
          .format= static_cast<SDL_GPUTextureFormat>(p_specs.texture_format),
          .blend_state= SDL_GPUColorTargetBlendState{
            .src_color_blendfactor= SDL_GPU_BLENDFACTOR_SRC_ALPHA,
            .dst_color_blendfactor= SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
            .color_blend_op= SDL_GPU_BLENDOP_ADD,
            .src_alpha_blendfactor= SDL_GPU_BLENDFACTOR_SRC_ALPHA,
            .dst_alpha_blendfactor= SDL_GPU_BLENDFACTOR_ONE_MINUS_SRC_ALPHA,
            .alpha_blend_op= SDL_GPU_BLENDOP_ADD,
            .color_write_mask= 0,
            .enable_blend= true,
            .enable_color_write_mask= false
          }
        }},
        .num_color_targets= 1,
        .depth_stencil_format= SDL_GPU_TEXTUREFORMAT_D16_UNORM,
        .has_depth_stencil_target= false
      }
    };

    m_gpu_graphics_pipeline_ptr_= reinterpret_cast<void*>(SDL_CreateGPUGraphicsPipeline(
      sdl_gpu_device_ptr,
      &sdl_gpu_graphics_pipeline_create_info
    ));
    if (m_gpu_graphics_pipeline_ptr_ == nullptr) {
      UE_CORE_ERROR("SDL error: {0}", SDL_GetError());
      UE_CORE_ASSERT(false, "Could not create GPUGraphicsPipeline!");
    }
  }

  void GPUGraphicsPipeline::destroy() noexcept {
    if (!expired()) {
      SDL_ReleaseGPUGraphicsPipeline(reinterpret_cast<SDL_GPUDevice*>(m_gpu_device_ptr_), reinterpret_cast<SDL_GPUGraphicsPipeline*>(m_gpu_graphics_pipeline_ptr_));
      m_gpu_graphics_pipeline_ptr_= nullptr;
    }
  }

  bool GPUGraphicsPipeline::bindToRenderPass(GPURenderPass& p_gpu_render_pass) noexcept {
    if (expired() || p_gpu_render_pass.expired()) { return false; }
    SDL_BindGPUGraphicsPipeline(reinterpret_cast<SDL_GPURenderPass*>(p_gpu_render_pass.getGPURenderPassPtr()), reinterpret_cast<SDL_GPUGraphicsPipeline*>(m_gpu_graphics_pipeline_ptr_));
    return true;
  }
} // namespace units