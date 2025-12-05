#include "test_application.h"

int main(int p_argc, char** p_argv) {
  test::TestApplication test_application{};
  test_application.run();
  return 0;
}