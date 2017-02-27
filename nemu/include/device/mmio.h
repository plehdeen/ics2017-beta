#ifndef __MMIO_H__
#define __MMIO_H__

#include "common.h"

typedef void(*mmio_callback_t)(hwaddr_t, int, bool);

void* add_mmio_map(hwaddr_t, int, mmio_callback_t);
int is_mmio(hwaddr_t);

uint32_t mmio_read(hwaddr_t, int, int);
void mmio_write(hwaddr_t, int, uint32_t, int);

#endif
