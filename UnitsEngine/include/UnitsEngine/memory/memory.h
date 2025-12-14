#pragma once
#include <cstddef>
#include <cstdint>

#include "UnitsEngine/core/platform_defines.h"

namespace units {
  struct Memory final {
    using byte_t= unsigned char;

    Memory()= delete;
    Memory(Memory&&)= delete;
    Memory(const Memory&)= delete;
    Memory& operator=(Memory&&)= delete;
    Memory& operator=(const Memory&)= delete;
    ~Memory()= delete;

    /*
     * returns OS memory Page Size
     */
    static inline size_t getPageSize() noexcept;
    /*
     * returns OS memory Allocation Granularity or Page Size if not supported
     */
    static inline size_t getAlloctionGranularity() noexcept;
    /*
     * returns p_offset rounded down to nearest Page Size
     */
    static inline size_t alignDownToPageSize(const size_t& p_offset) noexcept;
    /*
     * returns p_offset rounded down to nearest Allocation Granularity
     */
    static inline size_t alignDownToAllocationGranularity(const size_t& p_offset) noexcept;
    /*
     * returns p_offset rounded up to nearest Page Size
     */
    static inline size_t alignUpToPageSize(const size_t& p_offset) noexcept {
      const size_t offset= alignDownToPageSize(p_offset);
      return offset == p_offset ? offset : offset + getPageSize();
    }
    /*
     * returns p_offset rounded up to nearest Allocation Granularity
     */
    static inline size_t alignUpToAllocationGranularity(const size_t& p_offset) noexcept {
      const size_t offset= alignDownToAllocationGranularity(p_offset);
      return offset == p_offset ? offset : offset + getAlloctionGranularity();
    }

    class VirtualRegion final {
     public:
      inline VirtualRegion() noexcept= default;

      /*
       * p_size is in multiples of Allocation Granularity
       * p_ptr is rounded down to nearest Allocation Granularity
       * if p_ptr is nullptr or p_ptr is not available, receives pointer to an available address
       * receives nullptr on failure
       */
      inline VirtualRegion(const uint32_t& p_size, byte_t* p_ptr= nullptr) noexcept;

      inline VirtualRegion(VirtualRegion&& p_other) noexcept {
        *this= p_other;
        p_other.m_ptr_= nullptr;
        p_other.m_size_= 0u;
      }
      inline VirtualRegion& operator=(VirtualRegion&& p_other) noexcept {
        *this= p_other;
        p_other.m_ptr_= nullptr;
        p_other.m_size_= 0u;
        return *this;
      }
      inline ~VirtualRegion() noexcept;

      /*
       * p_size is in multiples of Page Size
       * p_offset is in multiples of Page Size
       */
      inline void commit(const uint32_t& p_size, uint32_t p_offset= 0u) const noexcept;
      /*
       * p_offset is in multiples of Page Size
       */
      inline byte_t* get(const uint32_t& p_offset= 0u) noexcept {
        if (m_ptr_ == nullptr)
          return nullptr;
        return m_ptr_ + p_offset;
      }
      /*
       * returns size in bytes of virtual region
       */
      inline size_t size() const noexcept { return m_size_; }

      inline operator void*() const noexcept { return m_ptr_; }
      inline operator byte_t*() const noexcept { return m_ptr_; }
      inline bool operator==(const nullptr_t&) const noexcept { return m_ptr_ == nullptr; }
      inline operator bool() const noexcept { return m_ptr_ != nullptr; }

     private:
      inline VirtualRegion(const VirtualRegion&) noexcept= default;
      inline VirtualRegion& operator=(const VirtualRegion&) noexcept= default;

      size_t m_size_= 0u;
      byte_t* m_ptr_= nullptr;
    };
  };
} // namespace units

#if defined(UE_PLATFORM_WIN32) || defined(UE_PLATFORM_WIN64)
#  include "UnitsEngine/memory/impl/memory_win32.ipp"
#elif defined(UE_PLATFORM_MACOS)
#  include "UnitsEngine/memory/impl/memory_macOS.ipp"
#endif