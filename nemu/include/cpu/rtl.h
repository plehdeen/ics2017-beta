#ifndef __RTL_H__
#define __RTL_H__

#include "nemu.h"

extern rtlreg_t t0, t1, t2, t3;
extern const rtlreg_t tzero;

/* RTL basic instructions */

static inline void rtl_li(rtlreg_t* dest, uint32_t imm) {
	*dest = imm;
}

#define c_add(a, b) ((a) + (b))
#define c_sub(a, b) ((a) - (b))
#define c_and(a, b) ((a) & (b))
#define c_or(a, b)  ((a) | (b))
#define c_xor(a, b) ((a) ^ (b))
#define c_shl(a, b) ((a) << (b))
#define c_shr(a, b) ((a) >> (b))
#define c_sar(a, b) ((int32_t)(a) >> (b))
#define c_slt(a, b) ((int32_t)(a) < (int32_t)(b))
#define c_sltu(a, b) ((a) < (b))

#define make_rtl_arith_logic(name) \
	static inline void concat(rtl_, name) (rtlreg_t* dest, const rtlreg_t* src1, const rtlreg_t* src2) { \
		*dest = concat(c_, name) (*src1, *src2); \
	} \
	static inline void concat3(rtl_, name, i) (rtlreg_t* dest, const rtlreg_t* src1, int imm) { \
		*dest = concat(c_, name) (*src1, imm); \
	}


make_rtl_arith_logic(add)
make_rtl_arith_logic(sub)
make_rtl_arith_logic(and)
make_rtl_arith_logic(or)
make_rtl_arith_logic(xor)
make_rtl_arith_logic(shl)
make_rtl_arith_logic(shr)
make_rtl_arith_logic(sar)
make_rtl_arith_logic(slt)
make_rtl_arith_logic(sltu)

static inline void rtl_mul(rtlreg_t* dest_hi, rtlreg_t* dest_lo, const rtlreg_t* src1, const rtlreg_t* src2) {
	asm volatile("mul %3" : "=d"(*dest_hi), "=a"(*dest_lo) : "a"(*src1), "r"(*src2));
}

static inline void rtl_imul(rtlreg_t* dest_hi, rtlreg_t* dest_lo, const rtlreg_t* src1, const rtlreg_t* src2) {
	asm volatile("imul %3" : "=d"(*dest_hi), "=a"(*dest_lo) : "a"(*src1), "r"(*src2));
}

static inline void rtl_div(rtlreg_t* q, rtlreg_t* r, const rtlreg_t* src1_hi, const rtlreg_t* src1_lo, const rtlreg_t* src2) {
	asm volatile("div %4" : "=a"(*q), "=d"(*r) : "d"(*src1_hi), "a"(*src1_lo), "r"(*src2));
}

static inline void rtl_idiv(rtlreg_t* q, rtlreg_t* r, const rtlreg_t* src1_hi, const rtlreg_t* src1_lo, const rtlreg_t* src2) {
	asm volatile("idiv %4" : "=a"(*q), "=d"(*r) : "d"(*src1_hi), "a"(*src1_lo), "r"(*src2));
}

static inline void rtl_lm(rtlreg_t *dest, const rtlreg_t* addr, int len) {
	*dest = swaddr_read(*addr, len);
}

static inline void rtl_sm(rtlreg_t* addr, int len, const rtlreg_t* src1) {
	swaddr_write(*addr, len, *src1);
}

static inline void rtl_lm_nemu_b(rtlreg_t *dest, const void *addr, const rtlreg_t* offset) {
	*dest = *(uint8_t *)(addr + *offset);
}

static inline void rtl_lm_nemu_w(rtlreg_t *dest, const void *addr, const rtlreg_t* offset) {
	*dest = *(uint16_t *)(addr + *offset);
}

static inline void rtl_lm_nemu_l(rtlreg_t *dest, const void *addr, const rtlreg_t* offset) {
	*dest = *(uint32_t *)(addr + *offset);
}

static inline void rtl_sm_nemu_b(void *addr, const rtlreg_t* offset, const rtlreg_t* src1) {
	*(uint8_t *)(addr + *offset) = *src1;
}

