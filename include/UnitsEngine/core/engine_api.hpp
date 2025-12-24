#pragma once
#include "UnitsEngine/core/platform_defines.hpp"

#if defined(UE_PLATFORM_WIN64)
#  if defined(UE_BUILD_DLL)
#    define UE_API __declspec(dllexport)
#  else
#    define UE_API _declspec(dllimport)
#  endif
#else
#  define UE_API
#endif