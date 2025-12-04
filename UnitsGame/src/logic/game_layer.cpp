#include "UnitsGame/game_layer.h"

#include <UnitsEngine/core/log.h>

namespace game {
  GameLayer::GameLayer() noexcept {}
  GameLayer::~GameLayer() noexcept {}

  void GameLayer::onAttatch() noexcept {
    UE_TRACE("GameLayer attatched");
  }
  void GameLayer::onDetatch() noexcept {
    UE_TRACE("GameLayer detatched");
  }

  void GameLayer::onFixedTick() noexcept {}
  void GameLayer::onTick() noexcept {}
  void GameLayer::onRender() noexcept {}
} // namespace game