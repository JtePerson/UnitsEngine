module;

#include <stdint.h>

module units.Memory;

namespace units {
  Memory::Allocator* Memory::Allocator::s_instance_ptr_= nullptr;

  uint32_t Memory::Allocator::init(const uint32_t& p_size, byte_t* p_ptr) noexcept {
    static const uint32_t size= alignUpToAllocationGranularity(p_size);
    static Allocator instance{size, p_ptr};
    if (s_instance_ptr_ != nullptr || instance.m_virtual_region_ == nullptr)
      return 0u;
    s_instance_ptr_= &instance;
    return size;
  }
  void Memory::Allocator::quit() noexcept {
    if (s_instance_ptr_ == nullptr)
      return;
    s_instance_ptr_->m_virtual_region_.~VirtualRegion();
    s_instance_ptr_= nullptr;
  }

  Memory::Allocator::Allocator(const uint32_t& p_size, byte_t* p_ptr) noexcept {
    m_virtual_region_= VirtualRegion{p_size / static_cast<uint32_t>(getAlloctionGranularity()), p_ptr};
  }
  Memory::Allocator::~Allocator() noexcept {
  }

  Memory::Allocator::MemoryBlock Memory::Allocator::request(const uint32_t& p_size) noexcept {
    if (s_instance_ptr_ == nullptr || p_size > space())
      return MemoryBlock{
        .ptr= nullptr,
        .size= space(),
      };
    const uint32_t page_start= alignDownToPageSize(s_instance_ptr_->m_next_byte_) / getPageSize();
    const uint32_t page_count= alignUpToPageSize(s_instance_ptr_->m_next_byte_ + p_size) / getPageSize();
    s_instance_ptr_->m_virtual_region_.commit(page_count, page_start);
    byte_t* byte_ptr= s_instance_ptr_->m_virtual_region_.get() + s_instance_ptr_->m_next_byte_;
    *(MetaData*)byte_ptr= MetaData{
      .index= s_instance_ptr_->m_meta_data_count_++,
      .size= p_size,
    };
    s_instance_ptr_->m_next_byte_+= static_cast<uint32_t>(sizeof(MetaData));
    return MemoryBlock{
      .ptr= byte_ptr + sizeof(MetaData),
      .size= p_size,
    };
  }
} // namespace units