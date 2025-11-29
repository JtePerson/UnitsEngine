#pragma once
#include "UnitsEngine/platform_defines.h"

#if defined(UE_PLATFORM_WIN632) || defined(UE_PLATFORM_WIN64)
  #if defined(UE_BUILD_ENGINE)
    #define UE_API __declspec(dllexport)
  #else
    #define UE_API __declspec(dllimport)
  #endif
#elif defined(UE_PLATFORM_APPLE) || defined(UE_PLATFORM_LINUX)
  #if defined(UE_BUILD_ENGINE)
    #define UE_API __attribute__((visibility("default")))
  #else
    #define UE_API
  #endif
#else
  #define UE_API
#endif