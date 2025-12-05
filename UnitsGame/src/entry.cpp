#include "game_application.h"

int main(int p_argc, char** p_argv) {
  game::Application game_application{};
  game_application.run();
  return 0;
}