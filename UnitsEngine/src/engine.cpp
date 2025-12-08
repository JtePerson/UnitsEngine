#include "UnitsEngine/engine.h"

#include "UnitsEngine/core/log.h"

namespace units {
bool Engine::load(int p_Argc, char* p_argv[]) {
  UE_INIT_LOG();
  return true;
}
void Engine::unload() {}

bool Engine::run(const CallbackT& p_init_callback,
                 const CallbackT& p_quit_callback) {
  if (p_init_callback != nullptr) p_init_callback();
  if (p_quit_callback != nullptr) p_quit_callback();
  return true;
}
}  // namespace units