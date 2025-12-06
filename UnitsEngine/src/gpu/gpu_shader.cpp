#include "UnitsEngine/gpu/gpu_shader.h"

#include <SDL3/SDL.h>

#include "UnitsEngine/core/log.h"
#include "UnitsEngine/core/assert.h"
#include "UnitsEngine/core/asset_loader.h"

namespace units {
  GPUShader::GPUShader(GPUDevice& p_gpu_device, const GPUShaderSpecs& p_specs) noexcept {
    if (p_gpu_device.expired()) { return; }
    m_gpu_device_ptr_= p_gpu_device.getGPUDevicePtr();
    auto* sdl_gpu_device_ptr= reinterpret_cast<SDL_GPUDevice*>(m_gpu_device_ptr_);

  	// Auto-detect the shader stage from the file name for convenience
  	SDL_GPUShaderStage stage;
  	if (SDL_strstr(p_specs.filepath.c_str(), ".vert")) {
  		stage = SDL_GPU_SHADERSTAGE_VERTEX;
  	} else if (SDL_strstr(p_specs.filepath.c_str(), ".frag")) {
  		stage = SDL_GPU_SHADERSTAGE_FRAGMENT;
  	} else {
      UE_CORE_ASSERT(false, "Invalid GPUShader stage!");
  	}

  	char full_path[256];
  	SDL_GPUShaderFormat backendFormats = SDL_GetGPUShaderFormats(sdl_gpu_device_ptr);
  	SDL_GPUShaderFormat format = SDL_GPU_SHADERFORMAT_INVALID;
  	const char *entrypoint;

    const char* base_path= AssetLoader::getAssetPath().c_str();
  	if (backendFormats & SDL_GPU_SHADERFORMAT_SPIRV) {
  		SDL_snprintf(full_path, sizeof(full_path), "%s/shaders/compiled/SPIRV/%s.spv", base_path, p_specs.filepath.c_str());
  		format = SDL_GPU_SHADERFORMAT_SPIRV;
  		entrypoint = "main";
  	} else if (backendFormats & SDL_GPU_SHADERFORMAT_MSL) {
  		SDL_snprintf(full_path, sizeof(full_path), "%s/shaders/compiled/MSL/%s.msl", base_path, p_specs.filepath.c_str());
  		format = SDL_GPU_SHADERFORMAT_MSL;
  		entrypoint = "main0";
  	} else if (backendFormats & SDL_GPU_SHADERFORMAT_DXIL) {
  		SDL_snprintf(full_path, sizeof(full_path), "%s/shaders/compiled/DXIL/%s.dxil", base_path, p_specs.filepath.c_str());
  		format = SDL_GPU_SHADERFORMAT_DXIL;
  		entrypoint = "main";
  	} else {
      UE_CORE_ASSERT(false, "Unrecognized GPUShader backend format!");
  	}

  	size_t code_size;
  	void* code = SDL_LoadFile(full_path, &code_size);
  	if (code == nullptr) {
      UE_CORE_ERROR("Could not load shader from disk [filepath: {0}]!", full_path);
      UE_CORE_ASSERT(false, "Could not create GPUShader");
  	}

  	SDL_GPUShaderCreateInfo sdl_gpu_shader_create_info = {
  		.code_size = code_size,
  		.code = reinterpret_cast<uint8_t*>(code),
  		.entrypoint = entrypoint,
  		.format = format,
  		.stage = stage,
  		.num_samplers = p_specs.sampler_count,
  		.num_storage_textures = p_specs.storage_texture_count,
  		.num_storage_buffers = p_specs.storage_buffer_count,
  		.num_uniform_buffers = p_specs.uniform_buffer_count
  	};
  	m_gpu_shader_ptr_ = SDL_CreateGPUShader(sdl_gpu_device_ptr, &sdl_gpu_shader_create_info);
  	if (m_gpu_shader_ptr_ == nullptr) {
  		SDL_free(code);
      UE_CORE_ERROR("SDL error: {0}", SDL_GetError());
      UE_CORE_ASSERT(false, "Could not create GPUShader!");
  	}

  	SDL_free(code);
  }

  void GPUShader::destroy() noexcept {
    if (!expired()) {
      SDL_ReleaseGPUShader(reinterpret_cast<SDL_GPUDevice*>(m_gpu_device_ptr_), reinterpret_cast<SDL_GPUShader*>(m_gpu_shader_ptr_));
      m_gpu_shader_ptr_= nullptr;
    }
  }
} // namespace units