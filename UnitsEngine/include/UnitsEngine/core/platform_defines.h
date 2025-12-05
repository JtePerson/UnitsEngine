#pragma once

#if defined(_WIN32)
  #if defined(_WIN64)
    #define UE_PLATFORM_WIN64 1
  #else
    #define UE_PLATFORM_WIN32 1
  #endif
#elif defined(__APPLE__)
  #if defined(__MACH__)
    #include <TargetConditionals.h>
    #define UE_PLATFORM_APPLE 1
    #if defined(TARGET_OS_IOS)
      #define UE_PLATFORM_APPLE_IOS 1
     #elif defined(TARGET_OS_TV)
      #define UE_PLATFORM_APPLE_TV 1
     #elif defined(TARGET_OS_WATCH)
      #define UE_PLATFORM_APPLE_WATCH 1
     #elif defined(TARGET_OS_SIMULATOR)
      #define UE_PLATFORM_APPLE_SIMULATOR 1
     #elif (TARGET_OS_MAC)
      #define UE_PLATFORM_APPLE_MACOS 1
    #endif
  #else
    #error "Unknown Apple Platform!"
  #endif
#elif defined(__linux__)
  #define UE_PLATFORM_LINUX 1
#elif defined(__unix__)
  #define UE_PLATFORM_UNIX 1
#elif defined(__FreeBSD__)
  #define UE_PLATFORM_FREEBSD 1
#elif defined(__ANDROID__)
  #define UE_PLATFORM_ANDROID 1
#else
  #error "Unknown Platform!"
#endif