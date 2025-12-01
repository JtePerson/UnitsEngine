#include "editor_layer.h"

#include <UnitsEngine/iapplication.h>
#include <UnitsEngine/core/log.h>

namespace Editor {
  EditorLayer::EditorLayer() noexcept {
  }
  EditorLayer::~EditorLayer() noexcept {}

  void EditorLayer::onAttatch() noexcept {
    UE_TRACE("EditorLayer attatched");
  }
  void EditorLayer::onDetatch() noexcept {
    UE_TRACE("EditorLayer detatched");
  }

  void EditorLayer::onEvent() noexcept {}
  void EditorLayer::onFixedTick() noexcept {}
  void EditorLayer::onTick() noexcept {
    UE_TRACE("EditorLayer ticked");
  }
  void EditorLayer::onImGui() noexcept {}
  void EditorLayer::onRender() noexcept {}
} // namespace Editor