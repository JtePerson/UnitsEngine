#pragma once
#include "UnitsEngine/core/platform_defines.h"

#if defined(UE_PLATFORM_WIN64)
#if defined(UE_BUILD_ENGINE_DLL)
#define UE_API __declspec(dllexport)
#endif
#define UE_API _declspec(dllimport)
#else
#define UE_API
#endif