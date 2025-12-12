#pragma once

#if defined(_WIN32) && defined(_WIN64)
#  define UE_PLATFORM_WIN64
#else
#  error "UnitsEngine only supports Win64 at the moment
#endif