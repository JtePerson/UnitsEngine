#pragma once
#include "UnitsEngine/core/log.h"
#include "UnitsEngine/core/application.h"

int main(int p_argc, char** p_argv) {
  UE_LOG_INIT();

  auto* application= Units::Application::getInstance();
  application->run();
  return 0;
}