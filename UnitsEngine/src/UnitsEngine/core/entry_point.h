#pragma once
#include "UnitsEngine/core/log.h"
#include "UnitsEngine/core/application.h"

int main(int p_argc, char** p_argv) {
  UE_LOG_INIT();

  auto* application= Units::Application::getInstance();
  if (application == nullptr) {
    UE_CORE_CRITICAL("Application could not be created!");
    return 0;
  }
  application->run();
  delete Units::Application::getInstance();
  return 0;
}