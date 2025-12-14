#pragma once
#include "UnitsEngine/core/platform_defines.h"
#include "UnitsEngine/memory/memory.h"

#if defined(UE_PLATFORM_MACOS)
#  include <mach/host_info.h>
#  include <mach/mach.h>
#  include <sys/mman.h>

namespace units {
  size_t Memory::getPageSize() noexcept {
    static size_t page_size= []() -> size_t {
      vm_size_t page_size;
      host_page_size(mach_host_self(), &page_size);
      return page_size;
    }();
    return page_size;
  }
  size_t Memory::getAlloctionGranularity() noexcept {
    static size_t allocation_granularity= []() -> size_t {
      return getPageSize();
    }();
    return allocation_granularity;
  }
  size_t Memory::alignDownToPageSize(const size_t& p_offset) noexcept {
    const size_t page_size= getPageSize();
    return (p_offset / page_size) * page_size;
  }
  size_t Memory::alignDownToAllocationGranularity(const size_t& p_offset) noexcept {
    const size_t allocation_granularity= getAlloctionGranularity();
    return (p_offset / allocation_granularity) * allocation_granularity;
  }

  Memory::VirtualRegion::VirtualRegion(const uint32_t& p_size, byte_t* p_ptr) noexcept {
    m_size_= p_size * getAlloctionGranularity();
    const void* ptr= mmap((void*)alignDownToAllocationGranularity((size_t)p_ptr), m_size_, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0u);
    if (ptr != MAP_FAILED)
      m_ptr_= (byte_t*)ptr;
    else
      m_size_= 0u;
  }
  Memory::VirtualRegion::~VirtualRegion() noexcept {
    if (m_ptr_ != nullptr)
      munmap((void*)m_ptr_, m_size_);
  }

  void Memory::VirtualRegion::commit(const uint32_t& p_size, uint32_t p_offset) const noexcept {}
} // namespace units

#endif