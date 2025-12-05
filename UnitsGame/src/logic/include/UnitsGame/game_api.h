#pragma once
#include "UnitsEngine/core/platform_defines.h"

#if defined(UE_PLATFORM_WIN632) || defined(UE_PLATFORM_WIN64)
  #if defined(GAME_BUILD_DLL)
    #define GAME_API __declspec(dllexport)
  #else
    #define GAME_API __declspec(dllimport)
  #endif
#elif defined(UE_PLATFORM_APPLE) || defined(UE_PLATFORM_LINUX)
  #if defined(GAME_BUILD_DLL)
    #define GAME_API __attribute__((visibility("default")))
  #else
    #define GAME_API
  #endif
#else
  #define GAME_API
#endif