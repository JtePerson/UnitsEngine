#include "editor_application.h"

#include <UnitsEngine/iapplication.h>

#include "editor_layer.h"

namespace editor {
  Application::Application() noexcept: units::IApplication{this} {}
  Application::~Application() noexcept {}

  void Application::onRun() noexcept {
    attatchLayer<EditorLayer>(0);
  }
  void Application::onQuit() noexcept {}
} // namespace editor