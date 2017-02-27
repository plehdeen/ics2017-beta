#include "cpu/exec.h"
#include "all-instr.h"

typedef struct {
	DHelper decode;
	EHelper execute;
} opcode_entry;

#define EX(ex) {NULL, concat(exec_, ex)}
#define IDEX(id, ex) {concat(decode_, id), concat(exec_, ex)}
#define EMPTY EX(inv)

/* Instruction Decode and EXecute */
static inline void idex(swaddr_t *eip, opcode_entry *e) {
	/* eip is pointing to the byte next to opcode */
	if(e->decode)
		e->decode(eip);
	e->execute(eip);
}

static make_EHelper(2byte_esc);

#define make_group(name, item0, item1, item2, item3, item4, item5, item6, item7) \
	static opcode_entry concat(opcode_table_, name) [8] = { \
	/* 0x00 */	item0, item1, item2, item3, \
	/* 0x04 */	item4, item5, item6, item7  \
	}; \
	static make_EHelper(name) { \
		idex(eip, &concat(opcode_table_, name)[decoding.ext_opcode]); \
	}
	
/* 0x80, 0x81, 0x83 */
make_group(gp1,
	EMPTY, EMPTY, EMPTY, EMPTY,
	EMPTY, EMPTY, EMPTY, EMPTY)

/* 0xc0, 0xc1, 0xd0, 0xd1, 0xd2, 0xd3 */
make_group(gp2,
	EMPTY, EMPTY, EMPTY, EMPTY,
	EMPTY, EMPTY, EMPTY, EMPTY)

/* 0xf6, 0xf7 */
make_group(gp3,
	EMPTY, EMPTY, EMPTY, EMPTY,
	EMPTY, EMPTY, EMPTY, EMPTY)

/* 0xfe */
make_group(gp4,
	EMPTY, EMPTY, EMPTY, EMPTY,
	EMPTY, EMPTY, EMPTY, EMPTY)

/* 0xff */
make_group(gp5,
	EMPTY, EMPTY, EMPTY, EMPTY,
	EMPTY, EMPTY, EMPTY, EMPTY)

/* 0x0f 0x01*/
make_group(gp7,
	EMPTY, EMPTY, EMPTY, EMPTY,
	EMPTY, EMPTY, EMPTY, EMPTY)

/* TODO: Add more instructions!!! */

opcode_entry opcode_table [512] = {
/* 0x00 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x04 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x08 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x0c */	EMPTY, EMPTY, EMPTY, EX(2byte_esc),
/* 0x10 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x14 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x18 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x1c */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x20 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x24 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x28 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x2c */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x30 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x34 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x38 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x3c */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x40 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x44 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x48 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x4c */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x50 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x54 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x58 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x5c */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x60 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x64 */	EMPTY, EMPTY, EX(operand_size), EMPTY,
/* 0x68 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x6c */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x70 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x74 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x78 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x7c */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x80 */	IDEX(I2E, gp1), IDEX(I2E, gp1), EMPTY, IDEX(SI2E, gp1),
/* 0x84 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x88 */	IDEX(mov_G2E, mov), IDEX(mov_G2E, mov), IDEX(mov_E2G, mov), IDEX(mov_E2G, mov),
/* 0x8c */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x90 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x94 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x98 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x9c */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xa0 */	IDEX(O2a, mov), IDEX(O2a, mov), IDEX(a2O, mov), IDEX(a2O, mov),
/* 0xa4 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xa8 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xac */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xb0 */	IDEX(mov_I2r, mov), IDEX(mov_I2r, mov), IDEX(mov_I2r, mov), IDEX(mov_I2r, mov),
/* 0xb4 */	IDEX(mov_I2r, mov), IDEX(mov_I2r, mov), IDEX(mov_I2r, mov), IDEX(mov_I2r, mov),
/* 0xb8 */	IDEX(mov_I2r, mov), IDEX(mov_I2r, mov), IDEX(mov_I2r, mov), IDEX(mov_I2r, mov),
/* 0xbc */	IDEX(mov_I2r, mov), IDEX(mov_I2r, mov), IDEX(mov_I2r, mov), IDEX(mov_I2r, mov),
/* 0xc0 */	IDEX(gp2_Ib2E, gp2), IDEX(gp2_Ib2E, gp2), EMPTY, EMPTY,
/* 0xc4 */	EMPTY, EMPTY, IDEX(mov_I2E, mov), IDEX(mov_I2E, mov),
/* 0xc8 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xcc */	EX(int3), EMPTY, EMPTY, EMPTY,
/* 0xd0 */	IDEX(gp2_1_E, gp2), IDEX(gp2_1_E, gp2), IDEX(gp2_cl2E, gp2), IDEX(gp2_cl2E, gp2),
/* 0xd4 */	EMPTY, EMPTY, EX(nemu_trap), EMPTY,
/* 0xd8 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xdc */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xe0 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xe4 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xe8 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xec */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xf0 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xf4 */	EMPTY, EMPTY, IDEX(E, gp3), IDEX(E, gp3),
/* 0xf8 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xfc */	EMPTY, EMPTY, IDEX(E, gp4), IDEX(E, gp5),

/*2 byte_opcode_table */

/* 0x00 */	EMPTY, IDEX(gp7_E, gp7), EMPTY, EMPTY,
/* 0x04 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x08 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x0c */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x10 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x14 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x18 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x1c */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x20 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x24 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x28 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x2c */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x30 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x34 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x38 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x3c */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x40 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x44 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x48 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x4c */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x50 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x54 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x58 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x5c */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x60 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x64 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x68 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x6c */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x70 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x74 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x78 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x7c */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x80 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x84 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x88 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x8c */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x90 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x94 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x98 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0x9c */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xa0 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xa4 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xa8 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xac */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xb0 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xb4 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xb8 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xbc */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xc0 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xc4 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xc8 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xcc */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xd0 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xd4 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xd8 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xdc */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xe0 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xe4 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xe8 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xec */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xf0 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xf4 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xf8 */	EMPTY, EMPTY, EMPTY, EMPTY,
/* 0xfc */	EMPTY, EMPTY, EMPTY, EMPTY
};

static make_EHelper(2byte_esc) {
	uint32_t opcode = instr_fetch(eip, 1) | 0x100;
	general_decode(opcode);
	idex(eip, &opcode_table[opcode]);
}

static unsigned long long nr_instr = 0;
unsigned long long get_nr_instr(void) {
	return nr_instr;
}

make_EHelper(real) {
	uint32_t opcode = instr_fetch(eip, 1);
	general_decode(opcode);
	idex(eip, &opcode_table[opcode]);
}

void string_exec(swaddr_t* eip, uint32_t opcode) {
	nr_instr ++;
	idex(eip, &opcode_table[opcode]);
}

static inline void update_eip(void) {
	cpu.eip = (decoding.is_jmp ? (decoding.is_jmp = 0, decoding.jmp_eip) : decoding.seq_eip);
}

void exec_wrapper(void) {
	decoding.seq_eip = cpu.eip;
#ifdef DEBUG
	decoding.p = decoding.asm_buf;
	decoding.p += sprintf(decoding.p, "%8x:   ", cpu.eip);
#endif

	nr_instr ++;
	exec_real(&decoding.seq_eip);

#ifdef DEBUG
	int instr_len = decoding.seq_eip - cpu.eip;
	sprintf(decoding.p, "%*.s", 50 - (12 + 3 * instr_len), "");
	strcat(decoding.asm_buf, decoding.assembly);
	Log_write("%s\n", decoding.asm_buf);
#endif

	update_eip();
}
