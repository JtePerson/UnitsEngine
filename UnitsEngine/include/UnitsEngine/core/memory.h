#pragma once
#include <cstdlib>
#include <iostream>

#include "UnitsEngine/core/debug.h"
#include "UnitsEngine/core/platform_defines.h"

#if defined(UE_PLATFORM_WIN64)
#  include <Windows.h>
#else
#endif

namespace units {
  struct Memory final {
    Memory()= delete;
    ~Memory()= delete;

    enum class AccessMode {
      READ,
      WRITE,
    };

    static inline size_t pageSize() noexcept {
      static const size_t page_size= []() -> size_t {
#if defined(UE_PLATFORM_WIN64)
        SYSTEM_INFO system_info;
        GetSystemInfo(&system_info);
        return system_info.dwAllocationGranularity;
#else
        return ~(0ull);
#endif
      }();
      return page_size;
    }

    static inline size_t pageAlign(const size_t& p_offset) noexcept {
      const size_t page_size= pageSize();
      return (p_offset / page_size) * page_size;
    }

    static inline void* pageAlloc() noexcept {
#if defined(UE_PLATFORM_WIN64)
      void* page_ptr= VirtualAlloc(nullptr, pageSize(), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
#endif
    }
  };
} // namespace units