static inline void rtl_sm_nemu_w(void *addr, const rtlreg_t* offset, const rtlreg_t* src1) {
	*(uint16_t *)(addr + *offset) = *src1;
}

static inline void rtl_sm_nemu_l(void *addr, const rtlreg_t* offset, const rtlreg_t* src1) {
	*(uint32_t *)(addr + *offset) = *src1;
}

static inline void rtl_lr_b(rtlreg_t* dest, int r) {
	*dest = reg_b(r);
}

static inline void rtl_lr_w(rtlreg_t* dest, int r) {
	*dest = reg_w(r);
}

static inline void rtl_lr_l(rtlreg_t* dest, int r) {
	*dest = reg_l(r);
}

static inline void rtl_sr_b(int r, const rtlreg_t* src1) {
	reg_b(r) = *src1;
}

static inline void rtl_sr_w(int r, const rtlreg_t* src1) {
	reg_w(r) = *src1;
}

static inline void rtl_sr_l(int r, const rtlreg_t* src1) {
	reg_l(r) = *src1;
}

/* RTL psuedo instructions */

static inline void rtl_lr(rtlreg_t* dest, int r, int len) {
	switch(len) {
		case 4: rtl_lr_l(dest, r); return;
		case 1: rtl_lr_b(dest, r); return;
		case 2: rtl_lr_w(dest, r); return;
		default: assert(0);
	}
}

static inline void rtl_sr(int r, int len, const rtlreg_t* src1) {
	switch(len) {
		case 4: rtl_sr_l(r, src1); return;
		case 1: rtl_sr_b(r, src1); return;
		case 2: rtl_sr_w(r, src1); return;
		default: assert(0);
	}
}

#define make_rtl_setget_eflags(f) \
	static inline void concat(rtl_set_, f) (const rtlreg_t* src) { \
		TODO(); \
	} \
	static inline void concat(rtl_get_, f) (rtlreg_t* dest) { \
		TODO(); \
	}

make_rtl_setget_eflags(CF)
make_rtl_setget_eflags(OF)
make_rtl_setget_eflags(PF)
make_rtl_setget_eflags(ZF)
make_rtl_setget_eflags(SF)
make_rtl_setget_eflags(DF)
make_rtl_setget_eflags(IF)


static inline void rtl_mv(rtlreg_t* dest, const rtlreg_t *src1) {
	// dest <- src1
	TODO();
}

static inline void rtl_not(rtlreg_t* dest) {
	// dest <- ~dest
	TODO();
}

static inline void rtl_sext(rtlreg_t* dest, const rtlreg_t* src1, int len) {
	// dest <- signext(src1[(len * 8 - 1) .. 0])
	TODO();
}

static inline void rtl_push(const rtlreg_t* src1) {
	// esp <- esp - 4
	// M[esp] <- src1
	TODO();
}

static inline void rtl_pop(rtlreg_t* dest) {
	// dest <- M[esp]
	// esp <- esp + 4
	TODO();
}

static inline void rtl_eq0(rtlreg_t* dest, const rtlreg_t* src1) {
	// dest <- (src1 == 0 ? 1 : 0)
	TODO();
}

static inline void rtl_eqi(rtlreg_t* dest, const rtlreg_t* src1, int imm) {
	// dest <- (src1 == imm ? 1 : 0)
	TODO();
}

static inline void rtl_neq0(rtlreg_t* dest, const rtlreg_t* src1) {
	// dest <- (src1 != 0 ? 1 : 0)
	TODO();
}

static inline void rtl_msb(rtlreg_t* dest, const rtlreg_t* src1, int len) {
	// dest <- src1[len * 8 - 1]
	TODO();
}

static inline void rtl_update_PF(const rtlreg_t* result) {
	// eflags.PF <- is_parity(result)
	TODO();
}

static inline void rtl_update_ZF(const rtlreg_t* result) {
	// eflags.ZF <- is_zero(result)
	TODO();
}

static inline void rtl_update_SF(const rtlreg_t* result, int len) {
	// eflags.SF <- is_sign(result[len * 8 - 1 .. 0])
	TODO();
}

static inline void rtl_update_PFZFSF(const rtlreg_t* result, int len) {
	rtl_update_PF(result);
	rtl_update_ZF(result);
	rtl_update_SF(result, len);
}

#endif
