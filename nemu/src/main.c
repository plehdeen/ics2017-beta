#include "common.h"
#include <unistd.h>
#include <sys/times.h>

void init_monitor(int, char *[]);
void reg_test();
void restart();
void ui_mainloop();
unsigned long long get_nr_instr(void);

int main(int argc, char *argv[]) {

	/* Initialize the monitor. */
	init_monitor(argc, argv);

	/* Test the implementation of the `CPU_state' structure. */
	reg_test();

	/* Initialize the virtual computer system. */
	restart();

	struct tms begin, end;
	times(&begin);

	/* Receive commands from user. */
	ui_mainloop();

	times(&end);

	double utime = (end.tms_utime - begin.tms_utime)/(double)sysconf(_SC_CLK_TCK);
	Log("utime{%7.2lfs}, #instr{%12llu}, freq{%10.2lfKHz}", utime, get_nr_instr(),
			get_nr_instr()/utime/1000);

	return 0;
}
