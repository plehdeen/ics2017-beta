#include "cpu/exec.h"

// compute step in t0
static inline void step(void) {
	rtl_li(&t1, id_dest->len);
	rtl_li(&t2, -id_dest->len);

	// implement the following only with sequential statements
	// t0 <- (eflags.DF ? t2 : t1);
	TODO();
}

make_EHelper(movs) {
	step();

	operand_write(id_dest, &id_src->val);
	rtl_add(&cpu.esi, &cpu.esi, &t0);
	rtl_add(&cpu.edi, &cpu.edi, &t0);

	print_asm_template2(movs);
}

make_EHelper(lods) {
	step();

	operand_write(id_dest, &id_src->val);
	rtl_add(&cpu.esi, &cpu.esi, &t0);

	print_asm_template2(lods);
}

make_EHelper(scas) {
	step();

	rtl_add(&cpu.edi, &cpu.edi, &t0);

	rtl_sub(&t2, &id_dest->val, &id_src->val);

	// unnecessary to update other flags in NEMU
	rtl_update_ZF(&t2);

	print_asm_template2(scas);
}

make_EHelper(stos) {
	step();

	operand_write(id_dest, &id_src->val);
	rtl_add(&cpu.edi, &cpu.edi, &t0);

	print_asm_template2(stos);
}

#define OPCODE_CMPSB 0xa6
#define OPCODE_CMPSW 0xa7
#define OPCODE_SCASB 0xae
#define OPCODE_SCASW 0xaf

make_EHelper(rep) {
	bool repne = decoding.opcode & 0x1;

	uint32_t opcode = instr_fetch(eip, 1);
	if(opcode == 0x66) {
		decoding.is_operand_size_16 = true;
		opcode = instr_fetch(eip, 1);
	}

	general_decode(opcode);
#ifdef DEBUG
	uint32_t cnt = 0;
#endif

	while(cpu.ecx) {
		void string_exec(swaddr_t*, uint32_t);
		swaddr_t eip_temp = *eip;
		string_exec(&eip_temp, opcode);
		rtl_subi(&cpu.ecx, &cpu.ecx, 1);
#ifdef DEBUG
		cnt ++;
#endif
		if(opcode == OPCODE_CMPSB ||
			opcode == OPCODE_CMPSW ||
			opcode == OPCODE_SCASB ||
			opcode == OPCODE_SCASW) {

			rtl_get_ZF(&t0);
			if((repne ^ t0) & 0x1) break;
		}
	}

	decoding.is_operand_size_16 = false;

#ifdef DEBUG
	char temp[80];
	strcpy(temp, decoding.assembly);
	sprintf(decoding.assembly, "%s %s [cnt = %d]", (repne ? "repne" : "rep"), temp, cnt);
#endif
}
