#include <cstdio>

#include <UnitsEngine/memory/memory.h>

int main(int p_argc, char* p_argv[]) {
  printf("Page size: %zu, Allocation granularity: %zu\n", units::Memory::getPageSize(), units::Memory::getAlloctionGranularity());
  units::Memory::VirtualRegion v_region{1u};
  v_region.commit(1u);
  *(int*)v_region.get()= -100;
  printf("Region size: %zu\n", v_region.size());
  printf("Region int value: %i\n", *(int*)v_region.get());
  return 0;
}