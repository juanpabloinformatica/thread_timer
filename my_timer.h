#ifndef __MY_TIMER__
#define __MY_TIMER__

#define MAX_SS 59
#define MAX_MM 59
#define MAX_HH 59

#include "my_thread_monitor.h"
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
/*hh:mm:ss\0*/
#define TIME_BUFFER_LENGTH 9
typedef struct my_timer my_timer;

struct my_timer {
	int ss;
	int mm;
	int hh;
	void *(*update_ss)(void *arg);
	void *(*update_mm)(void *arg);
	void *(*update_hh)(void *arg);
	void *(*show_current_time)(void *args);
	void (*start_timer)(my_timer *my_timer);
	my_thread_monitor *my_thread_monitor;
};
my_timer *new_my_timer(void);
void destroy_my_timer(my_timer *my_timer_obj);

#endif
