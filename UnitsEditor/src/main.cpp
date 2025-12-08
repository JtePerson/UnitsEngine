#include <UnitsEngine/core/log.h>
#include <UnitsEngine/core/macros.h>
#include <UnitsEngine/engine.h>

#include "UnitsEditor/project_loader.h"

struct Editor final {
  static void init() noexcept {
    UE_CORE_TRACE("Init Editor");
    std::unique_ptr<editor::Project>& units_project =
        editor::ProjectLoader::loadProject("./");
    UE_CORE_TRACE("Project name: {0}", units_project->name);
  }
  static void quit() noexcept { UE_CORE_TRACE("Quit Editor"); }
};

int main(int p_argc, char* p_argv[]) {
  units::Engine::load(p_argc, p_argv);
  units::Engine::run(&Editor::init, &Editor::quit);
  units::Engine::unload();
  return 0;
}