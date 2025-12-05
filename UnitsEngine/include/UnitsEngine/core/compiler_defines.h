#pragma once

#if defined(__GNUC__)
  #define UE_COMPILER "GCC"
  #define UE_COMPILER_VERSION __GNUC__
#elif defined(__clang__)
  #define UE_COMPILER "Clang"
  #define UE_COMPILER_VERSION __clang_major__
#elif defined(_MSC_VER)
  #define UE_COMPILER "MSVC"
  #define UE_COMPILER_VERSION _MSC_VER
#else
  #error "Unkown Compiler and Compiler Version"
#endif