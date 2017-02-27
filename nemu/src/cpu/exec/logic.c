#include "cpu/exec.h"

static inline void and_internal() {
	rtl_and(&t2, &id_dest->val, &id_src->val);
	rtl_update_PFZFSF(&t2, id_dest->len);
	rtl_set_CF(&tzero);
	rtl_set_OF(&tzero);
}

make_EHelper(test) {
	and_internal();
	print_asm_template2(test);
}

make_EHelper(and) {
	and_internal();
	operand_write(id_dest, &t2);
	print_asm_template2(and);
}

make_EHelper(xor) {
	rtl_xor(&t2, &id_dest->val, &id_src->val);
	operand_write(id_dest, &t2);
	rtl_update_PFZFSF(&t2, id_dest->len);
	rtl_set_CF(&tzero);
	rtl_set_OF(&tzero);
	print_asm_template2(xor);
}

make_EHelper(or) {
	rtl_or(&t2, &id_dest->val, &id_src->val);
	operand_write(id_dest, &t2);
	rtl_update_PFZFSF(&t2, id_dest->len);
	rtl_set_CF(&tzero);
	rtl_set_OF(&tzero);
	print_asm_template2(or);
}

make_EHelper(sar) {
	rtl_sar(&t2, &id_dest->val, &id_src->val);
	operand_write(id_dest, &t2);
	rtl_update_PFZFSF(&t2, id_dest->len);
	// unnecessary to update CF and OF in NEMU
	print_asm_template2(sar);
}

make_EHelper(shl) {
	rtl_shl(&t2, &id_dest->val, &id_src->val);
	operand_write(id_dest, &t2);
	rtl_update_PFZFSF(&t2, id_dest->len);
	// unnecessary to update CF and OF in NEMU
	print_asm_template2(shl);
}

make_EHelper(shr) {
	rtl_shr(&t2, &id_dest->val, &id_src->val);
	operand_write(id_dest, &t2);
	rtl_update_PFZFSF(&t2, id_dest->len);
	// unnecessary to update CF and OF in NEMU
	print_asm_template2(shr);
}

make_EHelper(setcc) {
	uint8_t subcode = decoding.opcode & 0xf;
	rtl_setcc(&t2, subcode);
	operand_write(id_dest, &t2);

	print_asm("set%s %s", cc_name[subcode], id_dest->str);
}

make_EHelper(not) {
	rtl_not(&id_dest->val);
	operand_write(id_dest, &id_dest->val);

	print_asm_template1(not);
}

make_EHelper(shrd) {
	// unnecessary to implement word operation in NEMU
	assert(id_dest->len == 4);

	rtl_shr(&t2, &id_dest->val, &id_src->val);
	rtl_li(&t0, 32);
	rtl_sub(&t0, &t0, &id_src->val);
	rtl_shl(&t0, &id_src2->val, &t0);
	rtl_or(&t2, &t2, &t0);

	operand_write(id_dest, &t2);
	// unnecessary to update eflags in NEMU
	print_asm_template3(shrd);
}

make_EHelper(bt) {
	TODO();

	print_asm_template2(bt);
}
