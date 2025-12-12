#include "UnitsEngine/inputs.h"

#include <SDL3/SDL.h>

#include "UnitsEngine/engine.h"
#include "UnitsEngine/events.h"

namespace units {
  void Inputs::getInputs(Events::EventDispatcher* p_event_dispatcher_ptr) noexcept {
    SDL_Event sdl_event;
    SDL_zero(sdl_event);
    while (SDL_PollEvent(&sdl_event)) {
      if (sdl_event.type == SDL_EVENT_QUIT) {
        Engine::quit();
      }
    }
  }
} // namespace units
