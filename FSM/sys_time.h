#ifndef SYS_TIME_H_
#define SYS_TIME_H_

#include <time.h>

unsigned int get_sys_tick();

unsigned int diff_time(unsigned int, unsigned int);

unsigned int diff_cur_time(unsigned int);

unsigned char time_cmp(unsigned int, unsigned int);

char * time_to_string(unsigned int);

void print_cur_time();

#endif // !_SYS_TIME_H

