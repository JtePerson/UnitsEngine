#include "editor_application.h"

int main(int p_argc, char** p_argv) {
  Editor::Application editor_application{};
  editor_application.run();
  return 0;
}