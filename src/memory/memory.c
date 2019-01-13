#include "nemu.h"
#include "device/io.h"

#define pmem_rw(addr, type) *(type *)({\
    Assert(addr < PMEM_SIZE, "physical address(0x%08x) is out of bound", addr); \
    guest_to_host(addr); \
    })

uint8_t pmem[PMEM_SIZE] PG_ALIGN;

/* Memory accessing interfaces */

uint32_t paddr_read(paddr_t addr, int len) {
  int mmio_id = is_mmio(addr);
  if (mmio_id != -1) {
    return mmio_read(addr, len, mmio_id) & (~0u >> ((4 - len) << 3));
  }

  return pmem_rw(addr, uint32_t) & (~0u >> ((4 - len) << 3));
}

void paddr_write(paddr_t addr, uint32_t data, int len) {
  int mmio_id = is_mmio(addr);
  if (mmio_id != -1) {
    mmio_write(addr, len, data, mmio_id);
    return;
  }

  memcpy(guest_to_host(addr), &data, len);
}

uint32_t arch_vaddr_read(vaddr_t addr, int len);
void arch_vaddr_write(vaddr_t addr, uint32_t data, int len);

uint32_t vaddr_read(vaddr_t addr, int len) {
  return arch_vaddr_read(addr, len);
}

void vaddr_write(vaddr_t addr, uint32_t data, int len) {
  arch_vaddr_write(addr, data, len);
}
