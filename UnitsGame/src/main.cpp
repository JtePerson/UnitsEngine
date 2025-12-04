#include <UnitsEngine/iapplication.h>
#include <UnitsEngine/core/log.h>

#include "UnitsGame/game_layer.h"

class Application final : public units::IApplication {
public:
  inline Application() noexcept
  : IApplication{this}
  {
    UE_WARN("Initializing Game");
    UE_INFO("Game Initialized");
  }
  inline virtual ~Application() noexcept override {
    UE_WARN("Quitting Game");
    UE_INFO("Game Quit");
  }

  inline virtual void onRun() noexcept override {
    UE_TRACE("Run Game");
    attatchLayer<game::GameLayer>(0);
    getLayer<game::GameLayer>(0);
  }
  inline virtual void onQuit() noexcept override {
    UE_TRACE("Quit Game");
  }

  static inline Application* getInstance() noexcept { return IApplication::getInstance<Application>(); }
private:
  game::GameLayer* m_game_layer_ptr_= nullptr;
};

int main(int p_argc, char** p_argv) {
  Application game_application{};
  game_application.run();
  return 0;
}