#include "pch.h"

#include "sys_time.h"
#include <stdio.h>

unsigned int get_sys_tick()
{
	time_t tick;
	time(&tick);
	printf("%d, %d\n", (unsigned int)tick, (unsigned int)tick);
	return (unsigned int)tick;
}

unsigned int diff_time(unsigned int time_1, unsigned int time_2)
{
	return time_1 > time_2 ? time_1 - time_2 : 0;
}

unsigned int diff_cur_time(unsigned int start_tick)
{
	unsigned int cur_tick = get_sys_tick();
	return diff_time(cur_tick, start_tick);
}

unsigned char time_cmp(unsigned int time_1, unsigned int time_2)
{
	return time_1 > time_2 ? 1 : 0;
}

char * time_to_string(unsigned int tick)
{
	return ctime((time_t*)&tick);
}

void print_cur_time()
{
	unsigned int cur_tick = get_sys_tick();
	char * str = time_to_string(cur_tick);
	printf("current time: %s\n", str);
}