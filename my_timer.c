#include "my_timer.h"

static void *update_ss(void *arg)
{
	my_timer *my_timer_obj = (my_timer *)arg;
	my_timer_obj->ss += 1;

	sleep(15);
}

static void *update_mm(void *arg)
{
	my_timer *my_timer_obj = (my_timer *)arg;
	my_timer_obj->mm += 1;

	sleep(15);
}
static void *update_hh(void *arg)
{
	my_timer *my_timer_obj = (my_timer *)arg;
	my_timer_obj->hh += 1;

	sleep(15);
}

void destroy_my_timer(my_timer *my_timer_obj)
{
	if (my_timer_obj)
		free(my_timer_obj);
}
static void show_current_time(my_timer *my_timer_obj)
{
	char time_buffer[TIME_BUFFER_LENGTH];

	int ret;
	ret = snprintf(time_buffer, TIME_BUFFER_LENGTH, "%i:%i:%i",
		       my_timer_obj->hh, my_timer_obj->mm, my_timer_obj->ss);
	printf("TIME:\t%s\n", time_buffer);
	assert(ret >= 0);
	assert(ret <= TIME_BUFFER_LENGTH);
}
my_timer *new_my_timer(void)
{
	my_timer *my_timer_obj = calloc(1, sizeof(my_timer));

	if (!my_timer_obj)
		free(my_timer_obj);

	my_timer_obj->ss = 0;
	my_timer_obj->mm = 0;
	my_timer_obj->hh = 0;
	my_timer_obj->update_ss = update_ss;
	my_timer_obj->update_mm = update_mm;
	my_timer_obj->update_hh = update_hh;
	my_timer_obj->show_current_time = show_current_time;

	return my_timer_obj;
}
