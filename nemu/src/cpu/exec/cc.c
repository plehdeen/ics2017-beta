#include "cpu/rtl.h"

/* Condition Code */

char *cc_name[] = {
	"o", "no", "b", "nb",
	"e", "ne", "be", "nbe",
	"s", "ns", "p", "np",
	"l", "nl", "le", "nle"
};

void rtl_setcc(rtlreg_t* dest, uint8_t subcode) {
	bool invert = subcode & 0x1;
	enum {O, NO, B, NB, E, NE, BE, NBE, S, NS, P, NP, L, NL, LE, NLE};

	// TODO: Query EFLAGS to determine whether the condition code is satisfied.
	// dest <- ( cc is satisfied ? 1 : 0)
	switch(subcode & 0xe) {
		case O:
		case B:
		case E:
		case BE:
		case S:
		case P:
		case L:
		case LE:
			TODO();
		default: panic("should not reach here");
	}

	if(invert) {
		rtl_xori(dest, dest, 0x1);
	}
}
