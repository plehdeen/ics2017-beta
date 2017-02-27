#include "nemu.h"
#include "cpu/decode.h"
#include "monitor/monitor.h"

/* The assembly code of instructions executed is only output to the screen
 * when the number of instructions executed is less than this value.
 * This is useful when you use the `si' command.
 * You can modify this value as you want.
 */
#define MAX_INSTR_TO_PRINT 10

int nemu_state = STOP;

void exec_wrapper(void);

/* This function will be called when an `int3' instruction is being executed. */
void do_int3() {
	printf("\nHit breakpoint at eip = 0x%08x\n", cpu.eip);
	nemu_state = STOP;
}

/* Simulate how the CPU works. */
void cpu_exec(uint32_t n) {
	if(nemu_state == END) {
		printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
		return;
	}
	nemu_state = RUNNING;

#ifdef DEBUG
	bool print_flag = n < MAX_INSTR_TO_PRINT;
#endif

	for(; n > 0; n --) {
		/* Execute one instruction, including instruction fetch,
		 * instruction decode, and the actual execution. */
		exec_wrapper();

#ifdef DEBUG
		if((n & 0xffff) == 0) {
			/* Output some dots while executing the program. */
			fputc('.', stderr);
		}

		if(print_flag) {
			puts(decoding.asm_buf);
		}

		/* TODO: check watchpoints here. */

#endif

#ifdef HAS_DEVICE
		extern void device_update();
		device_update();
#endif

		if(nemu_state != RUNNING) { return; }
	}

	if(nemu_state == RUNNING) { nemu_state = STOP; }
}
