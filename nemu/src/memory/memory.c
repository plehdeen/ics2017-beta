#include "nemu.h"

uint32_t dram_read(hwaddr_t, int);
void dram_write(hwaddr_t, int, uint32_t);

/* Memory accessing interfaces */

uint32_t hwaddr_read(hwaddr_t addr, int len) {
#ifdef ENABLE_DDR3
	return dram_read(addr, len) & (~0u >> ((4 - len) << 3));
#else
	return hw_rw(addr, uint32_t) & (~0u >> ((4 - len) << 3));
#endif
}

void hwaddr_write(hwaddr_t addr, int len, uint32_t data) {
#ifdef ENABLE_DDR3
	dram_write(addr, len, data);
#else
	memcpy(hwa_to_va(addr), &data, len);
#endif
}

uint32_t lnaddr_read(lnaddr_t addr, int len) {
	return hwaddr_read(addr, len);
}

void lnaddr_write(lnaddr_t addr, int len, uint32_t data) {
	hwaddr_write(addr, len, data);
}

uint32_t swaddr_read(swaddr_t addr, int len) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	return lnaddr_read(addr, len);
}

void swaddr_write(swaddr_t addr, int len, uint32_t data) {
#ifdef DEBUG
	assert(len == 1 || len == 2 || len == 4);
#endif
	lnaddr_write(addr, len, data);
}
