#include "cpu/exec.h"

make_EHelper(int3) {
	void do_int3(void);
	do_int3();
	print_asm("int3");
}

make_EHelper(nop) {
	print_asm("nop");
}

make_EHelper(std) {
	rtl_li(&t0, 1);
	rtl_set_DF(&t0);
	print_asm("std");
}

make_EHelper(cld) {
	rtl_set_DF(&tzero);
	print_asm("cld");
}
