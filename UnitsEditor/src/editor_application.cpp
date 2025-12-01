#include "editor_application.h"

#include <UnitsEngine/iapplication.h>

#include "editor_layer.h"

namespace Editor {
  Application::Application() noexcept: Units::IApplication() {}
  Application::~Application() noexcept {}

  void Application::onRun() noexcept {
    attatchLayer<EditorLayer>(0);
  }
  void Application::onQuit() noexcept {}
} // namespace Editor