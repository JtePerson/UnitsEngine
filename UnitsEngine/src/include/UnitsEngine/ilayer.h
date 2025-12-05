#pragma once
#include <functional>

#include "UnitsEngine/gpu/gpu_texture.h"
#include "UnitsEngine/event/event.h"
#include "UnitsEngine/event/event_dispatcher.h"
#include "UnitsEngine/iapplication.h"

namespace units {
  class ILayer {
  public:
    virtual inline ~ILayer() noexcept= default;

    virtual void onAttatch() noexcept= 0;
    virtual void onDetatch() noexcept= 0;

    virtual bool onEvent(Event& p_event, const void*& p_data) noexcept= 0;
    virtual bool onFixedTick() noexcept= 0;
    virtual bool onTick() noexcept= 0;
    virtual bool onImGui() noexcept= 0;
    virtual void onRender() noexcept= 0;

    template<typename EventT>
    inline void pushEvent(const EventT& p_event) noexcept {
      IApplication::getInstance<IApplication>()->pushEvent(p_event);
    }
    template<typename CallableT>
    inline void registerEventListener(CallableT&& p_listener) noexcept {
      m_event_dispatcher_.registerListener(std::forward<CallableT>(p_listener));
    }
    template<typename EventT>
    inline void dispatchEvent(Event& p_event, const EventT* p_data_ptr) noexcept {
      m_event_dispatcher_.dispatch(p_event, reinterpret_cast<const void*>(p_data_ptr));
    }

    inline GPUTexture* getGPUTexture(GPUCommandBuffer* p_gpu_command_buffer_ptr= nullptr) noexcept {
      return m_get_gpu_texture_callback(p_gpu_command_buffer_ptr);
    }
    template<typename CallableT>
    inline void setGPUTextureCallback(CallableT&& p_callable) noexcept {
      m_get_gpu_texture_callback= p_callable;
    }
  protected:
    inline ILayer() noexcept= default;
  private:
    EventDispatcher m_event_dispatcher_;
    
    std::function<GPUTexture*(GPUCommandBuffer*)> m_get_gpu_texture_callback= [](GPUCommandBuffer*)->GPUTexture* { return nullptr; };
  };
} // namespace units