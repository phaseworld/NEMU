#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "common.h"

#define PMEM_SIZE (128 * 1024 * 1024)
extern uint8_t pmem[];

/* convert the guest physical address in the guest program to host virtual address in NEMU */
#define guest_to_host(p) ((void *)(pmem + (unsigned)p))
/* convert the host virtual address in NEMU to guest physical address in the guest program */
#define host_to_guest(p) ((paddr_t)((void *)p - (void *)pmem))

uint32_t vaddr_read(vaddr_t, int);
uint32_t paddr_read(paddr_t, int);
void vaddr_write(vaddr_t, uint32_t, int);
void paddr_write(paddr_t, uint32_t, int);

#define PAGE_SIZE         4096
#define PAGE_MASK         (PAGE_SIZE - 1)
#define PG_ALIGN __attribute((aligned(PAGE_SIZE)))

#endif
