#include "editor_layer.h"

#include <UnitsEngine/event/event.h>
#include <imgui/imgui.h>
#include <glm/vec2.hpp>
#include <UnitsEngine/application.h>
#include <UnitsEngine/core/log.h>

namespace Editor {
  EditorLayer::EditorLayer() noexcept {
  }
  EditorLayer::~EditorLayer() noexcept {}

  void EditorLayer::onAttatch() noexcept {}
  void EditorLayer::onDetatch() noexcept {}
  void EditorLayer::onEvent(Units::IEvent& p_event) noexcept {}
  bool EditorLayer::onTick() noexcept { return false; }
  bool EditorLayer::onImGui() noexcept {
    ImGui::DockSpaceOverViewport(ImGui::GetID("Editor Dockspace"), ImGui::GetMainViewport());
    showTestWindow();
    showAnotherTestWindow();
    return false;
  }

  void EditorLayer::showTestWindow() noexcept {
    ImGui::SetNextWindowSize({ 100.0f, 100.0f }, ImGuiCond_FirstUseEver);
    ImGui::Begin("Test Window");
    ImGui::End();
  }
  void EditorLayer::showAnotherTestWindow() noexcept {
    ImGui::SetNextWindowSize({ 100.0f, 100.0f }, ImGuiCond_FirstUseEver);
    ImGui::Begin("Another Test Window");
    ImGui::End();
  }
} // namespace Editor