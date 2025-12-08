#pragma once
#include "UnitsEngine/core/engine_api.h"

namespace units {
class UE_API Engine final {
 public:
  using CallbackT = void (*)();

 public:
  static bool load(int p_argc, char* p_argv[]);
  static void unload();

  static bool run(const CallbackT& p_init_callback = nullptr,
                  const CallbackT& p_quit_callback = nullptr);

 private:
  Engine() = delete;
  ~Engine() = delete;
};
}  // namespace units