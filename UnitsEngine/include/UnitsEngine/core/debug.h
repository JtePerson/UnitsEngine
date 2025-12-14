#pragma once
#include "UnitsEngine/core/platform_defines.h"

#if defined(UE_BUILD_DEBUG)
#  if defined(UE_PLATFORM_WIN64)
#    define UE_DEBUG_BREAK() __debugbreak()
#  endif
#else
#  define UE_DEBUG_BREAK()
#endif