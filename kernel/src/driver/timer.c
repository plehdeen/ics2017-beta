#include "common.h"

void add_irq_handle(int, void (*)(void));

static void timer_test(void) {
	static int nr_timer_intr = 0;
	if(nr_timer_intr < 10) {
		nr_timer_intr ++;
		Log("timer interrupt comes for %d times", nr_timer_intr);
		if(nr_timer_intr == 10) {
			Log("It seems the interrupt procedure in kernel works well.");
		}
	}
}

void init_timer(void) {
	add_irq_handle(0, timer_test);
}
