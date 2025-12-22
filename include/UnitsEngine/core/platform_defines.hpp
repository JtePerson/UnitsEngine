#pragma once

#if defined(_WIN32)
#  if defined(_WIN64)
#    define UE_PLATFORM_SUPPORTED 1
#    define UE_PLATFORM_WIN64 1
#  else
#    define UE_PLATFORM_SUPPORTED 1
#    define UE_PLATFORM_WIN32 1
#  endif
#elif defined(__APPLE__)
#  include <TargetConditionals.h>
#  if defined(TARGET_OS_MAC)
#    define UE_PLATFORM_SUPPORTED 1
#    define UE_PLATFORM_MACOS 1
#  endif
#else
#  define UE_PLATFORM_SUPPORTED 0
#endif

#if !defined(UE_PLATFORM_SUPPORTED) || !UE_PLATFORM_SUPPORTED
#  error "UnitsEngine only supports Win32 and macOS at the moment
#endif