#pragma once

#if defined(_WIN32)
#  if defined(_WIN64)
#    define UE_PLATFORM_WIN64
#  else
#    define UE_PLATFORM_WIN32
#  endif
#else
#  error "UnitsEngine only supports Win64 at the moment
#endif