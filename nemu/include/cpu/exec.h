#ifndef __CPU_EXEC_H__
#define __CPU_EXEC_H__

#include "nemu.h"

#define make_EHelper(name) void concat(exec_, name) (swaddr_t *eip)
typedef void (*EHelper) (swaddr_t *);

#include "cpu/decode.h"

static inline uint32_t instr_fetch(swaddr_t *eip, int len) {
	uint32_t instr = swaddr_read(*eip, len);
#ifdef DEBUG
	uint8_t *p_instr = (void *)&instr;
	int i;
	for(i = 0; i < len; i ++) {
		decoding.p += sprintf(decoding.p, "%02x ", p_instr[i]);
	}
#endif
	(*eip) += len;
	return instr;
}

void rtl_setcc(rtlreg_t*, uint8_t);
extern char* cc_name[];

#ifdef DEBUG
#define print_asm(...) Assert(snprintf(decoding.assembly, 80, __VA_ARGS__) < 80, "buffer overflow!")
#else
#define print_asm(...)
#endif

#define suffix_char(len) ((len) == 4 ? 'l' : ((len) == 1 ? 'b' : ((len) == 2 ? 'w' : '?')))

#define print_asm_template1(instr) \
	print_asm(str(instr) "%c %s", suffix_char(id_dest->len), id_dest->str)

#define print_asm_template2(instr) \
	print_asm(str(instr) "%c %s,%s", suffix_char(id_dest->len), id_src->str, id_dest->str)

#define print_asm_template3(instr) \
	print_asm(str(instr) "%c %s,%s,%s", suffix_char(id_dest->len), id_src->str, id_src2->str, id_dest->str)

#endif
