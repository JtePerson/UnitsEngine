#pragma once
#include "UnitsEngine/platform_defines.h"

#if defined(UE_DEBUG)
  #if defined(UE_PLATFORM_WIN32) || defined(UE_PLATFORM_WIN64)
  	#define UE_DEBUG_BREAK() __debugbreak()
  #else
  	#define UE_DEBUG_BREAK()
  #endif
#endif